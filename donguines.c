#include <stdio.h>
#include <conio.h>
#define SIZE 4

void cls()
{
    printf("\033[H\033[J\033[3J");
}

void initBoard(char board[][SIZE])
{
    int i, j;

    for(i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

void displayBoard(char board[][SIZE])
{
    int i, j;
    int row = 0;

    printf("\nChoose a slot\n\n");
    
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

void getPos(char board[][SIZE], int *row, int *col, int player)
{
    int valid = 0;
    int error = 0;
    int rowTemp, colTemp;

    while(!valid)
    {
        error = 0;
        do
        {
            if(error)
                printf("\nInvalid\n\n");
                
            printf("Enter row: ");
            scanf("%d", &rowTemp);
            error = 1;
        }    
        while(rowTemp < 1 || rowTemp > SIZE);

        error = 0;
        do
        {
            if(error)
            printf("\nInvalid\n\n");
            
            printf("Enter column: ");
            scanf("%d", &colTemp);
            error = 1;
        }    
        while(colTemp < 1 || colTemp > SIZE);

        if((player == 1) && (board[rowTemp - 1][colTemp - 1] == ' '))
            valid = 1;
        else if((player == 2) && (board[rowTemp - 1][colTemp - 1] == '1' || board[rowTemp - 1][colTemp - 1] == '3'))
            valid = 1;
        else
            printf("\nInvalid\n\n");
    }

    *row = rowTemp;
    *col = colTemp;
}

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

int main()
{
    int row = 1;
    int col = 1;

    int turn = 1;
    int go = 0;
    int over = 0;
    
    char board[SIZE][SIZE];

    initBoard(board);
    
    while(!over)
    {
        displayBoard(board);
        
        if(turn && go)
        {
            printf("\nIt is Uno's turn\n\n");
            getPos(board, &row, &col, 1);
        }
        else if(turn && !go)
        {
            printf("It is Tres's turn\n\n");
            getPos(board, &row, &col, 1);
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
            // if(board[row - 1][col - 1] == '1' || board[row - 1][col - 1] == '3')
                board[row - 1][col - 1] = 'X';

            turn = !turn;
        }
        else if(turn && !go && board[row - 1][col - 1] == ' ')
        {            
            board[row - 1][col - 1] = '3';
            go = !go;            
        }
        
        over = isGameOver(board);
    }

    if(over == 1)
        printf("\nUno wins!\n\n");
    else if(over == 2)
        printf("\nDos wins!\n\n");
    else if(over == 3)
        printf("\nTres wins!\n\n");

    getch();
        
    return 0;
}
