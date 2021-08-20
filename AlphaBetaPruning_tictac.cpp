#include<bits/stdc++.h>
using namespace std;

char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
//player vs player
int player1score=0;
int player2score=0;
//computer vs player
int playerscore=0;
int computerscore=0;

void draw_board()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			cout<<board[i][j];
			if(j!=2)
				cout<<"|";
		}
		if(i!=2)
			cout<<endl<<"------"<<endl;
	}
	cout<<endl<<endl;
}

pair<int,int> getRowCol(int pos)
{
	int row,col;
	if(pos%3==0)
	{
		row=pos/3 -1;
		col=2;
	}
	else
	{
		row=pos/3;
		col=pos%3 -1;
	}
	return {row,col};
}

bool fill_grid(int pos,char choice)
{
	pair<int,int>p=getRowCol(pos);
	int row=p.first,col=p.second;
	if(board[row][col]!='O' && board[row][col]!='X')
	{
		board[row][col]=choice;

		return true;
	}
	return false;
}

bool check_winner()
{
	int i;
	for(i=0;i<3;i++)
	{
		if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
			return true;
		if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
			return true;
	}
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
		return true;
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
		return true;
	return false;
}

void reset_board()
{
	board[0][0]='1';
	board[0][1]='2';
	board[0][2]='3';
	board[1][0]='4';
	board[1][1]='5';
	board[1][2]='6';
	board[2][0]='7';
	board[2][1]='8';
	board[2][2]='9';
}

void game()
{
	int i=9,player=1;
	char choice;
	reset_board();
	draw_board();
	cout<<"Choose your choice ( O or X ) : ";
	cin>>choice;
	while(i--)
	{	
		cout<<"Player"<<player<<" turn : Enter your position : ";
		int position;
		cin>>position;
		cout<<endl;
		if(!fill_grid(position,choice))
		{
			i++;
			cout<<"Already Occupied, choose different position"<<endl;
		}
		else
		{
			if(check_winner())
			{
				draw_board();
				cout<<"Player"<<player<<" has won"<<endl;
				if(player==1)
					player1score++;
				else
					player2score++;
				break;
			}

			if(choice=='O')
				choice='X';
			else if(choice=='O')
				choice='O';
			else
			{
				cout<<"Wrong choice, choose either 'O' or 'X'"<<endl;
				game();
			}

			if(player==1)
				player=2;
			else
				player=1;

			draw_board();
		}
	}
	if(i==0)
		cout<<"Game Tie"<<endl;
	cout<<"Scores"<<endl<<"-------"<<endl;
	cout<<"Player1 : "<<player1score<<endl;
	cout<<"Player2 : "<<player2score<<endl<<endl;
}

int evaluate()
{
	char player = 'X';
	char opponent = 'O';

    for (int row = 0; row<3; row++)
    {
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2])
        {
            if (board[row][0]==player)
                return -10;
            else if (board[row][0]==opponent)
                return 10;
        }
    }
 
    for (int col = 0; col<3; col++)
    {
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col])
        {
            if (board[0][col]==player)
                return -10;
 
            else if (board[0][col]==opponent)
                return 10;
        }
    }
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if (board[0][0]==player)
            return -10;
        else if (board[0][0]==opponent)
            return 10;
    }
 
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2]==player)
            return -10;
        else if (board[0][2]==opponent)
            return 10;
    }
 
    return 0;
}

bool isMovesLeft()
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j]=='0' + 3*i+j+1)
                return true;
        }
    }
    return false;
}

pair<int,int> minimax(bool isMax, int alpha, int beta)
{
    int score = evaluate();
    char player = 'X';
	char opponent = 'O';
 
    if (score == 10 || score == -10)
        return {score,score};

    if (isMovesLeft()==false)
        return {0,0};

    int bestMove = -1;
 
    if (!isMax)
    {
        int bestVal = 1000;
 
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]!='O' && board[i][j]!='X')
                {
                    board[i][j] = player;
 
                    int moveVal = minimax(!isMax,alpha,beta).first;
                    if(moveVal < bestVal)
                    {
                    	bestMove = 3*i + j + 1;
                    	bestVal = moveVal;
                    	beta=min(beta,bestVal);
                    	
	                    if(alpha>=beta)
    					{
    						board[i][j] = '0' + 3*i + j + 1;
    						return {bestVal,bestMove};
    					}
                    }
                    board[i][j] = '0' + 3*i + j + 1;
                }
            }
        }
        return {bestVal,bestMove};
    }
 
    else
    {
        int bestVal = -1000;
 
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]!='O' && board[i][j]!='X')
                {
                    board[i][j] = opponent;
 
                    int moveVal = minimax(!isMax,alpha,beta).first;

                    if(moveVal > bestVal)
                    {
                    	bestMove = 3*i + j + 1;
                    	bestVal = moveVal;
                    	alpha=max(alpha,bestVal);
                    	
	                    if(alpha>=beta)
    					{
    						board[i][j] = '0' + 3*i + j + 1;
    						return {bestVal,bestMove};
    					}
                    }
                    board[i][j] = '0' + 3*i + j + 1;
                }
            }
        }
        return {bestVal,bestMove};
    }
}

int findBestMove()
{
    int bestVal = -1000, bestMove = -1, alpha=INT_MIN, beta=INT_MAX;
 
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if(board[i][j]!='O' && board[i][j]!='X')
            {
                board[i][j] = 'O';
                int moveVal = minimax(false,alpha,beta).first;
                board[i][j] = '0' + 3*i + j + 1;
                if (moveVal > bestVal)
                {
                	bestMove = 3*i + j + 1;
                    bestVal = moveVal;
                }
            }
        }
    }
 
    cout<<"Computer chooses : "<<bestMove<<endl;
    return bestMove;
}

void computer()
{
	int i=9;
	int position;
	bool player=true;
	reset_board();
	draw_board();
	while(i--)
	{	
		if(player==true)
		{
			cout<<"Player turn : Enter your position : "<<endl;
			cin>>position;
	
			if(!fill_grid(position,'X'))
			{
				i++;
				cout<<"Already Occupied, choose different position"<<endl;
			}
			else
			{
				if(check_winner())
				{
					draw_board();
					cout<<"Player has won"<<endl;
					playerscore++;
					break;
				}
				player=false;
				draw_board();
			}
		}
		else
		{
			position = findBestMove();
			if(!fill_grid(position,'O'))
			{
				i++;
				cout<<"Already Occupied, choose different position"<<endl;
			}
			else
			{
				if(check_winner())
				{
					draw_board();
					cout<<"Computer has won"<<endl;
					computerscore++;
					break;
				}
				player=true;
				draw_board();
			}
		}
	}
	if(i==0)
		cout<<"Game Tie"<<endl;
	cout<<"Scores"<<endl<<"-------"<<endl;
	cout<<"Player : "<<playerscore<<endl;
	cout<<"Computer : "<<computerscore<<endl<<endl;
}



int main()
{
	while(1)
	{
		cout<<"Player sign : 'X'"<<endl;
		cout<<"Computer sign : 'O'"<<endl;
		computer();
	}
}