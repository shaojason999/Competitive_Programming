/* UVa 10050 - Hartals
#		            Problem Verdict	    Language	Run Time	Submission Date
24974748	10050	Hartals	Accepted	ANSI C	    0.000	    2020-05-03 15:01:32
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    int T, N, P, input;
    int count;
    int i,j;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        bool hartal_period[N+1];
        bool hartal[N+1];   /* already counted or not */
        memset(hartal_period,0,sizeof(hartal_period));
        memset(hartal,0,sizeof(hartal));
        count = 0;
        scanf("%d",&P);
        for(i=0;i<P;++i){
            scanf("%d",&input);
            if(input<=N)
                hartal_period[input] = true;
        }
        /* special case */
        if(hartal_period[1]){
            if(N%7 == 5)
                printf("%d\n",N-(2*(N/7)+1));
            else if(N%7 == 6)
                printf("%d\n",N-(2*(N/7)+2));
            else
                printf("%d\n",N-2*(N/7));
            continue;
        }
        /* delete the multiples */
        for(i=2;i<=N;++i){
            if(hartal_period[i]){
                for(j=2;i*j<=N;++j){
                    hartal_period[i*j] = false;
                }
            }
        }
        /* set the weekly holiday hartal, but not counted (which make it easily to calculate) */
        for(i=6;i<=N;i+=7)
            hartal[i] = true;
        for(i=7;i<=N;i+=7)
            hartal[i] = true;
        /* start to traverse */
        for(i=2;i<=N;++i){
            if(hartal_period[i]){
                for(j=1;i*j<=N;++j){
                    if(!hartal[i*j]){
                        hartal[i*j] = true;
                        ++count;
                    }
                }
            }
        }
        printf("%d\n",count);
    }
    return 0;

}