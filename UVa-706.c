/* UVa 10189 - Minesweeper
#		        Problem	    Verdict	    Language	Run Time	Submission Date
24754359	706	LC-Display	Accepted	ANSI C   	0.010	    2020-03-24 11:52:13

可以參考 https://blog.csdn.net/mobius_strip/article/details/28506537 改進
*/


#include <stdio.h>
#include <string.h>

/* * * * * * * * * * * * * 
* 7 positions of a digit *
*                        *
*         -              *
*  0 ->  | |  <- 5       *
*         -              *
*  1 ->  | |  <- 6       *
*         -              *
*                        *
*         ^              *
*         |              *
*                        *
*       2,3,4            *
* * * * * * * * * * * * */

int display[10][7] = {
    {1,1,1,0,1,1,1},    /* 0 */
    {0,0,0,0,0,1,1},    /* 1 */
    {0,1,1,1,1,1,0},
    {0,0,1,1,1,1,1},
    {1,0,0,1,0,1,1},
    {1,0,1,1,1,0,1},
    {1,1,1,1,1,0,1},
    {0,0,1,0,0,1,1},
    {1,1,1,1,1,1,1},
    {1,0,1,1,1,1,1}     /* 9 */
};

int main()
{
    int s;
    char n[10],digit;
    int i,row,column,pos;

    while(scanf("%d %s",&s,n) && s){
        char output[2*s+3][strlen(n)*(s+2+1)];  /* +1 is for the blank between digits */
        memset(output,' ',sizeof(output));
        for (i=0;i<strlen(n);++i){
            digit = n[i]-'0';
            for (pos=0;pos<7;++pos){
                if (display[digit][pos]){   /* check which 7 positions to be displayed*/
                    switch(pos){
                        case 0: /* position 0 */
                            for(row=1;row<s+1;++row)
                                output[row][i*(s+2+1)]='|';
                            break;
                        case 1:
                            for(row=s+2;row<2*s+2;++row)
                                output[row][i*(s+2+1)]='|';
                            break;
                        case 2:
                            for(column=1;column<s+1;++column)
                                output[0][i*(s+2+1)+column]='-';
                            break;
                        case 3:
                            for(column=1;column<s+1;++column)
                                output[s+1][i*(s+2+1)+column]='-';
                            break;
                        case 4:
                            for(column=1;column<s+1;++column)
                                output[2*s+2][i*(s+2+1)+column]='-';
                            break;
                        case 5:
                            for(row=1;row<s+1;++row)
                                output[row][i*(s+2+1)+(s+1)]='|';
                            break;
                        case 6:
                            for(row=s+2;row<2*s+2;++row)
                                output[row][i*(s+2+1)+(s+1)]='|';
                            break;
                    }
                }
            }
        }
            
        for (row=0;row<2*s+3;++row){    /* display the lcd */
            for (column=0;column<strlen(n)*(s+2+1)-1;++column){
                printf("%c",output[row][column]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}