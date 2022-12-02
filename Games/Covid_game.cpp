#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//rang
string RESET ="\033[0m";
string RED = "\033[31m";

//data haye mohem va omoomi
int level=1 , vaccine=0 , credit=0 , round=1 , health=3 , amIn=3 , amOut=3 , zarfiat=3 , bord=5 , kill=0;
bool IsItFirst = true;
//mokhtasat ha :
int xp = 1 , yp = 15; //mokhtasate player
int xd = 15 , yd= 1; //mokhtasate noghte etesal
int xz[10] = { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1} , yz[10] = { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1}; //mokhtasate zombie
int xv[10] = { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1} , yv[10] = { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1}; //mokhtasate vaccine
int xa[10] = { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1} , ya[10] = { -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1}; //mokhtasate ammo
  
//safhe ha :
void Menu(void); //menu bazi
void Game(void); //mahale entekhabe harakat		//NAGHES
void Settings(void); //tanzimat
void Credits(void); //sazande
void Help(void); //amoozesh		//NAGHES
void Exit(void); //khorooj
void Upgrade(void); //safhe ye upgrade		//NAGHES
void GameBoard(void); //safhe bazi
void InGameMenu(void); //safheye menu ba zadande klid m
void InGameSettings(void); //safheye setting baraye bargasht be InGameMenu

//action ha :
void Health(void); //navare salamti
void Reload(void); //reload kardane tofang
void ZomMove(void); //barresiye harakate zombie ha
void NextLevel(void); //raftan be marhale ba'd		//NAGHES
void Reset(void); //Reset kardane etelaate bazi
void Achievement(void); //payami ke hengame koshtan mide
void CheckZ(void); //barresie zarbe khordan			//NAGHES
void CheckHealth(void);
void CheckV(void); //bardashtane vaccine		//NAGHES
void CheckA(void); //bardashtane ammo		//NAGHES

//mokhtasat :
void SetZ(void); //jologiri az oftadane mokhtasate zombie rooye player
void SetV(void); //jologiri az oftadane mokhtasate vaccine rooye player ya zombie
void SetA(void); //jologiri az oftadane mokhtasate ammo rooye player ya zombie ya vaccine



//movement :
void MoveUp(void); //harekat be bala
void MoveDown(void); //harekat be payin
void MoveLeft(void); //harekat be chap
void MoveRight(void); //harekat be rast
//shoot :
void ShootUp(void); //shelik be bala
void ShootDown(void); //shelik be payin
void ShootLeft(void); //shelik be chap
void ShootRight(void); //shelik be rast

int main(){
	
	//title:
	system("Color 04");
	cout<<" ######   #######  ##     ## #### ########     #######    #####    #######    #####  "<<endl;
	cout<<"##    ## ##     ## ##     ##  ##  ##     ##   ##     ##  ##   ##  ##     ##  ##   ## "<<endl;
	cout<<"##       ##     ## ##     ##  ##  ##     ##          ## ##     ##        ## ##     ##"<<endl;
	cout<<"##       ##     ## ##     ##  ##  ##     ##    #######  ##     ##  #######  ##     ##"<<endl;
	cout<<"##       ##     ##  ##   ##   ##  ##     ##   ##        ##     ##        ## ##     ##"<<endl;
	cout<<"##    ## ##     ##   ## ##    ##  ##     ##   ##         ##   ##  ##     ##  ##   ## "<<endl;
	cout<<" #####    ######      ###    #### ########    #########   #####    #######    #####  "<<RESET<<endl;
	
	cout<<"Welcome to Covid 2030 game!"<<endl<<endl;
	
	Menu();
	
	return 0;

	
}

void Menu(){
	
	while(1)
	{
	//list:
	cout<<"1-New Game\n2-Settings\n3-Credits\n4-Help\n5-Exit\n\n";
	char choice;
	cin>>choice;
	//choices:
	switch(choice)
	{
		case '1':
			Reset();
			Game();
			break;
		case '2':
			Settings();
			break;
		case '3':
			Credits();
			break;
		case '4':
			Help();
			break;
		case '5':
			Exit();
			break;
		default:
			cout<<"Please just enter the numbers in the menu:\n";
			Menu();
			break;
	}
	}
	return;
}

