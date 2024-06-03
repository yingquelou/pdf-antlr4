与startxref -> trailer & xref -> obj 的方式不同
本仓库采用antlr4对pdf进行硬解析
旨在学习antlr4


词法属性attr对应的类型和值

属性|类型|描述
-|-|-
`text`|`String`|词法符号匹配到的文本，它会被替换成`getText()`方法调用。例如`$ID.text`
`type`|`int`|词法符号对应的正整数类型值，如`INT`。它会转换成`getType()`方法调用。例如`$ID.type`
`line`|`int`|词法符号所处的行号，从1开始计数。它会被转换成getLine()方法调用，例如`$ID.line`
`pos`|`int`|词法符号的第一个字符在行内的位置，从0开始计数。它会被转换成`getCharPositionInLine()`方法调用。例如：`$ID.pos`
`index`|`int`|词法符号在词法符号流中的全局索引值，从0开始计数。它会转换成`getTokenIndex()`方法调用。例如：`$ID.index`
`channel`|`int`|词法符号所在的通道数。语法分析器只处理一个通道的词法符号。忽略其他通道的词法符号。默认的通道是`0(Token.DEFAULT_CHANNEL)`,默认的隐藏通道是`Token.HIDDEN_CHANNEL`。它会被转换成`getChannel()`方法调用。例如：`$ID.channel`
`int`|`int`|词法符号持有的整数值。它假设词法符号的文本是有效的数字。对于计算器之类的程序，这个属性非常有用。它会被转换成`Integer.valueOf(text-of-token)`。例如：`$INT.int`

文法属性attr对应的类型和值

属性|类型|描述
-|-|-
`text`|`String`|一条规则匹配的文本或者从这条规则的起始位置到`$text`当前位置对应的文本。需要注意的是，它包含了隐藏通道中的全部词法符号，这通常是正确的，因为其中含有全部的空白字符和注释。当作为当前规则的属性时，它可以在任何动作中使用，包括异常处理动作
`start`|`Token`|在主要词法符号通道上被规则匹配到第一个词法符号。换句话说，该属性永远不会位于隐藏通道中。对于那些不匹配任何词法符号的规则，这个属性指向第一个后续的词法符号。当作为当前规则的属性时，它可以在规则内的任何动作中使用
`stop`|`Token`|规则匹配到最后一个非隐藏通道的词法符号。当作为当前规则的属性时，它仅能在`after`和`finally`动作中使用
`ctx`|`ParseRuleContext`|一条规则调用对应的规则上下文对象。通过这个属性可以访问其余全部属性。例如：`$ctx.start`当问当前规则上下文对象的start字段。它等价于`$start`。

曾采用YACC方案

- 参见 https://github.com/yingquelou/pdfparse.git