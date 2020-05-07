/* UVa 10149 - Yahtzee
#		            Problem	Verdict	    Language	Run Time	Submission Date
24992407	10149	Yahtzee	Accepted	ANSI C	    0.090	    2020-05-07 11:17:51

這題的思路是先從 category 1 dp 到 13，為每個 category 找適合的 round。原本我一開始是從 round 1 dp 到 round 13 ，但是這樣 bonus 部分很難計算
我這題卡了將近一天，主要是因為是要額外去判斷是否要有 bonus，因此不是單純的 DP 而已: (因為同樣的 mask 時，有的可以有 bonus，有的無法)
1. 76 行附近時不能單純的用 DP，因為當 depth<6 時，需要重新計算(直接 return 的話，bonus 會算錯)
2. 101 行附近時需要判斷是否要更新 VALUE[mask] 的值(當 depth 小於 6 時需要去判斷)
*/

#include <stdio.h>
#include <string.h>

#define MASK_MAX 8192   /* 1<< 13*/

int DICE[13][7];    /* DICE[][0] is not used */
int SCORE[13][14];   /* SCORE[][0] is not used */
int VALUE[MASK_MAX];
int WHO[MASK_MAX];
int BONUS[6];

void score()
{
    int i,j;
    int full_house;
    for(i=0;i<13;++i){
        /* category 1~7 */
        for(j=0;j<6;++j){
            SCORE[i][j] = DICE[i][j]*(j+1); /* category 1~6 */
            SCORE[i][6] += SCORE[i][j]; /* category 7 */
        }
        /* category 8~10 */
        for(j=0;j<6;++j){
            if(DICE[i][j] == 3){
                SCORE[i][7] = SCORE[i][6];
                break;
            }else if(DICE[i][j] == 4){
                SCORE[i][8] = SCORE[i][6];
                break;
            }else if(DICE[i][j] == 5){
                SCORE[i][9] = 50;
                break;
            }
        }
        /* category 11~12 */
        if(DICE[i][2] && DICE[i][3]){
            if(DICE[i][0] && DICE[i][1]){
                if(DICE[i][4])
                    SCORE[i][11] = 35;   /* category 12: long straight */
                SCORE[i][10] = 25;  /* shot straight */
            }else if(DICE[i][1] && DICE[i][4]){
                if(DICE[i][5])
                    SCORE[i][11] = 35;   /* category 12: long straight */
                SCORE[i][10] = 25;  /* shot straight */
            }else if(DICE[i][4] && DICE[i][5]){
                SCORE[i][10] = 25;  /* shot straight */
            }
        }
        /* category 13 */
        full_house = 0;
        for(j=0;j<6;++j){
            if(DICE[i][j] == 2)
                ++full_house;
            else if(DICE[i][j] == 3)
                full_house += 4;
        }
        if(full_house == 5)
            SCORE[i][12] = 40;
    }
}

int dp(int mask, int depth)
{
    if(depth == 13)
        return 0;
    if(depth > 5 && VALUE[mask] != -1)
        return VALUE[mask];
    int i,j;
    int new_mask;
    int result, who, sum, max = -1;
    for(i=0;i<13;++i){
        if((mask & (1<<i)) == 0){
            new_mask = mask | (1<<i);
            if(depth<6)
                BONUS[depth] = SCORE[i][depth];
            result = SCORE[i][depth] + dp(new_mask, depth+1);
            if(depth == 5){
                sum = 0;
                for(j=0;j<6;++j)
                    sum += BONUS[j];
                if(sum >= 63){
                    result += 35;
                }
            }
            if(result > max){
                max = result;
                who = i;
            }
        }
    }
    if(max > VALUE[mask]){  /* when depth<6, you have to check wethere to overwrite (actually, dont' need to check for depth >=6) */
        VALUE[mask] = max;
        WHO[mask] = who;
    }
    return max;
}

void print_result()
{
    int i;
    int mask = 0;
    int output[15];
    int who, sum;
    for(i=0;i<13;++i){
        who = WHO[mask];
        output[i] = SCORE[who][i];
        mask = mask | (1<<who);
    }
    sum = 0;
    for(i=0;i<6;++i)
        sum += output[i];
    if(sum >= 63)
        output[13] = 35;
    else
        output[13] = 0;
    sum = 0;
    for(i=0;i<14;++i)
        sum += output[i];
    output[14] = sum;
    for(i=0;i<14;++i)
        printf("%d ",output[i]);
    printf("%d\n",output[14]);

}

int main()
{
    int i,j;
    int input;
    while(1){
        memset(DICE,0,sizeof(DICE));
        memset(SCORE,0,sizeof(SCORE));
        for(i=0;i<MASK_MAX;++i){
            VALUE[i] = -1;
            WHO[i] = -1;
        }
        for(i=0;i<13;++i){
            for(j=0;j<5;++j){
                if(scanf("%d",&input) == EOF)
                    return 0;
                ++DICE[i][input-1];
            }
        }
        score();
        dp(0,0);
        print_result();
    }
    return 0;
}