void Game(void){
	
	if(IsItFirst == true)
	{
		GameBoard();
		IsItFirst = false;
	}
	//gereftane dastoor:
	string choice;
	cin>>choice;
	
	for( int i=0 ; choice[i] != NULL ; i++)
	{
		choice[i] = tolower(choice[i]);
		
		//natijeye entekhab
		switch(choice[i])
		{
			case 'w':
				MoveUp();
				break;				
			case 's':
				MoveDown();
				break;
			case 'a':
				MoveLeft();
				break;
			case 'd':
				MoveRight();
				break;
			case 'f':
				ShootLeft();
				break;
			case 'g':
				ShootDown();
				break;
			case 't':
				ShootUp();
				break;
			case 'h':
				ShootRight();
				break;
			case 'e':
				return;
			case 'r':
				Reload();
				break;
			case 'm':
				InGameMenu();
				break;
			case 'u':
				Upgrade();
				break;
		}
		round++;
		ZomMove();
		
		if(xp == xd && yp == yd)
			NextLevel();
		CheckZ();
		CheckHealth();
		CheckV();
		CheckA();
		GameBoard();
	}
	Game();
}

void Settings(){
	
	cout<<"\nFinal level is: 10\n\n";
	Menu();
}

void Credits(){
	cout<<"\nMade by: Rasa Ghorbanalizadeh\n\n";
	Menu();
}

void Help(){
	
	cout<<"Type WASD to move"<<endl;
	cout<<"Type TFGH to shoot"<<endl;
	cout<<"Type r to reload"<<endl;
	cout<<"Type u to go to the upgrade menu"<<endl;
	cout<<"Type m to go to the menu"<<endl;
	cout<<"Type e to exit the game"<<endl;
	cout<<"If a zombie(shown with Z) comes to any blocks beside you(shown with P), you'll loose one of your lives"<<endl;
	cout<<"If you loose all your health, you'll loose the game"<<endl;
	cout<<"Pick all vaccines(shown with V) up and reach the D point(shown with D) to go to the next level"<<endl;
	cout<<"Good luck!"<<endl<<endl;
	Menu();
	return;
}

void Exit(){
	cout<<"\nAre you sure you want to exit the game?(y/n)\n\n";
	char YorN;
	cin>>YorN;
	YorN = tolower(YorN);
	
	if(YorN == 'n')
		return;
	else if(YorN == 'y')
		{
		cout<<"Good Bye!\n";
		exit(0);
		}
	else
		{
			cout<<"Please only choose y or n:\n";
			Exit();
		}
	return;
}

void Health(){
	
	cout<<"[ ";
	for(int i=0 ; i<health ; i++)
	{
		cout<<"| ";
	}
	cout<<"]";
	return;
}

void Reload(){
	
	if(amOut == 0)
	{
		cout<<"\nNo Ammo!\n\n";
	}
	else if(amIn == zarfiat)
	{
		cout<<"\nThe gun is already charged\n\n";
	}
	else if( amOut <= (zarfiat - amIn) )
	{
		amIn += amOut;
		amOut = 0;
		cout<<"\nReloaded!\n\n";
	}
	else
	{
		amOut -= (zarfiat - amIn);
		amIn = zarfiat;
		cout<<"\nReloaded!\n\n";
	}
	return;
}

void Upgrade(){
	
	cout<<"0-Return to game"<<endl;
	cout<<"1-Upgrade capacity of magazine: 1 bullet (maximum is 7 bullets, now is "<<zarfiat<<"), Credit required: "<<level*zarfiat<<endl;
	cout<<"2-Upgrade range of shotgun: 1 times the size of the person himself (maximum is 10 times, now is "<<bord<<"), Credit required: "<<level+bord<<endl;
	cout<<"3-Get an additional health (maximum is 5 healths, now is "<<health<<"),Credit required: "<<(level+1)*health<<endl;
	//choice
	char choice;
	cin>>choice;
	switch(choice)
	{
		case '0':
			return;
			break;
		case '1':
			if( credit<(level*zarfiat) )
				cout<<"\nUnfortunately, your credit is not enough to get this item. Please gain "<<(level*zarfiat)-credit<<" more credit by playing.\n";
			else if(zarfiat == 7)
				cout<<"The selected item is maximum.\n";
			else
			{
				zarfiat++;
				credit -= (level*zarfiat);
				cout<<"\nUpgrade done successfully.\nYour magazine capacity is now "<<zarfiat<<".\n";
			}
			break;
		case '2':
			if( credit<(level+bord) )
				cout<<"\nUnfortunately, your credit is not enough to get this item. Please gain "<<(level+bord)-credit<<" more credit by playing.\n";
			else if (bord == 10)
				cout<<"\nThe selected item is maximum.\n";
			else
			{
				credit -= (level+bord);
				bord++;
				cout<<"\nUpgrade done successfully.\nYour shotgun range is now "<<bord<<".\n";
			}
			break;
		case '3':
			if( credit<(level+1)*health )
				cout<<"\nUnfortunately, your credit is not enough to get this item. Please gain "<<((level+1)*health)-credit<<" more credit by playing.\n";
			else if (health == 5)
				cout<<"\nThe selected item is maximum.\n";
			else
			{
				credit -= ((level+1)*health);
				health++;
				cout<<"\nAdditional health received successfully.\nYour health is now "<<health<<".\n";
			}
			break;
		default:
			cout<<"\nPlease just enter the numbers in the menu:\n";
			break;
	}
	Upgrade();
	return;
}

