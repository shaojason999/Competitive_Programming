/* UVa 843 - Crypt Kicker
#		            Problem         Verdict     Language	Run Time	Submission Date
24984245	843	    Crypt Kicker	Accepted	ANSI C	    0.040	    2020-05-05 15:19:22
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int dict_words;
char dict[1001][20];
int dict_length[1001];
char encrypted[45][85];
int encrypted_count;
char e_to_d[26];    /* decrypt table */
bool used[26];  /* if the plain text alphabet is used */

bool dfs(int cur)
{
    if(cur == encrypted_count)
        return true;

    int i,j;
    char match[20];
    int stack[20];
    int top;
    for(i=0;i<dict_words;++i){
        if(dict_length[i] == strlen(encrypted[cur])){
            strncpy(match,dict[i],sizeof(match));
            top = 0;
            
            for(j=0;j<dict_length[i];++j){
                if(e_to_d[encrypted[cur][j] - 'a'] == 0){
                    if(used[match[j] - 'a'])
                        break;
                    e_to_d[encrypted[cur][j] - 'a'] = match[j];
                    used[match[j] - 'a'] = true;
                    stack[top++] = encrypted[cur][j] - 'a';  /* record the change */
                }else   /* (e_to_d[encrypted[cur][j] - 'a']) */ 
                    if(e_to_d[encrypted[cur][j] - 'a'] != match[j])
                        break;
            }
            if(j== dict_length[i])    /* match succeed */
                if(dfs(cur+1))  /* all match succeed */
                    return true;

            for(j=0;j<top;++j){  /* match failed, so make the e_to_d[] restored */
                used[e_to_d[stack[j]] - 'a'] = false;
                e_to_d[stack[j]] = false;
            }
        }
    }
    return false;
}

void print_result(int result)
{
    int i,j;
    for(i=0;i<encrypted_count;++i){
        for(j=0;encrypted[i][j];++j){
            if(result)
                printf("%c",e_to_d[encrypted[i][j] - 'a']);
            else
                printf("*");
        }
        if(i != encrypted_count-1)
            printf(" ");
    }
    printf("\n");
}

int main()
{
    int i,j;
    int result;
    char input;
    scanf("%d",&dict_words);
    for(i=0;i<dict_words;++i){
        scanf("%s",dict[i]);
        dict_length[i] = strlen(dict[i]);
    }
    while(getchar() != '\n');
    i = 0;
    encrypted_count = 0;
    while(scanf("%c",&input) != EOF){
        if(input == ' '){
            encrypted[encrypted_count++][i] = '\0';
            i = 0;
        }else if(input == '\n'){
            memset(e_to_d,0,sizeof(e_to_d));
            memset(used,0,sizeof(used));
            encrypted[encrypted_count++][i] = '\0';
            result = dfs(0);
            /* show the result */
            print_result(result);
            
            encrypted_count = 0;
            i = 0;
        }else{
            encrypted[encrypted_count][i++] = input;
        }
    }
    return 0;
}