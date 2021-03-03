#include<bits/stdc++.h>
using namespace std;

char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
int player1score=0;
int player2score=0;

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

bool fill_grid(int pos,char choice)
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
				i--;
				break;
			}

			if(choice=='O')
				choice='X';
			else
				choice='O';

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

int main()
{
	while(1)
	{
		game();
	}
}