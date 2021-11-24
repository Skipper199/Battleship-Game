#include <iostream>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <sstream>

using namespace std;

const int rows=5;			//size of board
const int columns=5;

const int MaxShots=15;		//Max shots

enum tileTypeEnum{			//Enum that helps define the type of a cell
	sea='~',
	ship='s',
	hit='X',
	miss='o'
};

class Tile{
	private:
		int x,y;
		tileTypeEnum tileType;
	public:
		void setCoordinateX(int x){
			this->x=x;
		}
		int getCoordinateX(){
			return x;
		}
		void setCoordinateY(int y){
			this->y=y;
		}
		int getCoordinateY(){
			return y;
		}
		void setTileType(tileTypeEnum tileType){	//sets tile=sea or tile=ship
			this->tileType=tileType;				//     or tile=miss or tile=hit
		}
		char getTileType(){
			return tileType;
		}
};

class Orientation{					//class that sets and returns the orientation of a ship
	private:
		int direction;
	public:
		void setOrientation(int direction){
			this->direction=direction;
		}
		int getOrientation(){
			return direction;
		}
};

class Ship{
	private:
		Tile startingTile;
	public:
		int size;				//size of ships

		bool placeShip(Tile startingTile,Tile board[][columns],Orientation orient){
			if(orient.getOrientation()==0){		//Orientation=0 => horizontal
				for(int i=0;i<size;i++){
					board[startingTile.getCoordinateX()][startingTile.getCoordinateY()+i]=startingTile;
				}
				return true;	//when a ship is placed I return true
			}
			else if(orient.getOrientation()==1){	//Orientation=1 => vertical
				for(int i=0;i<size;i++){
					board[startingTile.getCoordinateX()+i][startingTile.getCoordinateY()]=startingTile;
				}
				return true;	//when a ship is placed I return true
			}
		}
};

class Battleship: public Ship{
	public:
	Battleship(int size){		//constructor that sets the size of the ship(size is inherited from class Ship)
		this->size=size;
	}
};
class Cruiser: public Ship{		//constructor that sets the size of the ship(size is inherited from class Ship)
	public:
	Cruiser(int size){
		this->size=size;
	}
};
class Destroyer: public Ship{	//constructor that sets the size of the ship(size is inherited from class Ship)
	public:
	Destroyer(int size){
		this->size=size;
	}
};

class Board{
	private:
		int count=0,x,y,size,counter=0;
		Tile startingTile,tileObj1,tileObj2;
		bool success=false;
		bool flag1=false,flag2=false,flag3=false;
		Ship shipArray[3];
	public:
		Tile board[rows][columns];

