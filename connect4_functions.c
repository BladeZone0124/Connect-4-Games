
/******************************************************************************
 *
 * File name:
 *
 * Author:  Chong Gu
 *          A14464757
 *          chg056@ucsd.edu
 *
 *
 *     Lab #:4
 * Problem #:1
 *
 * Submission Date: Dec 6,2017
 *
 ******************************************************************************/


#include "connect4_functions.h"

//Reset predicted board
void reset( int predictedBoard[][BOARD_SIZE_VERT], int board[][BOARD_SIZE_VERT] );
//Check whether the last move can make connect 3 in horizontal direction
int check_connect3_horiz(int board[][BOARD_SIZE_VERT], int last_move);
//Check whether the last move can make connect 3 in vertical and diagonal direction
int check_connect3_other(int board[][BOARD_SIZE_VERT], int last_move);
//Reset no_touch array
void reset_no_touch( int* no_touch );

int print_welcome(void)
{
    int i = 0;
    char response[30];
    
    printf("*** Welcome to the Connect-Four game!!! ***\n");
    printf("Would you like to make the first move [y/n]: ");
    
    while((response[i] = getchar())!='\n')
        i++ ;
    
    printf( "\n" );
    if ( (response[0] == 'n' || response[0] == 'N') && i==1 )
        return 2;
    else
        return 1;
}

void display_board(int board[][BOARD_SIZE_VERT])
{
    printf( "\n" );
    for ( int i=0; i< BOARD_SIZE_VERT; i++ )
    {
        printf( "+---+---+---+---+---+---+---+\n" );
        printf( "|" );
        for (int j=0; j<BOARD_SIZE_HORIZ; j++ )
        {
            switch( board[j][i] )
            {
                case 0:
                    printf( "   |" );
                    break;
                case 1:
                    printf( " X |" );
                    break;
                case 2:
                    printf( " O |" );
                    break;
                default:
                    printf( "   |" );
            }
        }
        printf("\n");
    }
    printf( "+---+---+---+---+---+---+---+\n" );
    printf( "  1   2   3   4   5   6   7\n\n" );
}

int random_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
    srand(time(0));
    int num = 0;
    do
    {
        num = rand();
    }while( !(num >= 1 && num < BOARD_SIZE_HORIZ+1 ) || is_column_full(board, num) );
    
    update_board( board, num, computer_num );
    
    return num;
}

int player_move(int board[][BOARD_SIZE_VERT], int player_num)
{
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
            printf( "This column is full. Try again!.\n" );
        }
    }while( check_vaild != 1 );
    
    update_board( board, input, player_num );
    
    return input;
}

bool check_win_or_tie(int board[][BOARD_SIZE_VERT], int last_move)
{
    int board_full = 1;
    for ( int i=1; i<=BOARD_SIZE_HORIZ; i++ )
    {
        if( !is_column_full( board, i)  )
            board_full = 0;
    }
    if( check_winner(board, last_move) == 1 )
    {
        printf( "*****************************\n" );
        printf( "* Player X won!!! Game over *\n" );
        printf( "*****************************\n" );
        return true;
    }
    else if( check_winner(board, last_move) == 2 )
    {
        printf( "*****************************\n" );
        printf( "* Player O won!!! Game over *\n" );
        printf( "*****************************\n" );
        return true;
    }
    else if ( board_full == 1 )
    {
        printf( "*****************************\n" );
        printf( "* Game is a tie!! No winner *\n" );
        printf( "*****************************\n" );
        return true;
    }
    else
        return false;
}

