
#include <iostream>
#include <cstdlib>
#include <string>
#include<ios> 
#include<limits> 
using namespace std;

int compare[3][3]={ //1 for x 
	{0,0,0},		//2 for o
	{0,0,0},
	{0,0,0}
};

//int compare2[3][3]={ //1 for x 
//	{1,2,0},		//2 for o
//	{1,0,0},
//	{0,0,2}
//};

struct Board {
	int depth;
	int config[3][3];
	Board ** nextboards;
};

bool checkInput(string line,int * x, int * y);
void addPossibleMoves(Board ** board,bool xplayer);
Board * makeboard(Board * board,int x,int y,bool xplayer);
void resizeBoard(Board *** board, int count);
void printBoard(Board * board);
void printTutorialBoard(Board * board);
bool spaceAvailable(Board * board, int * spaces);
bool gameover(Board * board,int * winner);
int minimax(Board * board,bool xplayer);
Board * bestMove(Board ** board,bool xplayer);

int main(){

	bool xplayer = true;
	Board * startboard = (Board *)malloc(sizeof(Board));
 	
 	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			startboard->config[i][j]=compare[i][j];//////////////////////
		}
	}
	startboard->depth=0;
	startboard->nextboards = NULL;
	int winner = 0;		
		
	cout<<"Tic-tac-toe"<<endl;
	cout<<"(the unbeatable ai)"<<endl;
	cout<<"enter 1 if you want to play first"<<endl;
	cout<<"enter 2 if you want to play second"<<endl;
	bool flag = true,playermove = true;
	
	string player;
	while(flag){
		cin>>player;
		if(player.length()==1){
			if(isdigit(player[0])){
				if(stoi(player)==1){
					cout<<"first to move"<<endl;
					flag = false;
				}
				else if(stoi(player)==2){
					cout<<"second to move"<<endl;
					playermove = false;
					flag = false;
				}
				else{
					cout<<"Invalid input"<<endl;
					cin.clear();		
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
				}
			}
			else{
				cout<<"Invalid input"<<endl;
				cin.clear();		
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			}
		}	
		else{
			cout<<"Invalid input"<<endl;
			cin.clear();		
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		}
	}
	
	printTutorialBoard(startboard);
	int count =0;	
	string line;
	
	
	flag = true;
	int x,y;
	if(playermove){    //player chooses to move first 
		while(flag){
			cin>>line;
			if(checkInput(line,&x,&y)){
				startboard = makeboard(startboard,x,y,!xplayer);
				printBoard(startboard);
				startboard = bestMove(&startboard,xplayer);
				printBoard(startboard);
				flag = false;
			}
			else{
				cout<<"Invalid input"<<endl;
				cin.clear();		
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			}
		}
	}
	else{
		startboard = bestMove(&startboard,xplayer);
		printBoard(startboard);
	}
	
	while(!gameover(startboard,&winner)){
		flag = true;
		while(flag){
			cin>>line;
			if(checkInput(line,&x,&y)){
				startboard = makeboard(startboard,x,y,!xplayer);
				printBoard(startboard);
				flag = false;
			}else{
				cout<<"Invalid input"<<endl;
				cin.clear();		
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			}
		}
		if(!gameover(startboard,&winner)){		
			startboard = bestMove(&startboard,xplayer);
			printBoard(startboard);
		}
	}
	cout<<winner;
	
//	
	cout<<minimax(startboard,xplayer)<<endl;
	printBoard(bestMove(&startboard,xplayer));
	
}

