#include <bits/stdc++.h>
using namespace std;

int boardGame[10][10]; 
int currentBoardGame[10][10];
struct Action
{
	char action;
	int x;
	int y;
};
typedef struct Action ACTION;

int width;
int height;
int numberOfMines;

int status = 0;
int flag_Counter = 0;
int mines_Flagged_Counter = 0;
int x,y,countC;
char action;
void cellNumber(int i, int j)
{
	if(i >= 0 && i < width && j >= 0 && j < height && boardGame[i][j]!= -1)
	boardGame[i][j]++;
}

void printBoard(int board[10][10])
{
    cout << "    ";
    for(int i = 0; i < width; i++)
        cout << setw(3)<< i;

    cout << endl << "  ";
    for(int i = 0; i < 32; i++)
        cout << "_";
        cout << endl;

    for(int i = 0; i < width; i++){
            cout << setw(3) << i <<"|";
        for(int j = 0; j < height; j++)
            cout << setw(3) << board[i][j];
            cout << endl;
    }
}
void reveal(int i,int j)
{
	if (currentBoardGame[i][j] == -2 && boardGame[i][j] != -1 && i >= 0 && i < width && j >= 0 && j < height)
    {
    	currentBoardGame[i][j] = boardGame[i][j];

    if(boardGame[i][j] == 0)
        {
        reveal(i,j-1);
        reveal(i,j+1);
        reveal(i-1,j-1);
        reveal(i+1,j-1);
        reveal(i+1,j+1);
        reveal(i-1,j+1);
        reveal(i-1,j);
        reveal(i+1,j);
        }
    }
}
void generateBoardGame(int boardGame[10][10], int currentBoardGame[10][10], int width, int height, int numberOfMines)
{
	int count = 0;
	srand(time(NULL));

	for(int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
            boardGame[i][j]= 0;

        int i = 0;
        int j = 0;
 	while(count < numberOfMines)
    {
        int i = rand()%numberOfMines;
        int j = rand()%numberOfMines;
        if(boardGame[i][j] == 0 )
		{
            boardGame[i][j]= -1;
            cellNumber(i-1,j);
            cellNumber(i+1,j);
            cellNumber(i,j-1);
            cellNumber(i,j+1);
            cellNumber(i-1,j-1);
            cellNumber(i-1,j+1);
            cellNumber(i+1,j-1);
            cellNumber(i+1,j+1);
            count++;
        }
    }
    
	for(int i = 0; i < width; i++)
	{
        for(int j = 0; j < height;j++)
            currentBoardGame[i][j] = -2;
	}
	
}
void getPlayerAction()
{
	do 
	{
		cin >> x;
		cin >> y;
	}
	while (x < 0 || x >= width || y < 0 || y >= height || status == 1);
	cin >> action;
}
void setOrRemoveFlag()
{
	if (currentBoardGame[x][y] == -2)
    {
    	currentBoardGame[x][y] = -3;
    	flag_Counter++;
    	if(boardGame[x][y] == -1)
        	mines_Flagged_Counter++;
    }

	else if (currentBoardGame[x][y]== -3)
    {
    	currentBoardGame[x][y] = -2;
    	flag_Counter--;
    	if(boardGame[x][y] == -1 )
        	mines_Flagged_Counter--;
    }
    if (flag_Counter == numberOfMines && mines_Flagged_Counter == numberOfMines) status = 1;
}

int openATile()
{
	countC = 0;
	if(boardGame[x][y] == -1 && currentBoardGame[x][y] != -3)
    {
        currentBoardGame[x][y] = -1 ;
        status = -1;

        for(int i = 0; i < width; i++)
            for(int j = 0; j < height; j++)
                if(boardGame[i][j] == -1)
                    currentBoardGame[i][j] = -1;
    }
    else
        reveal(x,y);
	
	for (int i = 0; i < width; i++) 
	{
    	for (int j = 0; j < height; j++)
    	{
    		if (currentBoardGame[i][j] == -2 || currentBoardGame[i][j] == -3) countC++;
		}
	}
	if (boardGame[x][y] == -1 && currentBoardGame[x][y] != -3 ) return -1;
    else if (flag_Counter == numberOfMines && mines_Flagged_Counter == numberOfMines) return 1;
    else if (countC == numberOfMines) return 1;
    else return 0;
}
//displayGameStatus(boardGame, currentBoardGame, status)
//{
//	
//}
int main() 
{
	ifstream FileIn;
	FileIn.open("configure.txt", ios_base::in);
	ACTION get;
	FileIn >> width >> height >> numberOfMines;
	cout
	<< "Rules: Nhap theo cu phap"
	<< endl << "x y o : (open) Mo o co toa do (x,y) "
	<< endl << "x y f: (flag) Dat co hay do co o toa do (x,y) voi x la chi so cot, y la chi so hang"
	<< endl << "Ex : 1 5 o la lenh mo o co chi so cot 1 va chi so hang 5."
	<< endl << endl;
	generateBoardGame(boardGame, currentBoardGame, width, height, numberOfMines);
	
	while(status != -1 && status != 1)
    {
    	printBoard(currentBoardGame);
    	cout << endl << "Flags:" << flag_Counter << endl;
    	getPlayerAction();
		if (action == 'o') {
			openATile();
			status = openATile();
		}
		if (action == 'f') setOrRemoveFlag();
    }
	
    if(status == -1)
	{
    printBoard(currentBoardGame);
    cout << endl << "GAME OVER" << endl;
    }

	if(status == 1)
	cout << endl << "YOU WIN" << endl;
 
    return 0;
}


	
