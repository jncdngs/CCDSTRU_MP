#include <stdio.h>

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
    
    // else if(((board[0][0] == '3' || board[0][0] == 'X') && 
    //          (board[0][1] == '3' || board[0][1] == 'X') && 
    //          (board[0][2] == '3' || board[0][2] == 'X') && 
    //          (board[0][3] == '3' || board[0][3] == 'X')) || 

    //         ((board[0][0] == '3' || board[0][0] == 'X') && 
    //          (board[1][1] == '3' || board[1][1] == 'X') && 
    //          (board[2][2] == '3' || board[2][2] == 'X') && 
    //          (board[3][3] == '3' || board[3][3] == 'X')) || 

    //         ((board[0][3] == '3' || board[0][3] == 'X') && 
    //          (board[1][2] == '3' || board[1][2] == 'X') && 
    //          (board[2][1] == '3' || board[2][1] == 'X') && 
    //          (board[3][0] == '3' || board[3][0] == 'X')) || 
    
    //         ((board[3][0] == '3' || board[3][0] == 'X') && 
    //          (board[3][1] == '3' || board[3][1] == 'X') && 
    //          (board[3][2] == '3' || board[3][2] == 'X') && 
    //          (board[3][3] == '3' || board[3][3] == 'X')))
    //     over = 3;

    return over;
}

int main()
{
    int row;
    int col;

    int turn = 1;
    int go = 0;
    int over = 0;
    
    char board[SIZE][SIZE];

    initBoard(board);
    
    printf("\n\nTres turn\n");

    while(!over)
    {
        row = -1;
        col = -1;

        displayBoard(board);

        do
        {
            printf("Enter row: ");
            scanf("%d", &row);
        }    
        while(row < 1 || row > 4);

        do
        {
            printf("Enter column: ");
            scanf("%d", &col);
        }    
        while(col < 1 || col > 4);

        if(turn && go && board[row - 1][col - 1] == ' ')
        {
            board[row - 1][col - 1] = '1';
            turn = !turn;
            go = !go;

            printf("\n\nTres turn\n");
        }
        else if(!turn)
        {
            if(board[row - 1][col - 1] == '1' || board[row - 1][col - 1] == '3')
                board[row - 1][col - 1] = 'X';
            
            turn = !turn;

            printf("\n\nUno turn\n");
        }
        else if(turn && !go && board[row - 1][col - 1] == ' ')
        {
            board[row - 1][col - 1] = '3';
            go = !go;
            
            printf("\n\nDos turn\n");
        }

        over = isGameOver(board);
    }

    return 0;
}
