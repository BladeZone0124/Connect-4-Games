#include <stdio.h>
#define BOARD_SIZE_HORIZ 7
#define BOARD_SIZE_VERT 6

int main()
{
    int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = {{0}};
    
    board[1][0]=1;
    board[0][5]=2;
    
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
    printf( "  1   2   3   4   5   6   7\n" );
    
    return 0;
}