void ZomMove(){
	for(int k=0 ; k<level ; k++)
	if(xz[k] != -1 && yz[k] != -1)
		if(round%2 == 0)
		{
			if(xz[k] > xp)
				xz[k]--;
			else if(xz[k] < xp)
				xz[k]++;
			else if(yz[k] > yp)
				yz[k]--;
			else if(yz[k] < yp)
				yz[k]++;
		}
	return;
}

void GameBoard(){
	
	bool chapP=false;
	bool ZroP=false;
	
	cout<<"Level: "<<level<<"  Vaccine: "<<vaccine<<"  Credit: "<<credit<<"  Round: "<<round<<endl;
	cout<<"Health: ";
	Health();
	cout<<" Ammo: "<<amIn<<"/"<<amOut<<" Kill: "<<kill<<endl;
	
	//zamine bazi :
	
	string board[17][17];
	
	for(int j=16 ; j>=0 ; j--)
	{
		for(int i=0 ; i<17 ; i++)
		{
			if(j == 0 || j == 16)
			{
				board[i][j] = '-';
			}
			else if(i == 0 || i == 16)
			{
				board[i][j] = '|';
			}
			
			if( i == xp && j == yp )
			{
			for(int k=0 ; k<level ; k++)
				{
					if( xp == xz[k] && yp == yz[k] )
					{
						board[i][j] = 'Z';
						ZroP=true;
					}
					if( i == xz[k] && j == yz[k])
					{
						board[i][j] = 'Z';	
					}
				}
				
				if(!ZroP) //tashkhis dadane inke aya tooye in loop yekbar ro chap shode ya na
				{
					board[i][j] = 'P';
					chapP = true;
				}
			}
			else if( i == xd && j == yd )
			{
				
				board[i][j] = 'D';
			}
			
			for(int k=0 ; k<level ; k++)
			{
				if( i == xz[k] && j == yz[k] )
					{
						if(xp != xz[k] || yp != yz[k])
						{
					
							board[i][j] = 'Z';
						}
					}
				else if( i == xv[k] && j == yv[k] )
				{
					
					board[i][j] = 'V';
				}
					else if( (i == xa[k] && j == ya[k]) )
					{
						if( xa[k] == xp && ya[k] == yp)
						{	
							board[i][j] = 'P';
						}
						else
						{
							board[i][j] = 'A';
						}
					}
			}
							
			if(board[i][j] == "\0")
				board[i][j] = ' ';
		}
	}
	
	for(int j=16; j>=0 ; j--)
	{
		for(int i=0 ; i<17 ; i++)
		{
			cout<<board[i][j];
		}
		cout<<endl;
	}
	
	return;
}

void MoveUp(){
	
	if(yp<15)
		yp++;
}

void MoveDown(){
	
	if(yp>1)
		yp--;
}

void MoveRight(){
	
	if(xp<15)
		xp++;
}

void MoveLeft(){
	
	if(xp>1)
		xp--;
}

