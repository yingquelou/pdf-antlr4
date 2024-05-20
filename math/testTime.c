#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    time_t t;
    struct tm *date = NULL;
    char buffer[1024];
    for (clock_t start = clock(), ct = 0; 1;)
    {
        if ((clock() - start) > ct)
        {
            time(&t);
            date = localtime(&t);
            // strftime(buffer, 1024, "%Y/%m/%d %A %H:%M:%S", date);
            strftime(buffer, 1024, "%x %X", date);
            ct += CLOCKS_PER_SEC;
            system("cls");
            puts(buffer);
        }
    }
    return 0;
}