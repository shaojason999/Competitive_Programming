/* UVa 706 - LC-Display
#		            Problem	    Verdict	    Language	Run Time	Submission Date
24737924	10137	The Trip	Accepted	ANSI C	    0.000	    2020-03-21 13:28:01

# 小數點處理的超煩，解這題超花時間
*/

#include <stdio.h>
#include <math.h>

float round_digit(float input, int digit)
{
    input = input * pow(10,digit);
    input = round(input) / pow(10,digit);
    return input;
}

int main()
{
    int n;
    int i;
    double money[1005],sum,avg,diff_big,diff_small;
    int int_avg,int_rem;

    while(scanf("%d",&n) && n){
        sum=0,diff_big=0,diff_small=0;

        for (i=0;i<n;++i){
            scanf("%lf",&money[i]);
            sum += money[i];
        }

        avg = ((double)(int)(sum*100/n+0.5))/100;

        for (i=0;i<n;++i){
            if (money[i]>avg)
                diff_big += money[i]-avg;
            else
                diff_small += avg-money[i];
        }
        printf("$%.2lf\n",diff_big<diff_small?diff_big:diff_small);

    }
    return 0;

}