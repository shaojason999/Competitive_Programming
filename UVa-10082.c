/* UVa 10082 - WERTYU
#		            Problem Verdict     Language    Run Time    Submission Date
25100671    10082   WERTYU  Accepted    ANSI C      0.000       2020-06-03 12:27:05
*/

#include <stdio.h>
#include <string.h>

int main()
{
    int i;

    char input[100000];
    char transfer[100];
    char temp[100] = "!!#$$&;()*+M0,.9`12345678:L<->?@AVXSWDFGUHJKNBIOQEARYCQZTZP][^_";

    memset(transfer,' ',33);
    transfer[10] = '\n';
    transfer[33] = '\0';
    strncat(transfer,temp,64);

    while(fgets(input,sizeof(input),stdin)){
        for(i=0;input[i]!='\0';++i)
            printf("%c",transfer[input[i]]);
    }
    return 0;

}