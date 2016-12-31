#include <dirent.h>
#include <stdio.h>

void normprint(char *str)
{
    DIR *dir;
    struct dirent *dp;

    dir = opendir (str);

     while ((dp = readdir (dir)) != NULL)
     {
         
         printf("%s\n", dp->d_name);
     }
}

int main()
{
    normprint(".");
}
