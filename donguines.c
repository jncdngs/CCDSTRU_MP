#include <stdio.h>

#define SIZE 4

void cls()
{
    printf("\033[H\033[J\033[3J");
}

void initBoard(int board[][SIZE])
{
    int i, j;

    for(i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++)
            board[i][j] = 0;
}

void displayBoard(int board[][SIZE])
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
                printf("| %d ", board[row][j]);
            
            printf("|\n");
            row++;
        }
    }

    printf("\n");
}

int main()
{
    int row = -1;
    int col = -1;

    int turn = 1;
    int go = 0;
    int over = 0;
    
    int board[SIZE][SIZE];

    initBoard(board);
    
    while(!over)
    {
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

        if(turn && go && board[col - 1][row - 1] == 0)
        {
            board[col - 1][row - 1] = 1;
            turn = !turn;
            go = !go;
        }
        else if(!turn && board[col - 1][row - 1] == 1)
        {
            board[col - 1][row - 1] = 0;
            turn = !turn;
        }
        else if(turn && !go && board[col - 1][row - 1] == 0)
        {
            board[col - 1][row - 1] = 3;
            go = !go;
        }
    }        
    return 0;
}
