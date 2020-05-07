/* UVa 10137 - The Trip
#		            Problem	    Verdict	    Language	Run Time	Submission Date
24731537	10189	Minesweeper	Accepted	ANSI C	    0.000	    2020-03-20 14:26:25

# 記得要 return 0; 記得讀取要結束: scanf()!=EOF
# 否則都會錯
*/

#include <stdio.h>
#include <string.h>

int adj[105][105];

/*don't need to check the boundary, because it starts from adj[1][1], not adj[0][0]*/
void adjacent_plus(int i, int j)
{
    ++adj[i-1][j-1];
    ++adj[i-1][j];
    ++adj[i-1][j+1];
    ++adj[i][j-1];
    ++adj[i][j+1];
    ++adj[i+1][j-1];
    ++adj[i+1][j];
    ++adj[i+1][j+1];
}

int main()
{
    int n,m;
    int i,j;
    int filed=1;
    char mine[105][105];

    while(scanf("%d %d",&n,&m) && n && m){
        for(i=0;i<n;++i)
            scanf("%s",mine[i]);

        memset(adj,0,sizeof(adj));

        for(i=0;i<n;++i)
            for(j=0;j<m;++j){
                if(mine[i][j]=='*'){
                    adj[i+1][j+1]=-100; /*represent mine*/
                    adjacent_plus(i+1,j+1); /*the adj[n][m] is started from adj[1][1], so it should be shifted*/
                }
            }

        if(filed > 1)
            printf("\n");
        printf("Field #%d:\n",filed++);
        for(i=1;i<=n;++i){
            for(j=1;j<=m;++j)
                if(adj[i][j]<0)
                    printf("*");
                else
                    printf("%d",adj[i][j]);
            printf("\n");
        }
    }
}