	Board(){								//Constructor that sets board=~ (sea type tiles)
		tileObj1.setTileType(sea);
		for (int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				board[i][j]=tileObj1;
			}

		}
	}

	void  drawBoard(bool show){							//Function that prints board
		if (show==false){								//If show=false opponent's ships won't be visible to the player
			cout<<"  -O P P O N E N T-"<<"\n"<<"  ";

			for(int i=0;i<rows;i++){
				cout<<i<<"   ";
			}
			cout<<"\n";

			for (int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){
					if (j==0){
						if(board[i][j].getTileType()==ship){
							cout<<i<<" ~";
						}
						else cout<<i<<" "<<board[i][j].getTileType();
					}
					else {
						if(board[i][j].getTileType()==ship){
							cout<<"   ~";
						}
						else cout<<"   "<<board[i][j].getTileType();
					}

					if (j+1==rows) cout<<'\n';

				}
			}
		}
		else{											//Opponent's ships will be visible to the player
			cout<<"  -O P P O N E N T-"<<"\n"<<"  ";

			for(int i=0;i<rows;i++){
				cout<<i<<"   ";
			}
			cout<<"\n";

			for (int i=0;i<rows;i++){
					for(int j=0;j<columns;j++){
						if (j==0) {
							cout<<i<<" "<<board[i][j].getTileType();

						}

						else cout<<"   "<<board[i][j].getTileType();
						if (j+1==rows) cout<<'\n';

					}

			}
		}

	}
	void placeAllShips(){			//Function that places all ships on board randomly

		srand(time(NULL));

		Battleship bs(4);			//Create the different types of ships
		Cruiser cr(3);				//and set their size
		Destroyer des(2);

		Tile tileObject;
		Orientation orObj;

		shipArray[0]=bs;			//Store each ship in an array that stores objects
		shipArray[1]=cr;			//of type Ship(line 106)
		shipArray[2]=des;


		tileObject.setTileType(ship);	//set the type of a Tile Object equal to ship

		for(int j=0;j<3;j++){

			do{												//do-while loop
				success=false;								//when success= true do-while loop breaks
				tileObject.setCoordinateX(rand()%rows);		//set random coordinates to tile object
				tileObject.setCoordinateY(rand()%columns);
				x=tileObject.getCoordinateX();
				y=tileObject.getCoordinateY();
				orObj.setOrientation(rand()%2);				//set random orientation to tile object

				try{										//Oversize Exception
					if(orObj.getOrientation()==0){
						if(tileObject.getCoordinateY()+shipArray[j].size-1>=columns){
							throw "OversizeException";
						}
					}
					else if(orObj.getOrientation()==1 ){
						if(tileObject.getCoordinateX()+shipArray[j].size-1>=rows){
							throw "OversizeException";
						}
					}

				}
				catch(const char *e){
					flag1=true;								//if Oversize Exception occurs flag1 changes to true(by default it's set to false)
				}


				try{										//Overlap Tiles Exception
					if(orObj.getOrientation()==0){			//which means if orientation=horizontal
						for(int i=0;i<shipArray[j].size;i++){
							if(board[tileObject.getCoordinateX()][tileObject.getCoordinateY()+i].getTileType()==ship){
								throw "OverlapTilesException";
							}
						}
					}
					else if(orObj.getOrientation()==1){		//which means if orientation=vertical
						for(int i=0;i<shipArray[j].size;i++){
							if(board[tileObject.getCoordinateX()+i][tileObject.getCoordinateY()].getTileType()==ship){
								throw "OverlapTilesException";
							}
						}
					}
				}
				catch(const char *e){
				flag2=true;									//if Overlap Tiles Exception occurs flag2 changes to true(by default it's set to false)
				}


				try{										//AdjacentTiles Exception
					if(orObj.getOrientation()==0){
						for(int i=1;i<=shipArray[j].size;i++){
							if(board[x-1][y].getTileType()==ship ||		//checks all 4 cells next to the tile
							   board[x][y+1].getTileType()==ship ||
							   board[x+1][y].getTileType()==ship ||
							   board[x][y-1].getTileType()==ship)
							{
								throw "AdjacentTilesException";
							}
							y=tileObject.getCoordinateY()+i;
						}

					}
					else if(orObj.getOrientation()==1){
						for(int i=1;i<=shipArray[j].size;i++){
							if(board[x-1][y].getTileType()==ship ||
							   board[x][y+1].getTileType()==ship ||
							   board[x+1][y].getTileType()==ship ||
							   board[x][y-1].getTileType()==ship)
							{
								throw "AdjacentTilesException";
							}
							x=tileObject.getCoordinateX()+i;
						}

					}

				}
				catch(const char *e){
				flag3=true; 					//if Adjacent Tiles Exception occurs flag3 changes to true(by default it's set to false)
				}


				if(j==2) counter++;				//there is a chance that the placement of the last ship is impossible(at least one of the above excpetions will occure).So when j=2(j=2 refers to the last ship) I increment a counter by 1
				if(counter>50){					//when counter>50(after 50 failed attempts to place the last ship)I reset the board(make all Tiles equal to ~) and restart the for loop(j=-1)
					Tile tileObject1;
					tileObject1.setTileType(sea);
					for (int a=0;a<rows;a++){
				       for(int b=0;b<columns;b++){
							board[a][b]=tileObject1;
						}

					}
					j=-1;
					counter=0;
					break;
				}

				if(flag1==false && flag2==false && flag3==false){ //if all the flags are false which means no exception occured we can place the ship
					success=shipArray[j].placeShip(tileObject,board,orObj);//places ship and makes variable success equal to true
				}

				flag1=false;	//set all flags equal to false again so we can reuse the exceptions
				flag2=false;
				flag3=false;

			}while(success==false);
		}


	}
	bool allShipsSunk(){
		count=0;							//set a counter equal to 0
		for (int i=0;i<rows;i++){			//checks all cells of the board
			for(int j=0;j<columns;j++){
				if(board[i][j].getTileType()==ship){	//if a cell's tile type is ship I increment the counter by 1
					count++;
				}
			}
		}
		if(count==0) return true;			//if counter equals 0 than no ships are left on the board so I return true
		else return false;					//if counter does not equal 0 there are still ship type cells on the board
	}
};

