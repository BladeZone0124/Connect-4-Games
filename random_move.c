#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define BOARD_SIZE_HORIZ 7
#define BOARD_SIZE_VERT 6

bool is_column_full(int board[][BOARD_SIZE_VERT],int m)
{
    if( board[m-1][0] == 1 || board[m-1][0] == 2 )
        return true;
    else
        return false;
}

void update_board(int board[][BOARD_SIZE_VERT],int m,int player_num)
{
    int i=5;
    
    while ( board[m-1][i]!=0 )
        i--;
    
    board[m-1][i] = player_num;
}

int main()
{
    int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};
    
    int player_num = 1;
    int computer_num = 2;
    
    for ( int i=0; i<BOARD_SIZE_VERT; i++ )
    {
        board[1][i] = 1;
        board[2][i] = 2;
        board[3][i] = 2;
        board[0][i] = 2;
    }
    
    board[4][5] = 1;
    board[5][5] = 1;
    board[5][4] = 1;
    board[6][5] = 1;
    board[6][4] = 1;
    board[6][3] = 1;
    
    srand(time(0));
    int num = 0;
    do
    {
        num = rand();
    }while( !(num>=1 && num<=BOARD_SIZE_HORIZ) || is_column_full(board, num) );
    
    printf( "%d\n", num );
    
    update_board( board, num, computer_num );
    
    printf( "%d %d %d\n", board[4][4], board[5][3], board[6][2] );
    
    //Player
    int i;
    int input;
    int check_vaild = 0;
    char move[30];
    
    do
    {
        i=0;
        printf( "Please enter your move: " );
        while((move[i] = getchar())!='\n')
            i++ ;

        //check user's input
        for( input=1; input<=BOARD_SIZE_HORIZ; input++ )
        {
            if( (move[0]-'0')==input && i==1)
            {
                check_vaild = 1;
                break;
            }
        }
    
        if ( check_vaild == 0 )
            printf( "Not a valid move. Enter a column number!\n" );
        else if ( is_column_full(board, input) )
        {
            check_vaild = 0;
            printf( "This column is full. Try again!\n" );
        }
    }while( check_vaild != 1 );
       
    update_board( board, input, player_num );
    printf( "%d %d %d\n", board[4][4], board[5][3], board[6][2] );
    
    
    return 0;
}
