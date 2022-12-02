#include <iostream>
#include <windows.h>
using namespace std;

int numinsert;
int rvcnt=0;
int gvcnt=0;
int numkill[3]= {0};
int ngreenkill[16]= {0};
int nredkill[16]= {0};
char greenkill[16];
char redkill[16];
int count=2;
int turn[9][9]= {0};
char ar[9][9];
void r();
void g();
void w();
void b();
void wb();
bool sarbaz(int,int,int,int);
bool asb(int,int,int,int);
bool rokh(int,int,int,int);
bool fiil(int,int,int,int);
bool king(int,int,int,int);
bool check_insert(char);
void first_move();
void welcome();
void gaming();
void clear(int, int);
bool movecheck(char, int, int, int, int);
void print_board() {
	cout<<"     A     B     C     D     E     F     G     H      ";
	g();
	cout<<"Green Player killed: ";
	r();
	for(int i=0; ngreenkill[i]==1; i++)
		cout<<" "<<greenkill[i];
	w();
	cout<<"   | ";
	r();
	cout<<"Red Player killed: ";
	g();
	for(int i=0; nredkill[i]==1; i++)
		cout<<" "<<redkill[i];
	w();
	cout<<endl;
	for(int t=1; t<=8; t++) {
		for(int i=-1; i<=49; i++)
			if(i==-1||i==0)
				cout<<" ";
			else
				cout<<"#";
		cout<<endl;
		for(int n=1; n<=3; n++) {
			for(int i=-2; i<49; i++) {
				if((i==-2&&n!=2)||i==-1)
					cout<<" ";
				else if(i==-2&&n==2)
					cout<<t;
				else if(i==48&&n==2)
					cout<<"# "<<t;
				else if(i%6==0)
					cout<<"#";
				else if(i==48&&n==2)
					cout<<" "<<t;
				else if(n==2&&i>0&&i%3==0) {
					if(turn[t][((i/3)+1)/2]==1)
						r();
					else if(turn[t][((i/3)+1)/2]==2)
						g();
					cout<<ar[t][((i/3)+1)/2];
					w();
				} else
					cout<<" ";
				if(i==48)
					cout<<endl;
			}
		}
		if(t==8) {
			cout<<"  ";
			for(int i=1; i<=49; i++)
				cout<<"#";
		}
	}
	cout<<endl;
	cout<<"     A     B     C     D     E     F     G     H\n";
}

