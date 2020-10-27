#include <iostream>
#include <time.h>
#include <algorithm>

#define gridSize 9
#define bombAmount 10

struct cell
{
	bool isRevealed = false;
	bool isFlagged = false;
	int value;
} grid[gridSize][gridSize] = {};

bool isInRange(int x, int y)
{
    return (y >= 0 && y < gridSize && x >= 0 && x < gridSize);
}

bool isGameOver()
{
    int tmpCellCount = 0, tmpBombCount = 0;

    for(int i = 0; i < gridSize; i++)
        for(int j = 0; j < gridSize; j++)
            if(grid[i][j].isRevealed == true)
                tmpCellCount++;

    for(int i = 0; i < gridSize; i++)
        for(int j = 0; j < gridSize; j++)
            if(grid[i][j].isFlagged == true)
                tmpBombCount++;

    return tmpCellCount == gridSize * gridSize && tmpBombCount == bombAmount;
}

void revealAll()
{
    for(int i = 0; i < gridSize; i++)
        for(int j = 0; j < gridSize; j++)
            grid[i][j].isRevealed = true;
}

void printGrid()
{
	system("cls");

	printf("  ");

	for(int i = 1; i <= gridSize; i++)
		printf(" %i", i);

	printf("\n");

	for(int i = 0; i < gridSize; i++){
		i + 1 > 9 ? printf("%i ", i + 1) : printf(" %i ", i + 1);
		for(int j = 0; j < gridSize; j++){
            if(grid[i][j].isFlagged)
                printf("F ");
            else if(grid[i][j].isRevealed)
				grid[i][j].value == -1 ? printf("* ") : printf("%i ", grid[i][j].value);
			else
				printf("# ");
		}
		printf("\n");
	}
}

void generateGrid()
{
    srand(time(NULL));

	for(int i = 0; i < bombAmount; i++)
		grid[rand() % gridSize][rand() % gridSize].value = -1;

	int tmp;

	for(int i = 0; i < gridSize; i++){
		for(int j = 0; j < gridSize; j++){
			if(grid[i][j].value == 0){
				tmp = 0;
                if(grid[i + 1][j].value == -1 && isInRange(j, i + 1)) tmp++;
				if(grid[i - 1][j].value == -1 && isInRange(j, i - 1)) tmp++;
				if(grid[i][j + 1].value == -1 && isInRange(j + 1, i)) tmp++;
				if(grid[i][j - 1].value == -1 && isInRange(j - 1, i)) tmp++;
				if(grid[i + 1][j + 1].value == -1 && isInRange(j + 1, i + 1)) tmp++;
				if(grid[i - 1][j - 1].value == -1 && isInRange(j - 1, i - 1)) tmp++;
				if(grid[i + 1][j - 1].value == -1 && isInRange(j - 1, i + 1)) tmp++;
				if(grid[i - 1][j + 1].value == -1 && isInRange(j + 1, i - 1)) tmp++;
				grid[i][j].value += tmp;
			}
		}
	}
}

