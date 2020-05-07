/* UVa 10189 - Minesweeper
#		        Problem	            Verdict	    Language	Run Time	Submission Date
24726894	100	The 3n + 1 problem	Accepted	ANSI C	    0.280	    2020-03-19 14:59:50

*/

#include <stdio.h>

int main()
{
    int a,b,small,big;
    int i,n;
    int count,max;

    while(scanf("%d %d",&a,&b)!=EOF){   //must write !=EOF
        max=-1;

        if(a>b) //find the small one
            small=b,big=a;
        else
            small=a,big=b;

        for(i=small;i<=big;++i){    //calu over all integers between and including small and big
            n=i;
            count = 1;

            while(n!=1){    //odd or even
                if(n&1)
                    n=n*3+1;
                else
                    n>>=1;
                count+=1;
            }

            if(count>max)   //max one between small and big
                max=count;
        }
        printf("%d %d %d\n",a,b,max);

    }
    return 0;   //must write return=0;
}