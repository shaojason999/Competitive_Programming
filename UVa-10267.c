/* UVa 10137 - The Trip
#		            Problem	            Verdict	    Language	Run Time	Submission Date
24765101	10267	Graphical Editor	Accepted	ANSI C	    0.000	    2020-03-26 06:13:46

# 注意輸入的 x,y 不是照大小輸入
# 其中 F 指令的意思是把"相鄰"同顏色區塊都轉換成顏色 C (相鄰的定義為上下左右，不包括斜角線)
# 無須檢查邊界，因為我把邊界外多加一層，顏色設成 '@'。F 指令時可以直接檢查邊界外顏色，而且不會跟任何顏色相同
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* #define SWAP(x,y) {typeof(x) t=x, x=y, y=t;} // UVa compilation may fail
or #define SWAP(x,y) {typeof(x) t; t=x, x=y, y=t;} */
#define SWAP(x,y) {x^=y, y^=x, x^=y;}
/* or #define SWAP(x,y) {x=x+y; y=x-y; x=x-y;} */

char table[260][260];
char RC,C;
struct direction{
    int x,y;
} dir[4] = {{0,-1},{1,0},{0,1},{-1,0}};

void find_4_dirs(int X, int Y)
{
    int new_X,new_Y,i;

    for (i=0;i<4;++i){
        new_X = X + dir[i].x;
        new_Y = Y + dir[i].y;
        if(table[new_Y][new_X] == RC){
            table[new_Y][new_X] = C;
            find_4_dirs(new_X,new_Y);
        }
    }
}

int main()
{
    char F;
    int M,N;
    int i,j;
    int X1,Y1,X2,Y2;
    char name[1000];

    while(scanf("%c",&F)){
        if (F == 'X') {
            break;
        }else if (F == 'I' || F == 'C'){
            if (F == 'I')
                scanf("%d %d",&M,&N);

            /* clear all */
            memset(table,'O',sizeof(table));
            /* boundary set */
            for(j=0;j<M+2;++j)
                table[0][j] = '@';
            for(j=0;j<M+2;++j)
                table[N+1][j] = '@';
            for(i=0;i<N+2;++i)
                table[i][0] = '@';
            for(i=0;i<N+2;++i)
                table[i][M+1] = '@';

        }else if (F == 'L'){
            scanf("%d %d %c",&X1,&Y1,&C);
            table[Y1][X1] = C;
        }else if (F == 'V'){
            scanf("%d %d %d %c",&X1,&Y1,&Y2,&C);
            if(Y1>Y2) SWAP(Y1,Y2);
            for(i=Y1;i<=Y2;++i)
                table[i][X1] = C;
        }else if (F == 'H'){
            scanf("%d %d %d %c",&X1,&X2,&Y1,&C);
            if(X1>X2) SWAP(X1,X2);
            for(j=X1;j<=X2;++j)
                table[Y1][j] = C;
        }else if (F == 'K'){
            scanf("%d %d %d %d %c",&X1,&Y1,&X2,&Y2,&C);
            if(X1>X2) SWAP(X1,X2);
            if(Y1>Y2) SWAP(Y1,Y2);
            for(i=Y1;i<=Y2;++i)
                for(j=X1;j<=X2;++j)
                    table[i][j] = C;
        }else if (F == 'F'){
            scanf("%d %d %c",&X1,&Y1,&C);
            RC = table[Y1][X1];
            if( RC != C){
                table[Y1][X1] = C;
                find_4_dirs(X1,Y1);
            }
        }else if (F == 'S'){
            scanf("%s",name);
            printf("%s\n",name);
            for (i=1;i<=N;++i){
                for (j=1;j<=M;++j)
                    printf("%c",table[i][j]);
                printf("\n");
            }
        }
    }
    return 0;

}