void clear_scr() {
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

int main() {
	int num;
	welcome();
	cin>>num;
	if(num!=1)
		return 0;
	//clear_scr();
	first_move();
	while(1) {
		clear_scr();
		print_board();
		gaming();
		int x,y,x2,y2;
		char ch,ch2;
		cin>>x>>ch;
		if(x!=0) {
			ch=toupper(ch);
			y=ch-64;
			if(!(x>=1&&x<=8&&y>=1&&y<=8&&ar[x][y]!=' '&&turn[x][y]==count)) { //&&turn[x][y]==count
				while(1) {
					r();
					cout<<"invalid choose!!!  try again: \n";
					w();
					cin>>x>>ch;
					ch=toupper(ch);
					y=ch-64;
					if(x>=1&&x<=8&&y>=1&&y<=8&&ar[x][y]!=' '&&turn[x][y]==count) { //&&turn[x][y]==count
						clear_scr();
						print_board();
						gaming();
						break;
					}
				}
			}
			//clear_scr();
			//print_board();
			cout<<"Enter the final location..    changed your mind? send 0O\n";
			cin>>x2>>ch2;
			ch2=toupper(ch2);
			if(x2!=0 && ch2!='O') {
				y2=ch2-64;
				if(!(x2>=1&&x2<=8&&y2>=1&&y2<=8&&movecheck(ar[x][y],x,y,x2,y2)))
					while(1) {
						r();
						cout<<"invalid choose!!!  try again..\n";
						w();
						cin>>x2>>ch2;
						ch2=toupper(ch2);
						y2=ch2-64;
						if((x2>=1&&x2<=8&&y2>=1&&y2<=8&&movecheck(ar[x][y],x,y,x2,y2))) {
							clear_scr();
							break;
						}
						if(x2==0 && ch2=='O') {
							break;
						}
					}
				if(x2!=0 && ch2!='O') {
					if(ar[x2][y2]=='K'&&turn[x2][y2]==1) {
						g();
						cout<<"\n_______________ !!! Green Player is winner !!! _______________\n";
						w();
						return 0;
					}
					if(ar[x2][y2]=='K'&&turn[x2][y2]==2) {
						r();
						cout<<"\n_______________ !!! Red Player is winner !!! _______________\n";
						w();
						return 0;
					}
					if(ar[x2][y2]!=' '&&turn[x2][y2]==1) {
						if(ar[x2][y2]=='V'&&gvcnt==0) {
							ngreenkill[numkill[1]]=1;
							greenkill[numkill[1]]=ar[x2][y2];
							numkill[1]++;
							gvcnt++;
						} else if(ar[x2][y2]=='V'&&gvcnt!=0) {
							ngreenkill[numkill[1]]=1;
							greenkill[numkill[1]]='S';
							numkill[1]++;
						} else if(ar[x2][y2]!='V') {
							ngreenkill[numkill[1]]=1;
							greenkill[numkill[1]]=ar[x2][y2];
							numkill[1]++;
						}
					} else if(ar[x2][y2]!=' '&&turn[x2][y2]==2) {
						/*nredkill[numkill[2]]=1;
						redkill[numkill[2]]=ar[x2][y2];
						numkill[2]++;*/
						if(ar[x2][y2]=='V'&&rvcnt==0) {
							nredkill[numkill[2]]=1;
							redkill[numkill[2]]=ar[x2][y2];
							numkill[2]++;
							rvcnt++;
						} else if(ar[x2][y2]=='V'&&rvcnt!=0) {
							nredkill[numkill[2]]=1;
							redkill[numkill[2]]='S';
							numkill[2]++;
						} else if(ar[x2][y2]!='V') {
							nredkill[numkill[2]]=1;
							redkill[numkill[2]]=ar[x2][y2];
							numkill[2]++;
						}

					}
					ar[x2][y2]=ar[x][y];
					turn[x2][y2]=turn[x][y];
					if(ar[x2][y2]=='S'&&x2==1) {
						turn[x2][y2]=2;
						ar[x2][y2]='V';
					} else if(ar[x2][y2]=='S'&&x2==8) {
						turn[x2][y2]=1;
						ar[x2][y2]='V';
					}

					clear(x, y);
					if(count==2)
						count=1;
					else if(count==1)
						count=2;
				}
			}
		} else if(x==0&&(ch=='S'||ch=='R'||ch=='H'||ch=='E'||ch=='V')&&check_insert(ch)) {
			cout<<"Now, Please choose location for insert: ";
			cin>>x2>>ch2;
			ch2=toupper(ch2);
			y2=ch2-64;
			if(!(x2>=1&&x2<=8&&y2>=1&&y2<=8&&ar[x2][y2]==' '))
				while(1) {
					r();
					cout<<"invalid choose!!!  try again..\n";
					w();
					cin>>x2>>ch2;
					ch2=toupper(ch2);
					y2=ch2-64;
					if(x2>=1&&x2<=8&&y2>=1&&y2<=8&&ar[x2][y2]==' ') {
						clear_scr();
						break;
					}
				}

			if(ch=='S'&&(x2==1||x2==8))
				while(1) {
					r();
					cout<<"invalid choose!!!  try again..\n";
					w();
					cin>>x2>>ch2;
					ch2=toupper(ch2);
					y2=ch2-64;
					if(x2>=1&&x2<=8&&y2>=1&&y2<=8&&ar[x2][y2]==' '&&x2!=1&&x2!=8) {
						//clear_scr();
						break;
					}
				}

			ar[x2][y2]=ch;
			if(count==2)
				turn[x2][y2]=2;
			else if(count==1)
				turn[x2][y2]=1;
			if(count==2)
				greenkill[numinsert]=' ';
			else if(count==1)
				redkill[numinsert]=' ';

			if(count==2)
				count=1;
			else if(count==1)
				count=2;
		}
	}
}
//3 12
void r() {
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 4); //12
}
void g() {
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10); // 10 or 2
}
void w() {
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 7);
}
void b() {
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 9);
}
void wb() {
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 3);
}
void first_move() {
	for(int x=2; x<=7; x++)
		for(int y=1; y<=8; y++)
			if(x==2||x==7)
				ar[x][y]='S';
			else
				ar[x][y]=' ';
	ar[1][1]=ar[1][8]=ar[8][1]=ar[8][8]='R';
	ar[1][2]=ar[1][7]=ar[8][2]=ar[8][7]='H';
	ar[1][3]=ar[1][6]=ar[8][3]=ar[8][6]='E';
	ar[1][4]=ar[8][4]='V';
	ar[1][5]=ar[8][5]='K';
	for(int x=1; x<=2; x++)
		for(int y=1; y<=8; y++)
			turn[x][y]=1;
	for(int x=7; x<=8; x++)
		for(int y=1; y<=8; y++)
			turn[x][y]=2;
}
void welcome() {
	b();
	cout<<"            !!! Welcome to Chess !!!"<<endl<<endl;
	g();
	cout<<"For play new Game with your friend, enter 1 :"<<endl;
	r();
	cout<<"Or if you want exit, enter 2                \n\n";
	w();
}
void gaming() {
	cout<<"\nPlease enter the location you want change(example 3 A)   ";
	if(count==2) {
		g();
		cout<<"* Green Player, your turn *\n";
		w();
		cout<<"Or if you want insert from the outside, enter it(example 0 R)\n";
	} else if(count==1) {
		r();
		cout<<"* Red Player, your turn *\n";
		w();
		cout<<"Or if you want insert from the outside, enter it(example 0 R)\n";
	}
}
void clear(int x, int y) {
	ar[x][y]=' ';
	turn[x][y]=0;
}
bool movecheck(char ch, int x, int y, int x2, int y2) {
	if(ch=='S')
		return (sarbaz(x,y,x2,y2));
	else if(ch=='H')
		return(asb(x,y,x2,y2));
	else if(ch=='R')
		return (rokh(x,y,x2,y2));
	else if(ch=='K')
		return (king(x,y,x2,y2));
	else if(ch=='E')
		return (fiil(x,y,x2,y2));
	else if(ch=='V')
		return (fiil(x,y,x2,y2)||rokh(x,y,x2,y2));
	else
		return 0;
}
bool sarbaz(int x,int y,int x2,int y2) {
	if(turn[x][y]==2&&x==7&&ar[x2][y2]==' '&&y==y2&&(x2==6||x2==5)) {
		return 1;
	} else if(turn[x][y]==1&&x==2&&ar[x2][y2]==' '&&y==y2&&(x2==3||x2==4)) {
		return 1;
	} else if(turn[x][y]==1&&y==y2&&ar[x2][y2]==' '&&x2==x+1)
		return 1;
	else if(turn[x][y]==2&&y==y2&&ar[x2][y2]==' '&&x2==x-1)
		return 1;
	else if(turn[x][y]==1&&x2==x+1&&ar[x2][y2]!=' '&&(y2==y+1||y2==y-1))
		return 1;
	else if(turn[x][y]==2&&x2==x-1&&ar[x2][y2]!=' '&&(y2==y+1||y2==y-1))
		return 1;
	else
		return 0;
}
bool asb(int x,int y,int x2, int y2) {
	if((turn[x][y]!=turn[x2][y2]&&y2==y+2&&(x2==x+1||x2==x-1))||(turn[x][y]!=turn[x2][y2]&&y2==y-2&&(x2==x+1||x2==x-1)))
		return 1;
	else if((turn[x][y]!=turn[x2][y2]&&x2==x+2&&(y2==y+1||y2==y-1))||(turn[x][y]!=turn[x2][y2]&&x2==x-2&&(y2==y+1||y2==y-1)))
		return 1;
	else
		return 0;
}
bool rokh(int x,int y,int x2,int y2) {
	if(turn[x][y]!=turn[x2][y2]&&(x2==x+1||x2==x-1)&&y==y2)
		return 1;
	else if(turn[x][y]!=turn[x2][y2]&&(y2==y+1||y2==y-1)&&x==x2)
		return 1;
	else if(x==x2&&turn[x][y]!=turn[x2][y2]) {
		if(y2-y>1) {
			int t=0;
			for(int i=y+1; i<y2; i++) {
				if(ar[x][i]==' ')
					t++;
				if(t==y2-y-1)
					return 1;
			}
			return 0;
		} else if(y-y2>1) {
			int t=0;
			for(int i=y2+1; i<y; i++) {
				if(ar[x][i]==' ')
					t++;
				if(t==y-y2-1)
					return 1;
			}
			return 0;
		}
	} else if(y==y2&&turn[x][y]!=turn[x2][y2]) {
		if(x2-x>1) {
			int t=0;
			for(int i=x+1; i<x2; i++) {
				if(ar[i][y]==' ')
					t++;
				if(t==x2-x-1)
					return 1;
			}
			return 0;
		} else if(x-x2>1) {
			int t=0;
			for(int i=x2+1; i<x; i++) {
				if(ar[i][y]==' ')
					t++;
				if(t==x-x2-1)
					return 1;
			}
			return 0;
		}
	} else
		return 0;
}
bool fiil(int x,int y,int x2,int y2) {
	if((x2==x+1&&y2==y+1&&turn[x][y]!=turn[x2][y2])||(x2==x+1&&y2==y-1&&turn[x][y]!=turn[x2][y2])||(x2==x-1&&y2==y+1&&turn[x][y]!=turn[x2][y2])||(x2==x-1&&y2==y-1&&turn[x][y]!=turn[x2][y2]))
		return 1;
	else if(turn[x][y]!=turn[x2][y2]&&x2>x&&y2>y&&y2-y==x2-x) {
		int t=0;
		int i,j;
		for(i=x+1,j=y+1; i<x2,j<y2; i++,j++) {
			if(ar[i][j]==' ')
				t++;
			if(t==x2-x-1)
				return 1;
		}
		return 0;
	} else if(turn[x][y]!=turn[x2][y2]&&x2<x&&y2<y&&x-x2==y-y2) {
		int t=0;
		int i,j;
		for(i=x2+1,j=y2+1; i<x,j<y; i++,j++) {
			if(ar[i][j]==' ')
				t++;
			if(t==x-x2-1)
				return 1;
		}
		return 0;
	} else if(turn[x][y]!=turn[x2][y2]&&x2<x&&y2>y&&x-x2==y2-y) {
		int t=0;
		int i,j;
		for(i=x-1,j=y+1; i>x2,j<y2; i--,j++) {
			if(ar[i][j]==' ')
				t++;
			if(t==x-x2-1)
				return 1;
		}
		return 0;
	} else if(turn[x][y]!=turn[x2][y2]&&x2>x&&y2<y&&x2-x==y-y2) {
		int t=0;
		int i,j;
		for(i=x2-1,j=y2+1; i>x,j<y; i--,j++) {
			if(ar[i][j]==' ')
				t++;
			if(t==y-y2-1)
				return 1;
		}
		return 0;
	} else
		return 0;
}
bool king(int x,int y,int x2,int y2) {
	if((x2==x+1&&y2==y+1&&turn[x][y]!=turn[x2][y2])||(x2==x+1&&y2==y-1&&turn[x][y]!=turn[x2][y2])||(x2==x-1&&y2==y+1&&turn[x][y]!=turn[x2][y2])||(x2==x-1&&y2==y-1&&turn[x][y]!=turn[x2][y2]))
		return 1;
	else if(turn[x][y]!=turn[x2][y2]&&(x2==x+1||x2==x-1)&&y==y2)
		return 1;
	else if(turn[x][y]!=turn[x2][y2]&&(y2==y+1||y2==y-1)&&x==x2)
		return 1;
	else
		return 0;
}
bool check_insert(char ch) {
	if(count==1) {
		for(int i=0; nredkill[i]==1; i++)
			if(redkill[i]==ch) {
				numinsert=i;
				return 1;
			}
	} else if(count==2) {
		for(int i=0; ngreenkill[i]==1; i++)
			if(greenkill[i]==ch) {
				numinsert=i;
				return 1;
			}
	}
	return 0;
}