int check_winner(int board[][BOARD_SIZE_VERT], int last_move)
{
    int col_index=last_move-1;
    int row_index=5;
    int count_horiz = 1;
    int count_vert = 1;
    int count_diag1 = 1;
    int count_diag2 = 1;
    int i, j;
    
    //get the position of the last move
    while( row_index != 0 && board[col_index][row_index-1] != 0 )
        row_index--;
    
    int who_win = board[col_index][row_index]; //1 is X, 2 is O
    //printf( "[%d][%d]\n",col_index, row_index );
    
    //check horizontal
    i = col_index;
    j = row_index;
    while( i!=0 && board[i-1][j]== who_win )
    {
        count_horiz++;
        i--;
    }
    i = col_index;
    j = row_index;
    while( i!=BOARD_SIZE_HORIZ-1 && board[i+1][j]== who_win )
    {
        count_horiz++;
        i++;
    }
    
    //check vertical
    i = col_index;
    j = row_index;
    while( j!=0 && board[i][j-1]== who_win )
    {
        count_vert++;
        j--;
    }
    i = col_index;
    j = row_index;
    while( j!=BOARD_SIZE_VERT-1 && board[i][j+1]==who_win )
    {
        count_vert++;
        j++;
    }
    
    //check diagonal
    i = col_index;
    j = row_index;
    while( i!=0 && j!=0 && board[i-1][j-1]==who_win )
    {
        count_diag1++;
        i--;
        j--;
    }
    i = col_index;
    j = row_index;
    while( i!=BOARD_SIZE_HORIZ-1 && j!=BOARD_SIZE_VERT-1 && board[i+1][j+1]==who_win )
    {
        count_diag1++;
        i++;
        j++;
    }
    
    i = col_index;
    j = row_index;
    while( i!=0 && j!=BOARD_SIZE_VERT-1 && board[i-1][j+1]==who_win )
    {
        count_diag2++;
        i--;
        j++;
    }
    i = col_index;
    j = row_index;
    while( i!=BOARD_SIZE_HORIZ-1 && j!=0 && board[i+1][j-1]==who_win )
    {
        count_diag2++;
        i++;
        j--;
    }
    
    if( (count_horiz>=4 || count_vert>=4 || count_diag1>=4 || count_diag2>=4) && who_win == 1 )
        return 1;
    else if( (count_horiz>=4 || count_vert>=4 || count_diag1>=4 || count_diag2>=4) && who_win >= 2 )
        return 2;
    else
        return 0;
}

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

