#include <stdio.h>
#include <stdlib.h>
#include "path.h"
int main(int argc, char const *argv[])
{
    char*str=pwd();
    puts(str);
    free(str);
    return 0;
}
