/* UVa 10038 - Jolly Jumpers
#		            Problem	        Verdict	    Language	Run Time	Submission Date
24973024	10038	Jolly Jumpers	Accepted	ANSI C	    0.000	    2020-05-03 08:00:58
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    int n;
    int i;
    int diff, mask;
    while(scanf("%d",&n) != EOF){
        int input[n];
        bool jolly[n];
        memset(jolly,0,sizeof(bool)*n);
        for(i=0;i<n;++i)
            scanf("%d",&input[i]);
        for(i=1;i<n;++i){
            diff = input[i] - input[i-1];
            mask = diff>>31;    /* absolute value */
            diff = (diff + mask) ^ mask;
            if(diff>=n || diff<1 || jolly[diff])
                break;
            else
                jolly[diff] = true;
        }
        if(i==n)
            printf("Jolly\n");
        else
            printf("Not jolly\n");
    }
    return 0;
}