int best_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int bestMove=4;
    int nextMove=4;
    int player_num;
    if( computer_num == 1 )
        player_num = 2;
    else
        player_num = 1;
    
    int predictedBoard [BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};
    int predictedBoard_next [BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};
    
    int no_touch [BOARD_SIZE_HORIZ]={0};
    
    reset( predictedBoard, board );
    
    //If computer can win, then choose that move
    for( int x=0; x<BOARD_SIZE_HORIZ; x++ )
    {
        reset( predictedBoard, board );
        bestMove = x+1;
        
        if( is_column_full(predictedBoard, bestMove) )
            continue;
        
        update_board( predictedBoard, bestMove, computer_num );
        if( check_winner(predictedBoard, bestMove) == computer_num )
        {
            update_board( board, bestMove, computer_num );
            //printf("WIN!!!!!\n");
            return bestMove;
        }
    }
    
    //If player will win in next step, stop it
    for( int x=0; x<BOARD_SIZE_HORIZ; x++ )
    {
        reset( predictedBoard, board );
        bestMove = x+1;
        
        if( is_column_full(predictedBoard, bestMove) )
            continue;
        
        update_board( predictedBoard, bestMove, player_num );
        if( check_winner(predictedBoard, bestMove) == player_num )
        {
            update_board( board, bestMove, computer_num );
            //printf("STOP!!!!!\n");
            return bestMove;
        }
    }
    
    //If player will connect 3 in horizontal, stop it
    for( int x=0; x<BOARD_SIZE_HORIZ; x++ )
    {
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
        bestMove = x+1;
        
        if( is_column_full(predictedBoard, bestMove) )
            continue;
        
        
        //Check whether this move causes loses game or chance of win
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        update_board( predictedBoard, bestMove, player_num );

        if( check_connect3_horiz(predictedBoard, bestMove) == player_num && no_touch[bestMove-1]==0 )
        {
            update_board( board, bestMove, computer_num );
            //printf("Stop 3 Horiz!!\n");
            return bestMove;
        }
    }
    
    //If computer can connect 3, then choose that move
    for( int x=0; x<BOARD_SIZE_HORIZ; x++ )
    {
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
        bestMove = x+1;
        
        if( is_column_full(predictedBoard, bestMove) )
            continue;
        
        //Check whether this move causes loses game or chance of win
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        update_board( predictedBoard, bestMove, computer_num );
        if( check_connect3_other(predictedBoard, bestMove) == computer_num && no_touch[bestMove-1]==0 )
        {
            update_board( board, bestMove, computer_num );
            //printf("Connect 3!!\n");
            return bestMove;
        }
    }
    
    //If player will connect 3 in vertical and diagonal, stop it
    for( int x=0; x<BOARD_SIZE_HORIZ; x++ )
    {
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
        bestMove = x+1;
        
        if( is_column_full(predictedBoard, bestMove) )
            continue;
        
        //Check whether this move causes loses game or chance of win
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        update_board( predictedBoard, bestMove, player_num );
        
        if( check_connect3_other(predictedBoard, bestMove) == player_num && no_touch[bestMove-1] == 0 )
        {
            update_board( board, bestMove, computer_num );
            //printf("Stop 3 Other!!\n");
            return bestMove;
        }
    }
    
    
    //printf("Take Best!!\n");
    bestMove = 4;
    reset( predictedBoard, board );
    reset_no_touch( no_touch );
    if( !is_column_full(board, bestMove) )
    {
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        if(no_touch[bestMove-1]==0)
        {
            update_board( board, bestMove, computer_num );
            return bestMove;
        }
        else
        {
            bestMove = 3;
            reset( predictedBoard, board );
            reset_no_touch( no_touch );
        }
    }
    else
    {
        bestMove = 3;
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
    }
    
    if( !is_column_full(board, bestMove) )
    {
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
               // printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        if(no_touch[bestMove-1]==0)
        {
            update_board( board, bestMove, computer_num );
            return bestMove;
        }
        else
        {
            bestMove = 5;
            reset( predictedBoard, board );
            reset_no_touch( no_touch );
        }
    }
    else
    {
        bestMove = 5;
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
    }
    
    if( !is_column_full(board, bestMove) )
    {
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
               // printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        if(no_touch[bestMove-1]==0)
        {
            update_board( board, bestMove, computer_num );
            return bestMove;
        }
        else
        {
            bestMove = 2;
            reset( predictedBoard, board );
            reset_no_touch( no_touch );
        }
    }
    else
    {
        bestMove = 2;
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
    }
    
    if( !is_column_full(board, bestMove) )
    {
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
               //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        if(no_touch[bestMove-1]==0)
        {
            update_board( board, bestMove, computer_num );
            return bestMove;
        }
        else
        {
            bestMove = 6;
            reset( predictedBoard, board );
            reset_no_touch( no_touch );
        }
    }
    else
    {
        bestMove = 6;
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
    }
    
    if( !is_column_full(board, bestMove) )
    {
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
             //   printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        if(no_touch[bestMove-1]==0)
        {
            update_board( board, bestMove, computer_num );
            return bestMove;
        }
        else
        {
            bestMove = 1;
            reset( predictedBoard, board );
            reset_no_touch( no_touch );
        }
    }
    else
    {
        bestMove = 1;
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
    }
    
    if( !is_column_full(board, bestMove) )
    {
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        if(no_touch[bestMove-1]==0)
        {
            update_board( board, bestMove, computer_num );
            return bestMove;
        }
        else
        {
            bestMove = 7;
            reset( predictedBoard, board );
            reset_no_touch( no_touch );
        }
    }
    else
    {
        bestMove = 7;
        reset( predictedBoard, board );
        reset_no_touch( no_touch );
    }
    
    
    if( !is_column_full(board, bestMove) )
    {
        for( int y=0; y<BOARD_SIZE_HORIZ; y++ )
        {
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            nextMove = y+1;
            
            if(is_column_full(predictedBoard_next, nextMove))
                continue;
            //Check if causing lose
            update_board( predictedBoard_next, nextMove, player_num );
            if( check_winner(predictedBoard_next, nextMove) == player_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
            //Check if losing chance of win
            reset( predictedBoard_next, predictedBoard );
            update_board( predictedBoard_next, bestMove, computer_num );
            update_board( predictedBoard_next, nextMove, computer_num);
            if( check_winner(predictedBoard_next, nextMove) == computer_num )
            {
                //printf("Set No Touch!!\n");
                no_touch[y] = 1;
            }
        }
        
        if(no_touch[bestMove-1]==0)
        {
            update_board( board, bestMove, computer_num );
            return bestMove;
        }
    }
    
    //printf("No Way!!!!\n");
    srand(time(0));
    int num = 0;
    do
    {
        num = rand();
    }while( !(num>=1 && num<=BOARD_SIZE_HORIZ) || is_column_full(board, num) );
    
    update_board( board, num, computer_num );
    
    return num;
    
}

