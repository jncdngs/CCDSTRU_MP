// Donguines, Jon Chester C.    S27
// CCDSTRU Machine Project

#include <stdio.h>
#include <conio.h>
#define SIZE 4
#define CLS "\033[H\033[J\033[3J"

// Initializes the board to be empty
//
// @param board     array containing the positions taken
void initBoard(char board[][SIZE])
{
    int i, j;

    for(i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

// Displays the title ASCII art
void displayTitle()
{
    printf(" _   _             ____           _____\n");
    printf("| | | |_ __   ___ |  _ \\  ___  __|_   _| __ ___  ___\n");
    printf("| | | | '_ \\ / _ \\| | | |/ _ \\/ __|| || '__/ _ \\/ __|\n");
    printf("| |_| | | | | (_) | |_| | (_) \\__ \\| || | |  __/\\__ \\\n");
    printf(" \\___/|_| |_|\\___/|____/ \\___/|___/|_||_|  \\___||___/\n\n");
}

// Displays the board and positions of players
//
// @param board     array containing the positions taken
void displayBoard(char board[][SIZE])
{
    int i, j;
    int row = 0;
    
    for(i = 0; i < SIZE * 2 + 2; i++)
    {
        if(i == 0)       // First row
        {
            printf("     ");
            
            for(j = 0; j < SIZE; j++)
                printf("%d   ", j + 1);

            printf("\n");
        }
        else if(i % 2)  // Odd rows
        {
            printf("   ");

            for(j = 0; j < SIZE; j++)
                printf("+---", j + 1);

            printf("+\n");
        }
        else            // Even rows
        {
            printf("%d  ", i / 2);

            for(j = 0; j < SIZE; j++)
            {
                    printf("| %c ", board[row][j]);
            }

            printf("|\n");
            row++;
        }
    }

    printf("\n");
}

// Gets row and column from user and checks if it is valid
//
// @param board     array containing the positions taken
// @param row       address to store the player's row to
// @param col       address to store the player's column to
// @param player    the current player picking a position
void getPos(char board[][SIZE], int *row, int *col, int player)
{
    int valid = 0;
    int error = 0;
    int rowTemp, colTemp;

    while(!valid)
    {
        // Ask user for row
        error = 0;
        do
        {
            if(error)
                printf("\nInvalid!\n\n");
                
            printf("Enter row: ");

            if(scanf("%d", &rowTemp) != 1)
                while(getchar() != '\n');

            error = 1;
        }    
        while(rowTemp < 1 || rowTemp > SIZE);

        // Ask user for column
        error = 0;
        do
        {
            if(error)
            printf("\nInvalid!\n\n");
            
            printf("Enter column: ");

            if(scanf("%d", &colTemp) != 1)
                while(getchar() != '\n');

            error = 1;
        }    
        while(colTemp < 1 || colTemp > SIZE);

        // If player is uno or tres, check if position is valid
        if((player == 1 || player == 3) && (board[rowTemp - 1][colTemp - 1] == ' '))
            valid = 1;
        // If player is dos, check if position is valid
        else if((player == 2) && (board[rowTemp - 1][colTemp - 1] == '1' || board[rowTemp - 1][colTemp - 1] == '3'))
            valid = 1;
        else
            printf("\nInvalid!\n\n");
    }

    *row = rowTemp;
    *col = colTemp;
}

// Checks if the game is over by comparing the board to the patterns
//
// @param board     array containing the positions taken
int isGameOver(char board[][SIZE])
{
    int i, j;
    int over = 0;
    int full = 1;
    char player;

    for(i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++)
            if(board[i][j] == ' ')
                full = 0;
    
    if(full == 1)
        over = 2;
    else
    {
        for(player = '1'; player <= '3'; player += 2)
        {
            if(((board[0][0] == player || board[0][0] == 'X') && 
                (board[0][1] == player || board[0][1] == 'X') && 
                (board[0][2] == player || board[0][2] == 'X') && 
                (board[0][3] == player || board[0][3] == 'X')) || 
    
               ((board[0][0] == player || board[0][0] == 'X') && 
                (board[1][1] == player || board[1][1] == 'X') && 
                (board[2][2] == player || board[2][2] == 'X') && 
                (board[3][3] == player || board[3][3] == 'X')) || 
    
               ((board[0][3] == player || board[0][3] == 'X') && 
                (board[1][2] == player || board[1][2] == 'X') && 
                (board[2][1] == player || board[2][1] == 'X') && 
                (board[3][0] == player || board[3][0] == 'X')) || 
            
               ((board[3][0] == player || board[3][0] == 'X') && 
                (board[3][1] == player || board[3][1] == 'X') && 
                (board[3][2] == player || board[3][2] == 'X') && 
                (board[3][3] == player || board[3][3] == 'X')))
                {
                    over = player - '0';
                    break;
                }
        }
    }

    return over;
}

// Main game function
//
// @param board     array containing the positions taken
int play(char board[][SIZE])
{
    int row = 1;
    int col = 1;

    int turn = 1;
    int go = 0;
    int over = 0;
    
    while(!over)
    {
        printf(CLS);
        displayTitle();
        printf("Choose a slot\n\n");
        displayBoard(board);
        
        if(turn && go)
        {
            printf("It is Uno's turn\n\n");
            getPos(board, &row, &col, 1);
        }
        else if(turn && !go)
        {
            printf("It is Tres's turn\n\n");
            getPos(board, &row, &col, 3);
        }
        else
        {
            printf("It is Dos's turn\n\n");
            getPos(board, &row, &col, 2);
        }

        if(turn && go && board[row - 1][col - 1] == ' ')
        {
            board[row - 1][col - 1] = '1';
            turn = !turn;
            go = !go;
            
        }
        else if(!turn)
        {
            board[row - 1][col - 1] = 'X';
            turn = !turn;
        }
        else if(turn && !go && board[row - 1][col - 1] == ' ')
        {            
            board[row - 1][col - 1] = '3';
            go = !go;            
        }
        
        // Check if game is over
        over = isGameOver(board);
    }

    printf(CLS);
    displayTitle();
    
    // Declare the winner
    displayBoard(board);
    
    if(over == 1)
        printf("\nUno wins!\n\n");
    else if(over == 2)
        printf("\nDos wins!\n\n");
    else if(over == 3)
        printf("\nTres wins!\n\n");

    printf("Press any key to return to the main menu...");
    getch();

    return over;
}

int main()
{   
    char board[SIZE][SIZE];
    int menu = 0;
    int error = 0;

    do
    {
        printf(CLS);
        displayTitle();

        if(error)
            printf("Invalid!\n\n");

        error = 0;

        printf("[1] Play game\n");
        printf("[2] Exit game\n\n");
        printf("Enter option: ");

        if(scanf("%d", &menu) != 1)
            while(getchar() != '\n');
        
        switch(menu)
        {
            case 1:
                initBoard(board);

                play(board);

                break;

            default:
                error = 1;
                break;
        }
    }
    while(menu != 2);

    printf(CLS);
    displayTitle();
    printf("Thank you for playing UnoDosTres!\n\n");
    printf("Press any key to exit...");
    getch();

    return 0;
}