bool checkInput(string line,int * x,int * y){	
	if(line.length() == 2){
		if((!isdigit(line[0]))&&isdigit(line[1])){
			if(((int)line[1])-48<4){
				if(line[0] == 'a'){
					*x = 0;
					*y = ((int)line[1])-49;
					return true;
				}
				else if(line[0] == 'b'){
					*x = 1;
					*y = ((int)line[1])-49;
					return true;
				}
				else if(line[0] == 'c'){
					*x = 2;
					*y = ((int)line[1])-49;
					return true;
				}
			}else{
				cout<<line[1]<<" line more than 4"<<endl;
				return false;
			}
		}
		else{
			cout<<"baiktad"<<endl;
			return false;
		}
	}
	else{
		cout<<"linelen more than 2"<<endl;
		return false;
	}
}
void addPossibleMoves(Board ** board,bool xplayer){
	int space = 0;
	if(spaceAvailable(*board,&space)){
		resizeBoard(&(*board)->nextboards,space);
		int count=0;	
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if((*board)->config[i][j]==0){
						(*board)->nextboards[count] = makeboard(*board,i,j,xplayer); 
						count++;
					}
				}
			}
	}else{
		cout<<"no space "<<space<<endl;
	}
	//check if has space available
	//count space available 
	//resize board according to the number of spaces
	//make new boards
	//connect boards to the double pointer
}
void resizeBoard(Board *** board, int count){
	*board = (Board **)realloc(*board,count*sizeof(Board*));
}
Board * makeboard(Board * board,int x,int y,bool xplayer){
	Board * newboard = (Board *)malloc(sizeof(Board)); 
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(i==x && j==y){
				if(xplayer){
					newboard->config[i][j] = 1; 
				}else{
					newboard->config[i][j] = 2;
				}
			}else{
				newboard->config[i][j] = board->config[i][j];
			}
		}
	}
	newboard->depth = (board->depth)+1;
	newboard->nextboards = NULL;
	return newboard;
}
void printBoard(Board * board){
	if(board !=NULL){
 		for(int i=0;i<3;i++){
 			for(int j=0;j<3;j++){ 		
 				if(j!=2){
					if(board->config[i][j]==0){
				 		cout<<"   |";
					}
					else if(board->config[i][j]==1){
						cout<<" X |";
					}
					else if(board->config[i][j]==2){
						cout<<" O |";
					}
				}else{
					if(board->config[i][j]==0){
				 		cout<<"   ";
					}
					else if(board->config[i][j]==1){
						cout<<" X ";
					}
					else if(board->config[i][j]==2){
						cout<<" O ";
					}
				}
			}	
			cout<<endl;
			if(i!=2){
				cout<<"-----------"<<endl;
			}
		cout<<endl;
		}
	cout<<endl;
	}else{
		cout<<"cannot print null object"<<endl;
	}
}
void printTutorialBoard(Board * board){
	if(board !=NULL){
		cout<<"   ";
		for(int i=0;i<3;i++){
			cout<<i+1<<"   ";
		}
		cout<<endl;
 		for(int i=0;i<3;i++){
 			if(i==0){
 				cout<<"a ";
			}
			if(i==1){
				cout<<"b ";
			}
			if(i==2){
				cout<<"c ";
			}
 			for(int j=0;j<3;j++){ 		
			 		if(j!=2){
					if(board->config[i][j]==0){
				 		cout<<"   |";
					}
					else if(board->config[i][j]==1){
						cout<<" X |";
					}
					else if(board->config[i][j]==2){
						cout<<" O |";
					}
				}else{
					if(board->config[i][j]==0){
				 		cout<<"   ";
					}
					else if(board->config[i][j]==1){
						cout<<" X ";
					}
					else if(board->config[i][j]==2){
						cout<<" O ";
					}
				}
			}	
			cout<<endl;
			if(i!=2){
				cout<<"  -----------"<<endl;
			}
		cout<<endl;
		}
	}else{
		cout<<"cannot print null object"<<endl;
	}	
}
bool spaceAvailable(Board * board,int * spaces){
	int temp=0;
	for(int i=0;i<3;i++){
 		for(int j=0;j<3;j++){ 		
 			if(board->config[i][j] == 0){
 				temp++;		
			}
		}
	}
	if(temp>0){
		*spaces = temp;
		return true;
	}else{
		*spaces = 0;
		return false;
	}
}
bool gameover(Board * board,int * winner){
	
	int temp;
	for(int i=0;i<3;i++){		
 		if(board->config[i][0]!=0 && board->config[i][1]!=0 && board->config[i][2]!=0){
			 if(board->config[i][0] == board->config[i][1] && board->config[i][0] == board->config[i][2]){
				*winner = board->config[i][0];
				return true;				
			}
		}
	}
	//check horizontal
	
	for(int i=0;i<3;i++){		
 		if(board->config[0][i]!=0 && board->config[1][i]!=0 && board->config[2][i]!=0){
			 if(board->config[0][i] == board->config[1][i] && board->config[0][i] == board->config[2][i]){
 				*winner = board->config[0][i];
			 	return true;				
			}
		}
	}
	//check vertical
	
	bool flag=true;
	for(int i=0;i<3&&flag==true;i++){
		if(board->config[i][i]==0){
			flag = false;
			//there is 0
		}	
	}
	if(flag){
		if(board->config[0][0]==board->config[1][1]&&board->config[0][0]==board->config[2][2]){
			*winner = board->config[0][0];
			return true;		
		}	
	}
	flag=true;
	for(int i=0;i<3&&flag==true;i++){
		for(int j=0;j<3&&flag==true;j++){
			if(i==3-j-1){
				if(board->config[i][j]==0){
					flag=false;
					//there is 0
				}
			}
		}
	}
	if(flag){
		if(board->config[0][2]==board->config[1][1]&&board->config[0][2]==board->config[2][0]){
			*winner = board->config[0][2];
			return true;
		}
	}
	//check diagonal 	
	int pointer=0;
	if(!spaceAvailable(board,&pointer)){
		return true;
	}
	winner = 0;
	return false;
}

