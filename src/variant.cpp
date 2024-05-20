#include <iostream>
#include <array>
#include <string>
// 辅助工具
template <size_t Index>
struct in_place_index_t
{
}; // 单纯的静态工具，用于传递Index，没有运行期意义

template <size_t Index>
constexpr inline in_place_index_t<Index> in_place_index; // 对应in_place_index_t类型的实例

template <size_t Index, typename Head, typename... Args>
struct get_type_by_index : get_type_by_index<Index - 1, Args...>
{
};

template <typename Head, typename... Args>
struct get_type_by_index<0, Head, Args...>
{
    using type = Head;
};

// variant结构的声明
template <typename... Types>
class variant
{
public:
    template <size_t Index, typename... Args>
    variant(const in_place_index_t<Index> &, Args &&...args);

    variant(const variant &va);
    variant(variant &&va);

    ~variant();

    variant &operator=(const variant &va);
    variant &operator=(variant &&va);

    // 获取当前序号
    int index() const;

    // 取出数据
    template <size_t Index>
    auto get() const -> std::add_lvalue_reference_t<std::decay_t<typename get_type_by_index<Index, Types...>::type>>;

private:
    void *data_ = std::malloc(std::max(sizeof(Types)...));
    int index_; // 当前生效的数据序号

    // 生成每一个Type下对应类型的析构方法
    template <typename Type>
    void destory_data();

    // 生成每一个Type下对应类型的构造方法
    template <typename Type>
    void create_data(const void *obj);
};

// 实现构造函数
template <typename... Types>
template <size_t Index, typename... Args>
variant<Types...>::variant(const in_place_index_t<Index> &, Args &&...args) : index_(Index)
{
    using data_type = typename get_type_by_index<Index, Args...>::type;
    new (data_) std::decay_t<data_type>(std::forward<Args>(args)...);
}

// 实现析构函数
template <typename... Types>
variant<Types...>::~variant()
{
    // 析构函数中，把所有的index对应的destory_data保存下来（编译期完成这样一个映射表）
    std::array<void (variant::*const)(), sizeof...(Types)> destory_functions{
        &variant::destory_data<Types>...};

    // 到了运行期，根据当前实际的index_值，选择对应的析构方法
    if (data_ != nullptr)
    {
        (this->*destory_functions.at(index_))();
        std::free(data_);
    }
}

// 实现拷贝构造函数
template <typename... Types>
variant<Types...>::variant(const variant &va) : index_(va.index_)
{
    // 静态期保存所有类型的构造函数
    static std::array<void (variant<Types...>::*)(const void *), sizeof...(Types)> create_functions{
        &variant<Types...>::create_data<Types>...};
    // 动态时根据index_调用对应的构造
    (this->*create_functions.at(index_))(va.data_);
}

// 实现拷贝赋值函数
template <typename... Types>
variant<Types...> &variant<Types...>::operator=(const variant &va)
{
    // 先析构现有数据
    std::array<void (variant<Types...>::*)(), sizeof...(Types)> destory_functions{
        &variant<Types...>::destory_data<Types>...};
    (this->*destory_functions.at(index_))();

    // 再重新构造
    std::array<void (variant<Types...>::*)(const void *), sizeof...(Types)> create_functions{
        &variant<Types...>::create_data<Types>...};
    (this->*create_functions.at(index_))(va.data_);

    return *this;
}

// 实现移动构造函数
template <typename... Types>
variant<Types...>::variant(variant &&va) : index_(va.index_), data_(va.index_)
{
    // 上面直接浅拷贝即可，然后把被移动的data_置空
    va.data_ = nullptr;
    va.index_ = -1; // 标记为不合法值
}

// 实现移动赋值函数
template <typename... Types>
variant<Types...> &variant<Types...>::operator=(variant &&va)
{
    // 先析构现有数据
    std::array<void (variant<Types...>::*)(), sizeof...(Types)> destory_functions{
        &variant<Types...>::destory_data<Types>...};
    (this->*destory_functions.at(index_))();

    // 再浅拷贝
    data_ = va.data_;
    index_ = va.index_;

    // 把被移动的data_置空
    va.data_ = nullptr;
    va.index_ = -1; // 标记为不合法值

    return *this;
}

// 私有方法的实现
template <typename... Types>
template <typename Type>
void variant<Types...>::create_data(const void *obj)
{
    // 用data_指针按照对应的类型调用拷贝构造
    new (data_) Type(*static_cast<const Type *>(obj));
}

template <typename... Types>
template <typename Type>
void variant<Types...>::destory_data()
{
    // 用data_指针按照对应的类型调用析构函数
    static_cast<std::add_pointer_t<Type>>(data_)->~Type();
}

// 公有方法的实现
// 获取序号
template <typename... Types>
int variant<Types...>::index() const
{
    return index_;
}

// 取出数据（这个功能在std::variant中其实实现在std::get中）
template <typename... Types>
template <size_t Index>
auto variant<Types...>::get() const -> std::add_lvalue_reference_t<std::decay_t<typename get_type_by_index<Index, Types...>::type>>
{
    using data_type = std::decay_t<typename get_type_by_index<Index, Types...>::type>;
    return *static_cast<data_type *>(data_);
}
#include <variant>
int main(int argc, char const *argv[])
{
    // variant<long, int> var(in_place_index<0>, 11);
    // std::cout << var.get<1>();
    std::variant<int,double> v(std::in_place_index<1>,1.5);
    return 0;
}