void NextLevel(){
if( vaccine == level)
	{
		if(level != 10)
		{
			cout<<"You Won! You have reached level "<< level+1 <<endl;
			vaccine = 0;
			round = 1;
			level++;
		
			xp = 1 , yp = 15;
			xd = 15 , yd= 1;
		
			srand(time(0));
			for(int i=0 ; i<level ; i++)
			{
				xz[i] = rand() % 15 + 1; //mokhtasate zombie
				yz[i] = rand() % 15 + 1; 
				xv[i] = rand() % 15 + 1; //mokhtasate vaccine
				yv[i] = rand() % 15 + 1;
			}
			for(int i=0 ; i<(level/2) ; i++)
			{
				xa[i] = rand() % 15 + 1; //mokhtasate ammo
				ya[i] = rand() % 15 + 1;
			}
			IsItFirst = true;
			
			SetZ();
			SetV();
			SetA();
			
			Game();
		}
		else
		{
			cout<<"\nCongratulations! You have successfully collected all the vaccines!\nNow it is time to return to the Earth\nGood Bye!\n";
			Menu();
		}
	}
	else
	{
		cout<<"\nFirst get all the vaccines.\n\n";
	}
	return;
}

void SetZ(){
	for(int k=0 ; k<level ; k++)
	{
		if( (xz[k] == xp && yz[k]==yp) || (xz[k] == xd && yz[k]==yd) )
		{
			srand(time(0));
			xz[k] = rand() % 15 + 1;
			yz[k] = rand() % 15 + 1;
			SetZ();
		}
	}
	return;
}

void SetV(){
	for(int k=0 ; k<level ; k++)
	{
		for(int t=0 ; t<level ; t++)
		{
			if( (xv[k] == xp && yv[k]==yp) || (xv[k] == xz[t] && yv[k]==yz[t]) || (xv[k] == xd && yv[k]==yd) )
			{
				srand(time(0));
				xv[k] = rand() % 15 + 1;
				yv[k] = rand() % 15 + 1;
				SetV();
			}
		}
	}
	return;
}

void SetA(){
	
	for(int k=0 ; k<(level/2) ; k++)
	{
		for(int t=0 ; t<level ; t++)
		{
			if( (xa[k] == xp && ya[k] == yp) || (xa[k] == xz[t] && ya[k] == yz[t]) || (xa[k] == xv[t] && ya[k] == yv[t]) || (xa[k] == xd && ya[k] == yd) )
			{
				srand(time(0));
				xa[k] = rand() % 15 + 1;
				ya[k] = rand() % 15 + 1;
				SetA();
			}
		}
	}
	return;
}

void InGameMenu(){
	
	cout<<"\n0-Return to game\n1-New Game\n2-Settings\n3-Exit\n";
	//choice
	int choice;
	cin>>choice;
	switch(choice)
	{
		case 0:
			GameBoard();
			break;
		case 1:
			Reset();
			Game();
			break;
		case 2:
			InGameSettings();
			InGameMenu();
			break;
		case 3:
			Exit();
			InGameMenu();
			break;
		default:
			cout<<"Please just enter the numbers in the menu:";
			InGameMenu();
			break;
	}
	return;
}

void InGameSettings(){
	
	cout<<"\nFinal level is: 10\n\n";
	InGameMenu();
}

void Reset(){
	level=1 , vaccine=0 , credit=0 , round=1 , health=3 , amIn=3 , amOut=3 , zarfiat=3 , bord=5 , kill=0;
	IsItFirst = true;

	xp = 1 , yp = 15;
	xd = 15 , yd= 1;
	
	srand(time(0));
	for(int i=0 ; i<level ; i++)
	{
		xz[i] = rand() % 15 + 1; //mokhtasate zombie
		yz[i] = rand() % 15 + 1; 
		xv[i] = rand() % 15 + 1; //mokhtasate vaccine
		yv[i] = rand() % 15 + 1;
	}
	for(int i=0 ; i<(level/2) ; i++)
	{
		xa[5] = rand() % 15 + 1; //mokhtasate ammo
		ya[5] = rand() % 15 + 1;
	}
	
	SetZ();
	SetV();
	SetA();
	
	return;
}

void ShootUp(){
	
	if ( amIn == 0)
		cout<<"\nNo charged ammo!\n\n";
	else
	{
		for(int k=0 ; k<level ; k++)
		{
			if(xp == xz[k] && yz[k]-yp>=0 && yz[k]-yp <= bord)
			{
				xz[k] = -1;
				yz[k] = -1;
				kill++;
				Achievement();
				credit += level + 1;
				cout<<endl<<level + 1<<" credit gained!\n\n";
				amIn--;
				return;
			}
		}
	cout<<"\nZombie is not in range! come closer.\n\n";
	amIn--;
	}
	return;
}

