#include <stdio.h>

#define SIZE 4

void displayBoard()
{
    int i, j;
    
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
                printf("|   ");
            
            printf("|\n");
        }
    }

    printf("\n");
}

int main()
{
    // int turn = 1;
    // int go = 0;
    // int over = 0;

    // int uno[SIZE][SIZE] = {0};
    // int dos[SIZE][SIZE] = {0};
    // int tres[SIZE][SIZE] = {0};
    // int free[SIZE][SIZE] = {0};

    displayBoard();

    return 0;
}