//Reset predicted board
void reset( int predictedBoard[][BOARD_SIZE_VERT], int board[][BOARD_SIZE_VERT] )
{
    for( int i=0; i< BOARD_SIZE_VERT; i++ )
    {
        for( int j=0; j<BOARD_SIZE_HORIZ; j++ )
        {
            predictedBoard[j][i] = board[j][i];
        }
    }
}

int check_connect3_horiz(int board[][BOARD_SIZE_VERT], int last_move)
{
    int col_index=last_move-1;
    int row_index=5;
    int count_horiz = 1;
    int i, j;
    
    //get the position of the last move
    while( row_index != 0 && board[col_index][row_index-1] != 0 )
        row_index--;
    
    int who_win = board[col_index][row_index]; //1 is X, 2 is O
    //printf( "[%d][%d]\n",col_index, row_index );
    
    //check horizontal
    i = col_index;
    j = row_index;
    while( i!=0 && board[i-1][j]== who_win )
    {
        count_horiz++;
        i--;
    }
    i = col_index;
    j = row_index;
    while( i!=BOARD_SIZE_HORIZ-1 && board[i+1][j]== who_win )
    {
        count_horiz++;
        i++;
    }
    
    
    if( count_horiz==3 && who_win == 1 )
        return 1;
    else if( count_horiz==3  && who_win == 2 )
        return 2;
    else
        return 0;
}

int check_connect3_other(int board[][BOARD_SIZE_VERT], int last_move)
{
    int col_index=last_move-1;
    int row_index=5;
    int count_vert = 1;
    int count_diag1 = 1;
    int count_diag2 = 1;
    int i, j;
    
    //get the position of the last move
    while( row_index != 0 && board[col_index][row_index-1] != 0 )
        row_index--;
    
    int who_win = board[col_index][row_index]; //1 is X, 2 is O
    //printf( "[%d][%d]\n",col_index, row_index );
    
    //check vertical
    i = col_index;
    j = row_index;
    while( j!=0 && board[i][j-1]== who_win )
    {
        count_vert++;
        j--;
    }
    i = col_index;
    j = row_index;
    while( j!=BOARD_SIZE_VERT-1 && board[i][j+1]==who_win )
    {
        count_vert++;
        j++;
    }
    
    //check diagonal
    i = col_index;
    j = row_index;
    while( i!=0 && j!=0 && board[i-1][j-1]==who_win )
    {
        count_diag1++;
        i--;
        j--;
    }
    i = col_index;
    j = row_index;
    while( i!=BOARD_SIZE_HORIZ-1 && j!=BOARD_SIZE_VERT-1 && board[i+1][j+1]==who_win )
    {
        count_diag1++;
        i++;
        j++;
    }
    
    i = col_index;
    j = row_index;
    while( i!=0 && j!=BOARD_SIZE_VERT-1 && board[i-1][j+1]==who_win )
    {
        count_diag2++;
        i--;
        j++;
    }
    i = col_index;
    j = row_index;
    while( i!=BOARD_SIZE_HORIZ-1 && j!=0 && board[i+1][j-1]==who_win )
    {
        count_diag2++;
        i++;
        j--;
    }
    
    if( ( count_vert==3 || count_diag1==3 || count_diag2==3) && who_win == 1 )
        return 1;
    else if( ( count_vert==3 || count_diag1==3 || count_diag2==3) && who_win == 2 )
        return 2;
    else
        return 0;
}

void reset_no_touch( int* no_touch )
{
    for(int i=0; i<BOARD_SIZE_HORIZ; i++ )
        no_touch[i]=0;
}



