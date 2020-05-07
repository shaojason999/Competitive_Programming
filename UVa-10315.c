/* UVa 10315 - Poker Hands
#		            Problem	        Verdict	    Language	Run Time	Submission Date
24973420	10315	Poker Hands	    Accepted	ANSI C	    0.000	    2020-05-03 09:45:52
*/

#include <stdio.h>
#include <string.h>

char VALUE[13] = {"23456789TJQKA"};
char SUIT[4] = {"CDHS"};

int value(char a)
{
    int i;
    for(i=0;i<13;++i)
        if(VALUE[i] == a)
            return i;
}

int suit(char a)
{
    int i;
    for(i=0;i<4;++i)
        if(SUIT[i] == a)
            return i;
}

/* rank: high card(0), pair(1), two pairs(2), three of a kind(3), straight(4), flush(5), full house(6), four of a kind(7), straight flush(8) */
int get_rank(int *value, int *suit)
{
    int i;
    int flush = 0, three = 0, two = 0;
    /* check flush */
    for(i=0;i<4;++i)
        if(suit[i] == 5)
            flush = 1;
    /* check others */
    for(i=0;i<13;++i){
        if(value[i] == 4){
            return 7;   /* four of a kind */
        }else if(value[i] == 3){
            three = 1;
        }else if(value[i] == 2){
            ++two;
        }else if(i<9 && value[i] == 1){
            if(value[i+1]==1 && value[i+2]==1 && value[i+3] == 1 && value[i+4]==1){
                if(flush)
                    return 8;   /* straight flush */
                return 4;   /* straight */
            }
        }
    }
    /* return rank*/
    if(three){
        if(two)
            return 6;   /* full house */
        return 3;   /* three of a kind */
    }else if(two){
        if(two == 2)
            return 2;   /* two pairs */
        return 1;   /* pair */
    }else if(flush){
        return 5;   /* flush */
    }else
        return 0;   /* high card */

}

int highest(int *B_value, int *W_value, int count)
{
    int i;
    for(i=12;i>=0;--i)
        if(B_value[i] != W_value[i]){   /* find the highest different value */
            if(B_value[i] == count)    /* and one of the value must be count */
                return 0;
            else if(W_value[i] == count)
                return 1;
            else
                continue;   /* keep finding */
        }
    return 2;   /* tie */
}

/* rank: high card(0), pair(1), two pairs(2), three of a kind(3), straight(4), flush(5), full house(6), four of a kind(7), straight flush(8) */
int who_is_higher(int *B_value, int *W_value, int rank)
{
    int i;
    int result;
    if(rank==0 || rank==4 || rank==5 || rank==8)
        return highest(B_value,W_value,1);
    else if(rank==7)
        return highest(B_value,W_value,4);
    else if(rank==3 || rank==6)
        return highest(B_value,W_value,3);
    else if(rank==1 || rank==2){
        result = highest(B_value,W_value,2);
        if(result != 2) /* not tie */
            return result;
        else
            return highest(B_value,W_value,1);
    }
}

int main()
{
    char input[50];
    int B_value[13], W_value[13];
    int B_suit[4], W_suit[4];
    int i;
    int B_rank, W_rank;
    int winner;
    while(fgets(input,sizeof(input),stdin) != NULL){
        memset(B_value,0,sizeof(B_value));
        memset(W_value,0,sizeof(W_value));
        memset(B_suit,0,sizeof(B_suit));
        memset(W_suit,0,sizeof(W_suit));
        for(i=0;i<5;++i){
            ++B_value[value(input[i*3])];
            ++B_suit[suit(input[i*3+1])];
        }
        for(i=5;i<10;++i){
            ++W_value[value(input[i*3])];
            ++W_suit[suit(input[i*3+1])];
        }
        B_rank = get_rank(B_value,B_suit);
        W_rank = get_rank(W_value,W_suit);

        if(B_rank>W_rank){
            winner = 0;
        }else if(W_rank>B_rank){
            winner = 1;
        }else{
            winner = who_is_higher(B_value,W_value,B_rank);
        }

        if(winner == 0)
            printf("Black wins.\n");
        else if(winner == 1)
            printf("White wins.\n");
        else
            printf("Tie.\n");
    }
    return 0;

}