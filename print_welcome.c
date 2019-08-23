#include <stdio.h>

int main()
{
    int i = 0;
    char response[30];
    
    printf("*** Welcome to the Connect Four game!!! ***\n");
    printf("Would you like to make the first move [y/n]: ");
    
    while((response[i] = getchar())!='\n')
        i++ ;
    
    printf( "%s",  response );
    
    if ( (response[0] == 'n' || response[0] == 'N') && i==1 )
        printf ( "2\n" );
    else
        printf ( "1\n" );
    
    return 0;
}