void revealZeroes(int x, int y, int &score)
{
    grid[y][x].isRevealed = true;

    if(grid[y + 1][x].value == 0 && grid[y + 1][x].isRevealed == false && isInRange(x, y + 1)) revealZeroes(x, y + 1, score);
    if(grid[y - 1][x].value == 0 && grid[y - 1][x].isRevealed == false && isInRange(x, y - 1)) revealZeroes(x, y - 1, score);
    if(grid[y][x + 1].value == 0 && grid[y][x + 1].isRevealed == false && isInRange(x + 1, y)) revealZeroes(x + 1, y, score);
    if(grid[y][x - 1].value == 0 && grid[y][x - 1].isRevealed == false && isInRange(x - 1, y)) revealZeroes(x - 1, y, score);
    if(grid[y + 1][x + 1].value == 0 && grid[y + 1][x + 1].isRevealed == false && isInRange(x + 1, y + 1)) revealZeroes(x + 1, y + 1, score);
    if(grid[y - 1][x - 1].value == 0 && grid[y - 1][x - 1].isRevealed == false && isInRange(x - 1, y - 1)) revealZeroes(x - 1, y - 1, score);
    if(grid[y + 1][x - 1].value == 0 && grid[y + 1][x - 1].isRevealed == false && isInRange(x - 1, y + 1)) revealZeroes(x - 1, y + 1, score);
    if(grid[y - 1][x + 1].value == 0 && grid[y - 1][x + 1].isRevealed == false && isInRange(x + 1, y - 1)) revealZeroes(x + 1, y - 1, score);

    if(grid[y + 1][x].value > 0 && grid[y + 1][x].isRevealed == false && isInRange(x, y + 1)){
        grid[y + 1][x].isRevealed = true;
        score += grid[y + 1][x].value;
    }
    if(grid[y - 1][x].value > 0 && grid[y - 1][x].isRevealed == false && isInRange(x, y - 1)){
        grid[y - 1][x].isRevealed = true;
        score += grid[y - 1][x].value;
    }
    if(grid[y][x + 1].value > 0 && grid[y][x + 1].isRevealed == false && isInRange(x + 1, y)){
        grid[y][x + 1].isRevealed = true;
        score += grid[y][x + 1].value;
    }
    if(grid[y][x - 1].value > 0 && grid[y][x - 1].isRevealed == false && isInRange(x - 1, y)){
        grid[y][x - 1].isRevealed = true;
        score += grid[y][x - 1].value;
    }
    if(grid[y + 1][x + 1].value > 0 && grid[y + 1][x + 1].isRevealed == false && isInRange(x + 1, y + 1)){
        grid[y + 1][x + 1].isRevealed = true;
        score += grid[y + 1][x + 1].value;
    }
    if(grid[y - 1][x - 1].value > 0 && grid[y - 1][x - 1].isRevealed == false && isInRange(x - 1, y - 1)){
        grid[y - 1][x - 1].isRevealed = true;
        score += grid[y - 1][x - 1].value;
    }
    if(grid[y + 1][x - 1].value > 0 && grid[y + 1][x - 1].isRevealed == false && isInRange(x - 1, y + 1)){
        grid[y + 1][x - 1].isRevealed = true;
        score += grid[y + 1][x - 1].value;
    }
    if(grid[y - 1][x + 1].value > 0 && grid[y - 1][x + 1].isRevealed == false && isInRange(x + 1, y - 1)){
        grid[y - 1][x + 1].isRevealed = true;
        score += grid[y - 1][x + 1].value;
    }
}

int main()
{
	generateGrid();
	printGrid();

	int x, y, score = 0;
    char action;

	while(!isGameOver()){
		printf("\nScore = %i\nInput action type o/f and location (x, y): ", score);
		scanf("%c %i %i", &action, &x, &y);

        if(action == 'o')
            switch(grid[y - 1][x - 1].value){
                case -1:
                    grid[y - 1][x - 1].isRevealed = true;
                    revealAll();
                    printGrid();
                    printf("\nScore = %i\n(x, y) = (%i, %i)\nGame over!", score, x, y);
                    scanf("%i", &score);
                    return 0;
                case 0:
                    revealZeroes(x, y, score);
                default:
                    if(!grid[y - 1][x - 1].isRevealed)
                        score += grid[y - 1][x - 1].value;
                    grid[y - 1][x - 1].isRevealed = true;
                    break;
            }
        if(action == 'f')
            grid[y - 1][x - 1].isFlagged ? grid[y - 1][x - 1].isFlagged = false : grid[y - 1][x - 1].isFlagged = true;
		printGrid();
	}

	printf("\nScore = %i\n(x, y) = (%i, %i)\nYou win!", score, x, y);
	scanf("%i", &score);
}
