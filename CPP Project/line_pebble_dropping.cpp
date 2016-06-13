#include<iostream>
#include<cstdio>
#include <string>
#include <cstdlib>
#include<windows.h>

using namespace std;

class Board
{
     private:
    void clearScreen()
    {
        system("cls");
    }

    public:
    void printBoard(int arr[6][6])//pass a 6*6 matrix
    {
        clearScreen();

        printf("\n\n");

        int i, j;

        for(i=5;; i--)
        {
            printf("  %c", 197);

            for(int k=0;k<6;k++)
            {
                printf("%c%c%c%c",196,196,196,197);
            }

            printf("\n");

            if(i<0) break;  //this action is necessary to make the last line

            printf("  %c ", 179);

            for(j=0; j<6 ; j++)  //6 columns
            {
                if(arr[i][j]==0)printf(" ", arr[i][j]);

                else if(arr[i][j]==1) printf("%c", 4 );

                else printf("%c", 15 );

                printf(" %c ", 179);
            }

            printf("\n");
        }

        printf("    1   2   3   4   5   6  \n\n\n");  //column number

        return ;
    }
};
class Player
{ private:
  string pl1;
    public:
    void setName(string name)
    {
    	pl1=name;
    }

    string getName()
    {
    	return pl1;
    }
    int getMove()
    {
    	inputMessage();
    	int p_num;
        cin>>p_num;

        return p_num;

    }
    void inputMessage()
    {
      cout << getName() <<", it's your move; choose a column:";
    }
};

class Game
{ private:
  Player player1,player2;
  Board board;
  int array[6][6];
  int arr[6];
    public:
    Game(string name1,string name2)
    {
    	player1.setName(name1);
    	player2.setName(name2);

		initializeArrays();
    }

    void initializeArrays()
    {
    	for(int i=0;i<6;i++)
    	{
    		for(int j=0;j<6;j++)
    		{
    			array[i][j]=0;
    		}

    		arr[i]=0;
    	}
    }

    bool isValidInput(int input)
    {
    	if(input<1 || input>6) return false;

    	if(arr[input-1]>5) return false;

    	return true;
    }

    bool place(int input,int player)
    {
    	array[arr[input-1]][input-1] = player;
    	arr[input-1]++;
    }

    bool gameOver(int pl)  //finds out the winner
	{
		int v1, v2;
		int symbol;

		if(pl==1) symbol=1;
		else symbol=2;

		for(v1=0; v1<6; v1++)  //finds row match
		    for(v2=0; v2<3; v2++)
		        if(array[v1][v2]==symbol && array[v1][v2+1]==symbol && array[v1][v2+2]==symbol && array[v1][v2+3]==symbol)
		            return true;

		for(v1=5; v1>2; v1--)  //finds column match
		    for(v2=0; v2<6; v2++)
		        if(array[v1][v2]==symbol && array[v1-1][v2]==symbol && array[v1-2][v2]==symbol && array[v1-3][v2]==symbol)
		            return true;

		for(v1=3; v1<6; v1++)  //finds right-angle match
		    for(v2=0; v2<3; v2++)
		        if(array[v1][v2]==symbol && array[v1-1][v2+1]==symbol && array[v1-2][v2+2]==symbol && array[v1-3][v2+3]==symbol)
		            return true;

		for(v1=3; v1<6; v1++)  //finds left-angles match
		    for(v2=3 ; v2<6; v2++)
		        if(array[v1][v2]==symbol && array[v1-1][v2-1]==symbol && array[v1-2][v2-2]==symbol && array[v1-3][v2-3]==symbol)
		            return true;

		return false;
	}

    Player run()
	{
		int i;
		for(i=0;i<36;i++)
		{
			board.printBoard(array);

			if(i%2==0)
			{
				int input;
				while(1)
				{
					input = player1.getMove();
					bool flag = isValidInput(input);
					if(flag) break;
					cout << "Invalid Input" << endl;
				}

				place(input,1);

				bool over = gameOver(1);

				if(over)
				{
				    board.printBoard(array);
				    return player1;
				}
			}
			else
			{
				int input;
				while(1)
				{
					input = player2.getMove();
					bool flag = isValidInput(input);
					if(flag) break;
					cout << "Invalid Input" << endl;
				}

				place(input,2);

				bool over = gameOver(2);

				if(over)
				{
				    board.printBoard(array);
				    return player2;
				}
			}
		}

        board.printBoard(array);

        Player pl;

		return pl;
	}
};


int main()
{
    system("Color 1a");
    char peb1=4,peb2=15;
    cout<<"\n  ```LINE PEBBLE DROPPING```  \n\n\n";

    cout<<" Player_1's pebble looks like: "<<peb1<<"\n"<<endl;
    cout<<" Player_2's pebble looks like: "<<peb2<<"\n";

	string name1,name2;
    cout << "\n\nEnter player_1's name: ";
    cin >> name1;


    cout << "\nEnter player_2's name: ";
    cin >> name2;

    Game game(name1,name2);

    Player pl = game.run();

    if(pl.getName()=="")
     cout << " Game Draw :/ \n" << endl;
    else
     cout <<"\nCongratulations "<< pl.getName() << "!\nYou have won the game!" << endl;
    return 0;
}