class Game{
	private:
		int x,y;

		string line;
	public:
		int r[2];
		int * getInput(){
			do{
				cout<<"Give the coordinates of your shot separated with space(x y)"<<endl;
				while(getline(cin,line)){	//Makes sure that the input is 2 integers separated with a space
					stringstream ss(line);
					if(ss >> x && ss>>y){
						if (ss.eof()){
							break;
						}
					}
					cout<<"Wrong Input!The coordinates of your shots have to be 2 integers(Example:3 4).Please try again"<<endl;
				}
				if(x>=rows || y>=columns || x<0 || y<0){
					cout<<"Wrong input.The coordinates of your shot have to be within the limits of the board.Please try again\n"<<endl;
				}
			}while(x>=rows || y>=columns || x<0 || y<0);

			r[0]=x;
			r[1]=y;

			return r;	//return the array
		}
};

class Player{
	private:
		Board boar;
		Game gameObj1;
		int x,y,shotsCount=0,shotsOnTargetCount=0,missedShotsCount=0,repeatedShotsCount=0;
		int *ptr;		//pointer that points to an int
	public:
		void fire(Tile board[][columns],Tile fireTile){
			ptr=gameObj1.getInput();	//points to the array class Game
															//*ptr=r[0],*(ptr+1)=r[1]
			if(board[*ptr][*(ptr+1)].getTileType()==hit){	//checks the type of cell and prints accordingly
				cout<<"\nAlready HIT"<<endl;
				shotsCount++;								//incement counters
				missedShotsCount++;
				repeatedShotsCount++;
			}
			if(board[*ptr][*(ptr+1)].getTileType()==miss){	//checks the type of cell and prints accordingly
				cout<<"\nAlready MISS"<<endl;
				shotsCount++;								//incement counters
				missedShotsCount++;
				repeatedShotsCount++;
			}
			if(board[*ptr][*(ptr+1)].getTileType()==ship){	//checks the type of cell and prints accordingly
				fireTile.setTileType(hit);
				board[*ptr][*(ptr+1)]=fireTile;
				cout<<"\nHIT"<<endl;
				shotsCount++;								//incement counters
				shotsOnTargetCount++;
			}
			if(board[*ptr][*(ptr+1)].getTileType()==sea){	//checks the type of cell and prints accordingly
				fireTile.setTileType(miss);
				board[*ptr][*(ptr+1)]=fireTile;
				cout<<"\nMISS"<<endl;
				shotsCount++;								//incement counters
				missedShotsCount++;
			}

		}
		void getStats(){				//returns player's stats
			cout<<"\n\nSTATS"<<endl;
			cout<<"\nNumber of shots:"<<shotsCount<<endl;
			cout<<"Number of shots on target:"<<shotsOnTargetCount<<endl;
			cout<<"Number of missed shots:"<<missedShotsCount<<endl;
			cout<<"Number of repeated shots:"<<repeatedShotsCount<<endl;
		}
};

int main(){
	static int shots=0;	//shots counter

	Tile tileObj;				//OBJECTS
	Player playerObj;
	Board boardObj;
	Game gameObj;
	Orientation orientationObject;

	cout<<"Welcome to the battleship game.\n\n"<<endl;
	boardObj.placeAllShips();	//Place ships on board
	boardObj.drawBoard(false);	//prints board(ships not visible from the player)


	while(boardObj.allShipsSunk()==false){		//Game loop that breaks when function allShipsSunk return true or number of MaxShots is reached
		if(shots>=MaxShots) break;
		cout<<"Number of remaining shots:"<<MaxShots - shots<<"\n"<<endl;
		playerObj.fire(boardObj.board,tileObj);
		boardObj.drawBoard(false);
		shots++;
		boardObj.allShipsSunk();
	}
	if(boardObj.allShipsSunk()==true){
		cout<<"\nCongrats champ you won :)"<<endl;
		playerObj.getStats();
	}
	else if(boardObj.allShipsSunk()==false){
		cout<<"Game Over.Better luck next time :("<<endl;
		playerObj.getStats();
	}
	cout<<"\n"<<endl;
	boardObj.drawBoard(true);				//prints board(ships are visible)

	return 0;
}
