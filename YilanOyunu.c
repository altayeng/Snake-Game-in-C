#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int lenght, bend_time, len, life;
char key;
void record();
int printscore();
long double delaytime;
int skor();
void delay(long double);
void med(long double);
void hard(long double);
void action();
void eat();
void coordinate(int x, int y);
void headxy(int x,int y);
void foldPoint();
void playground();
void moveDown();
void moveLeft();
void moveUp();
void moveRight();
void endGame();
void Menu();
void spawn();

struct crdnte
{
    int x,y,direction;
};

typedef struct crdnte crdnte;

crdnte head, bend[500],food,body[30];

int main()
{
	Menu();
	system("cls");
	 
	int secim;
	coordinate(25,14);
	printf("Select game difficulty(1-2-3): ");
	scanf("%d",&secim);
	
    char key;

    system("cls");

    

    lenght=5;

	spawn();
//playground oluþturduk ve içine eat atadýk
    playground();
    eat();

    life=secim;

    bend[0]=head;

    action();
    
    //bu if bloðundan zorluða göre hýz oluþturulacak.
if(secim==1){
	delaytime = 100000000;
}
else if (secim==2){
	delaytime = 100000;
}
else {
	delaytime = 10000;
}
//


    return 0;
}

void delay(long double delaytime)
{
	
    skor();
    long double i;
//for içindeki 100000 deðeri, yýlanýn hýzýný belirliyor.
//TODO: bunu bir þekilde main içindeki delaytime ile almamýz lazým.
    for(i=0; i<=5000000; i++);
}

void spawn()
{
	//yýlan nerede spawn olacak belirtiyoruz.
    head.x=25;
    head.y=20;
    head.direction=RIGHT;

}

void Menu()
{

char in, c;
  FILE *info = fopen("record.txt", "r");
  	system("cls");

  	coordinate(15,14);
	printf("\t\tDou you want to see old scores? (y/n)");
	in=getch();
 	if(in=='y')
    {
    	system("cls");
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    fclose(info);
    	 printf("\n\n Press any key to continue");
 getch();
    }
	
    
}

void action()
{
    int a,i;

    do
    {

        eat();
        fflush(stdin);

        len=0;

        for(i=0; i<30; i++)

        {

            body[i].x=0;

            body[i].y=0;

            if(i==lenght)

                break;

        }

       delay(delaytime);

        playground();

        if(head.direction==RIGHT)

            moveRight();

        else if(head.direction==LEFT)

            moveLeft();

        else if(head.direction==DOWN)

            moveDown();

        else if(head.direction==UP)

            moveUp();

        endGame();

    }
    while(!kbhit());

    a=getch();

    if(a=='m')

    {
    	 system("cls");
    	 coordinate(15,14);
		printf("Do you want to return to the main menu?(y/n)");
    	a=getch();
    	
    	if(a=='y') {
		
		system("cls");
			Menu();  
    }
	}
    	
	
    
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))

    {

        bend_time++;

        bend[bend_time]=head;

        head.direction=key;

        if(key==UP)

            head.y--;

        if(key==DOWN)

            head.y++;

        if(key==RIGHT)

            head.x++;

        if(key==LEFT)

            head.x--;

        action();

    }

    else if(key==27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        action();

    }
}

void coordinate(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void headxy(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void moveDown()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_time].y)&&len<lenght; i++)
    {
        headxy(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("|");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    foldPoint();
    if(!kbhit())
        head.y++;
}
//karakter hayatta mý onu kontrol ediyoruz
void endGame()
{
    int i,check=0;

    for(i=2; i<lenght; i++)
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {	//baþýn vücuda göre koordinat oranýný kontrol ediyoruz.
            check++;  
        }
        if(i==lenght||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>0)
        {
            head.x=25;
            head.y=20;
            bend_time=0;
            head.direction=RIGHT;
            action();
        }
        else
        {
            system("cls");
            printf("Game Over");
            record();
            exit(0);
        }
    }
}
void eat()
{
    if(head.x==food.x&&head.y==food.y)
    {
        lenght++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    //burada yemek oluþturuyoruz.
    else if(food.x==0) 
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void moveLeft()
{
    int i;
    for(i=0; i<=(bend[bend_time].x-head.x)&&len<lenght; i++)
    {
        headxy((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("-");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    foldPoint();
    if(!kbhit())
        head.x--;

}
void moveRight()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_time].x)&&len<lenght; i++)
    {
       
        body[len].x=head.x-i;
        body[len].y=head.y;
        headxy(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("-");
        }
       	
        len++;
    }
    foldPoint();
    if(!kbhit())
        head.x++;
}
void moveUp()
{
    int i;
    for(i=0; i<=(bend[bend_time].y-head.y)&&len<lenght; i++)
    {
        headxy(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("|");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    foldPoint();
    if(!kbhit())
        head.y--;
}
void foldPoint()
{
    int i,j,diff;
    for(i=bend_time; i>=0&&len<lenght; i--)
    {
       if(bend[i].x==bend[i-1].x)
      {
        diff=bend[i].y-bend[i-1].y;
        if(diff<0)
         for(j=1; j<=(-diff); j++)
    {
        body[len].x=bend[i].x;
        body[len].y=bend[i].y+j;
        headxy(body[len].x,body[len].y);
        printf("|");
        len++;
        if(len==lenght)
        break;
    }
        else if(diff>0)
             for(j=1; j<=diff; j++)
          {
            headxy(bend[i].x,(bend[i].y-j));
            printf("|");
            len++;
            if(len==lenght)
            break;
          }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<lenght; j++)
                {
                    headxy((bend[i].x+j),bend[i].y);
                    printf("-");
                    len++;
                    if(len==lenght)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<lenght; j++)
                {
                    headxy((bend[i].x-j),bend[i].y);
                    printf("-");
                    len++;
                    if(len==lenght)
                        break;
                }
        }
    }
}

//playground çizimi.
void playground()
{
    system("cls");
    int i;
    //ekranda rastgele yemek bastýrýyor
    headxy(food.x,food.y);   
    printf("+");
    for(i=10; i<71; i++)
    {
        headxy(i,10);
        printf("X");
        headxy(i,30);
        printf("X");
    }
    for(i=10; i<31; i++)
    {
        headxy(10,i);
        printf("X");
        headxy(70,i);
        printf("X");
    }
}

//tahtaya skor ve life yazdýrýyor
int skor()
{
    int score;
    headxy(35,8);
    score=lenght-5;
    printf("Score : %d",(lenght-5));
    score=lenght-5;
    headxy(35,7);
    printf("Life  : %d",life);
    return score;
}
int printscore()
{
    int score=skor();
    system("cls");
    return score;
}


void record()
{
    char plname[30],nplname[30],in,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Name:\n");
    scanf("%[^\n]",plname);
    for(j=0; plname[j]!='\0'; j++) 
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
   
    fprintf(info,"Player :%s\n",nplname);

    time_t date;
    date = time(NULL);
    fprintf(info,"Played time:%s",ctime(&date));
    fprintf(info,"Score:%d\n",px=printscore());
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    
    printf("Dou you want to see old scores? (y/n)");
    in=getch();
    system("cls");
    if(in=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    getch();
    
    fclose(info);
    
    system("cls");

}

