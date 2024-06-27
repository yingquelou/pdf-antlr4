#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include<pdf.config.h>
int main(int argc, char const *argv[])
{
    json_t *obj = json_pack("{s:s}", "foo","baz");
    char *s = json_dumps(obj, JSON_COMPACT);
    puts(s);
    free(s);
    JSON_TRUE;
    return 0;
}
