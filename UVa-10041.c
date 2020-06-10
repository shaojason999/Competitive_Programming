/* UVa 10082 - WERTYU
#		            Problem         Verdict     Language    Run Time    Submission Date
25126846    10041   Vito's Family   Accepted    ANSI C      0.010       2020-06-10 14:18:08
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    int i;
    int Cases, relatives;
    int input[500];
    int distance, l, r;

    scanf("%d",&Cases);
    while(Cases--){
        scanf("%d",&relatives);
        for(i=0;i<relatives;++i)
            scanf("%d",&input[i]);
        qsort(input,relatives,sizeof(int),cmp);

        distance = 0;
        l = 0;
        r = relatives-1;
        while(l<r){
            distance += input[r] - input[l];
            ++l;
            --r;
        }

        printf("%d\n",distance);
    }
    return 0;

}