/* UVa 10010 - Where's Waldorf?
#		            Problem             Verdict     Language    Run Time    Submission Date
25101112    10010   Where's Waldorf?    Accepted    ANSI C      0.000       2020-06-03 13:39:26
*/

#include <stdio.h>
#include <string.h>

#define MAP_SIZE 60

int direct_x[8] = {1,1,0,-1,-1,-1,0,1};
int direct_y[8] = {0,1,1,1,0,-1,-1,-1};

void check_match(int m, int n, char map[MAP_SIZE][MAP_SIZE], char *match)
{
    int i,j,d,k;
    int match_len;

    match_len = strlen(match);
    for(i=1;i<=m;++i)
        for(j=1;j<=n;++j){
            for(d=0;d<8;++d){   /* check 8 directions */
                for(k=0;k<match_len;++k)
                    if(match[k] != map[i+k*direct_y[d]][j+k*direct_x[d]])
                        break;
                if(k==match_len){
                    printf("%d %d\n",i,j);
                    return;
                }
            }
        }
}

int main()
{
    int cases,m,n,k;
    int i,j;
    char map[MAP_SIZE][MAP_SIZE];

    scanf("%d",&cases);
    while(cases--){
        memset(map,0,sizeof(map));
        scanf("%d %d",&m,&n);
        for(i=1;i<=m;++i){
            scanf("%s",map[i]+1);
            for(j=1;j<=n;++j)
                map[i][j] |= 32;    /* transfer to lower case */
        }

        scanf("%d",&k);
        char match[k][50];
        for(i=0;i<k;++i){
            scanf("%s",match[i]);
            for(j=0;match[i][j];++j)
                match[i][j] |= 32;  /* transfer to lower case */
        }

        for(i=0;i<k;++i)
            check_match(m,n,map,match[i]);

        if(cases)
            printf("\n");
    }
    return 0;


}