void ShootDown(){
	
	if ( amIn == 0)
		cout<<"\nNo charged ammo!\n\n";
	else
	{
		for(int k=0 ; k<level ; k++)
		{
			if(xp == xz[k] && yp-yz[k]>=0 && yp-yz[k] <= bord)
			{
				xz[k] = -1;
				yz[k] = -1;
				kill++;
				Achievement();
				credit += level + 1;
				cout<<endl<<level + 1<<" credit gained!\n\n";
				amIn--;
				return;
			}
		}
	cout<<"\nZombie is not in range! come closer.\n\n";
	amIn--;
	}
	return;
}

void ShootRight(){
	
	if ( amIn == 0)
		cout<<"\nNo charged ammo!\n\n";
	else
	{
		for(int k=0 ; k<level ; k++)
		{
			if(yp == yz[k] && xz[k]-xp>=0 && xz[k]-xp <= bord)
			{
				xz[k] = -1;
				yz[k] = -1;
				kill++;
				Achievement();
				credit += level + 1;
				cout<<endl<<level + 1<<" credit gained!\n\n";
				amIn--;
				return;
			}
		}
	cout<<"\nZombie is not in range! come closer.\n\n";
	amIn--;
	}
	return;
}

void ShootLeft(){
	
	if ( amIn == 0)
		cout<<"\nNo charged ammo!\n\n";
	else
	{
		for(int k=0 ; k<level ; k++)
		{
			if(yp == yz[k] && xp-xz[k]>=0 && xp-xz[k] <= bord)
			{
				xz[k] = -1;
				yz[k] = -1;
				kill++;
				Achievement();
				credit += level + 1;
				cout<<endl<<level + 1<<" credit gained!\n\n";
				amIn--;
				return;
			}
		}
	}
	cout<<"\nZombie is not in range! come closer.\n\n";
	amIn--;

	return;
}

void Achievement(){
	
	switch( (kill-1) %14)
	{
		case 0:
			cout<<"\nfirst Blood\n\n";
			break;
		case 1:
			cout<<"\nDouble Kill\n\n";
			break;
		case 2:
			if(round%2 == 0)
				cout<<"\nTriple Kill\n\n";
			else
				cout<<"\nHattrick\n\n";
		case 3:
			cout<<"\nTeam Killer\n\n";
			break;
		case 4:
			cout<<"\nHead Shot\n\n";
			break;
		case 5:
			cout<<"\nRampage\n\n";
			break;
		case 6:
			cout<<"\nKilling Spree\n\n";
			break;
		case 7:
			cout<<"\nUnstoppable\n\n";
			break;
		case 8:
			cout<<"\nMonster Kill\n\n";
			break;
		case 9:
			cout<<"\nMulti Kill\n\n";
			break;
		case 10:
			cout<<"\nLudicrouskill\n\n";
			break;
		case 11:
			cout<<"\nUltra Kill\n\n";
			break;
		case 12:
			cout<<"\nDominating\n\n";
			break;
		case 13:
			cout<<"\nGodlike\n\n";
			break;
	}
	
	return;
}

void CheckZ(){
	
	for(int k=0 ; k<level ; k++)
	{
		if( ( xz[k]-xp < 2 && xz[k]-xp > -2 ) && ( yz[k]-yp < 2 && yz[k]-yp > -2 ) )
		{
			health--;
			cout<<"\nThe zombie is eating you! You lost one of your healths!\n\n";
		}
	}
	return;
}

void CheckHealth(){
	
	if(health == 0)
	{
		cout<<"\nYou Died!\n\nYou Lose! Would you like to try again?(y/n)\n\n";
		char YorN;
		cin>>YorN;
		if(YorN == 'n')
			Menu();
		else
		{
			cout<<"\nThe game will restart in 5 seconds\n\n";
			Reset();
			Game();
		}
	}
	return;
}

void CheckV(){
	
	for(int k=0 ; k<level ; k++)
	{
		if( xv[k] == xp && yv[k] == yp)
		{
			vaccine++;
			credit += (level + 1);
			xv[k] = -1;
			yv[k] = -1;
			cout<<"\nVaccine collected!\n"<< level+1 <<" credit gained!\n\n";
		}
	}
}

void CheckA(){

	for(int k=0 ; k<(level/2) ; k++)
		{
			if( xa[k] == xp && ya[k] == yp)
			{
				if( amOut == zarfiat)
				{
					cout<<"\nAmmo is full\n\n";
				}
				else
				{
					amOut++;
					xa[k] = -1;
					ya[k] = -1;
					cout<<"\nAmmo collected!\n\n";
				}
			}
		}
	}