int minimax(Board * board,bool xplayer){
	
	int winner=0;
	if(gameover(board,&winner)){
		if(winner==1){
			return 1;
		}
		else if(winner==2){
			return -1;
		}
		else{
			return 0;
		}
	}
	int spaces = 0;
	addPossibleMoves(&board,xplayer);
	spaceAvailable(board,&spaces);
	Board * winnerMove = (Board *)malloc(sizeof(Board));
	if(xplayer){
		int maxEval = -10;
		for(int i=0;i<spaces;i++){
			int eval = minimax(board->nextboards[i],false);
//			printBoard(board->nextboards[i]);
//			cout<<"depth "<<board->nextboards[i]->depth<<endl;
//			cout<<"max "<<eval<<endl;
			if(eval>maxEval){
				maxEval=eval;
			}	
		}
		return maxEval;
	}else{
		int minEval = 10;
		for(int i=0;i<spaces;i++){
			int eval = minimax(board->nextboards[i],true);
//			printBoard(board->nextboards[i]);
//			cout<<"depth "<<board->nextboards[i]->depth<<endl;		
//			cout<<"min "<<eval<<endl;
			if(eval<minEval){
				minEval = eval;  
			}
		}	
		return minEval;
	}
}
Board * bestMove(Board ** board,bool xplayer){
	int spaces=0;
	int score,bestScore = -10;
	Board * winnerBoard = (Board *)malloc(sizeof(Board));
	addPossibleMoves(board,xplayer);
	if(spaceAvailable(*board,&spaces)){
		for(int i=0;i<spaces;i++){
			score = minimax((*board)->nextboards[i],!xplayer);
//			printBoard((*board)->nextboards[i]);
//			cout<<"depth: "<<(*board)->nextboards[i]->depth<<endl;
//			cout<<endl;
			if(score > bestScore){
				bestScore = score;
				winnerBoard = (*board)->nextboards[i];
//				cout<<"score "<<score<<" > "<<"bestscore "<<bestScore<<endl;
			}
		}
		return winnerBoard;
	}else{
		cout<<"no more possible moves"<<endl;
	}
}
	


