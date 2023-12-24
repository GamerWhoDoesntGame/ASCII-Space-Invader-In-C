#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
 
//Declaring and initialising global variables used throughout the program
int count=0;
int score=0;
char ch;
int dead;
int victory =1;
int drop1, drop2;
int row = 25;
int col = 40;
char player= 'A';
char enemy = 'O';
char enemyShield = 'W';
char laser = '^';
char explosion = 'X';
char enemyLaser ='u';
char keyPress;
char direction;
int aF=0;
int alienFlag=0;
 
 
 
//initialising the world where the game will be played, i.e.,a character matrix
char world[25][40] =
    {
            "*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        *",
            "*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        *",
            "*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        *",
            "*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        *",
            "*MMMMMMMMMMMMMMMMMMMMMMMMMMMMM        *",
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *", 
            "*                                     *",
            "*                                     *"
              
    };
 
 
//print function to print the world over and over
void print()
{
    /*printing world*/
    system("cls");  
    printf("\nScore : %d\n\n", score); 
    for(int y=0; y<row; y++)
    {
        for(int x=0; x<col ; x++)
        {
            printf("%c",world[y][x]);
        }
        printf("\n");
    }
    Sleep(200);
}
 
 
 
//still in progress
/*void readFile(FILE * fPtr)
{
    char ch;
    do 
    {
        ch = fgetc(fPtr);
 
        putchar(ch);
 
    } while (ch != EOF);
}*/
 
 
//function to print you lost
void youLost()
{
    victory=0;
    system("cls");
    printf("\n\nYOU LOST\n\n");
    printf("%d",score);
    getch();
}
 
 
//function to print you won
void youWon()
{
    system("cls");
    system("cls");
    printf("\n\nYOU WON!!!\n\n");
    printf("%d",score);
    getch();
 
}
 
/*still in progress
int charPresent(char a[],char c)
{
    for(int i=0; i<col; i++ )
    {
        if(a[i]!=c)
        {
            return 0;
        }
 
    }
    
}*/
 
//-------------------------Player's laser's functions-----------------------------------------------------------------------
 
//function for player's laser travelling vertically
void laser_travel()
{
    for(int y=0;y<row;y++)
        {
            for(int x=0;x<col;x++)
            {
                if(world[y][x]== '^')
                {
                    world[y-1][x]='^';
                    world[y][x]=' ';
                }
 
            }
        }
}
 
//function for player's laser removal on the first row
void laser_remove()
{
    for(int x=0; x<col ; x++)
    {
        if(world[0][x]== '^')
        {
            world[0][x]= ' ';
        }
        
    }
}
 
//function for player's laser impact on alien ship
void laser_impact()
{
    for(int y=0; y<row ;y++)
    {
        for(int x=0; x<col ; x++)
        {
            if(world[y][x]=='^' && world[y-1][x]=='M')
            {
                world[y-1][x]='@';
                world[y][x]=' ';
                score+=50;
                
    
            }
            if(world[y][x]=='^' && world[y-1][x]== '@')
            {
                world[y-1][x]=' ';
                world[y][x]=' ';
 
                score+=100;
                
            }
            
        }
    }
}
 
 
//--------------------------Alien's bomb's functions--------------------------------------------------------------------------
//Alien's Bomb drop using rand fucntion
void bomb_drop()
{
    
    int num = rand()%7;
    for(int i=1;i<num;i++)
    {
        int var = rand()%37+1;
        for(int y=row; y>0; y--)
        {
            if((world[y][var]=='M' || world[y][var]=='@') && world[y+1][var]==' ')
            {
                world[y+1][var]='v';
                break;
            }
        }
    }
    
}
 
//Alien's bomb travel
void bomb_travel()
{
    for(int y=23; y>0; y--)
    {
        for(int x=37; x>=1; x--)
        {
            if(world[y][x]=='v')
            {
                
                world[y][x]=' ';
                world[y+1][x]='v';
            }
        }
    }
}
 
//Alien's bomb nullifying in the last row function
void bomb_nullify()
{
    for(int x=1;x<col; x++)
    {
        if(world[23][x]=='v' && world[24][x]=='A')
        {
            world[23][x]=' ';
            world[24][x]='X';
 
        }
        if(world[24][x]=='v')
        {
            world[24][x]=' ';
        }
    }
}
 
 
//---------------------------Alien Ship movement function----------------------------------------------------------------------
//Function for Alien ship movement leftwards
void alienMovementL()
{
    for(int y=0; y<row; y++)
    {
        if(world[y][1]==' ' && alienFlag == 0)
        {
            for(int x=0; x<col ; x++)
            {
                if(world[y][x]=='@')
                {
                    world[y][x]=' ';
                    world[y][x-1]='@';
                }
                if(world[y][x]=='M')
                {
                    world[y][x]=' ';
                    world[y][x-1]='M';
                }
            }
        }
        else if(world[1][1]=='@' || world[2][1]=='@' || world[3][1]=='@' || world[4][1]=='@' || world[5][1]=='@'|| world[6][1]=='@'
        || world[7][1]=='@'  || world[8][1]=='@'  || world[9][1]=='@'  || world[10][1]=='@' || world[11][1]=='@' || world[12][1]=='@'
        || world[13][1]=='@' || world[14][1]=='@' || world[15][1]=='@' || world[16][1]=='@' || world[17][1]=='@' || world[18][1]=='@'
        || world[19][1]=='@' || world[20][1]=='@' || world[21][1]=='@' || world[22][1]=='@' || world[23][1]=='@' || world[24][1]=='@'        
        || world[5][1]== 'M' || world[6][1]=='M'  || world[7][1]=='M'  || world[8][1]=='M'  || world[9][1]=='M'   || world[10][1]=='M' 
        || world[11][1]=='M' || world[12][1]=='M' || world[13][1]=='M' || world[14][1]=='M' || world[15][1]=='M' || world[16][1]=='M' 
        || world[17][1]=='M' || world[18][1]=='M' || world[19][1]=='M' || world[20][1]=='M' || world[21][1]=='M' || world[22][1]=='M' 
        || world[23][1]=='M' || world[24][1]=='M' )
        {
            alienFlag= 1;
 
        }
    }
}
 
//Function for alien ship movement rightwards
void alienMovementR()
{
    for(int y=0; y<row; y++)
    {
        if(world[y][37]==' ' && alienFlag==1)
        {
            for(int x=37; x>=1 ; x--)
            {
                if(world[y][x]=='@')
                {
                    world[y][x]=' ';
                    world[y][x+1]='@';
                }
                if(world[y][x]=='M')
                {
                    world[y][x]=' ';
                    world[y][x+1]='M';
                }
            }
        }
        else if(world[1][37]=='@' || world[2][37]=='@' || world[3][37]=='@' || world[4][37]=='@' || world[5][37]=='@' || world[6][37]=='@'
        || world[7][37]=='@'  || world[8][37]=='@'  || world[9][37]=='@'  || world[10][37]=='@' || world[11][37]=='@' || world[12][37]=='@'
        || world[13][37]=='@' || world[14][37]=='@' || world[15][37]=='@' || world[16][37]=='@' || world[17][37]=='@' || world[18][37]=='@'
        || world[19][37]=='@' || world[20][37]=='@' || world[21][37]=='@' || world[22][37]=='@' || world[23][37]=='@' || world[24][37]=='@' 
        || world[5][37]=='M'  || world[6][37]=='M'  || world[7][37]=='M'  || world[8][37]=='M'  || world[9][37]=='M'  || world[10][37]=='M' 
        || world[11][37]=='M' || world[12][37]=='M' || world[13][37]=='M' || world[14][37]=='M' || world[15][37]=='M' || world[16][37]=='M' 
        || world[17][37]=='M' || world[18][37]=='M' || world[19][37]=='M' || world[20][37]=='M' || world[21][37]=='M' || world[22][37]=='M' 
        || world[23][37]=='M' || world[24][37]=='M' )
        {
            alienFlag= 0;
        }
    }
}
 
//Function for alien ship dropping
void alienDrop()
{
    for(int y=23; y>=0; y--)
    {
        for(int x=0; x<col; x++ )
        {
            if(world[y][x]=='M')
            {
                world[y][x]=' ';
                world[y+1][x]='M';
            }
            if(world[y][x]=='@')
            {
                world[y][x]=' ';
                world[y+1][x]='@';
            }
        }
    }
}
 
 
//Main Gameplay function which also contains condition for movement of player rightward and leftward
void gamePlay()
{
    world[24][19]=player;
    while(victory==1)
    {
            print();
            srand(time(NULL));
 
            if(kbhit())
            {
                keyPress = getch();
            }
            else
            {
                keyPress = ' ';
            }
            if(keyPress == 'a')
            {
                for(int x=1; x<col ; x=x+1)
                {
                    if(world[row-1][x+1]==player)
                    {
                        world[row-1][x]=player;
                        world[row-1][x+1]=' ';
                    }
                }
                //print();
        
            }
            if(keyPress == 'd')
            {
                for(int x = col - 3; x > 0; x=x-1)
                {
                    if(world[row-1][x-1]==player)
                    {
                        world[row-1][x]=player;
                        world[row-1][x-1]= ' ';
                    }
                }
                // print();
            }
 
            if(keyPress == 'm')
            {
                //for(int y=23; y>0 ;y=y-1)
        
                for(int x=1; x<col; x=x+1)
                {
                    if(world[row-1][x]== player)
                    {
                        world[row-2][x]='^';
 
                    }
                }
        
 
            }
    
            //Quiting the Game
            if(keyPress== 'E')
            {
                victory = 0;
                printf("\n\n You Quit \n\n");
                Sleep(2000);
                //system("cls");
                printf("%d\n\n",score);
            }
        
 
            /*players laser*/
            laser_travel();
            laser_impact();
            laser_remove();
 
            
 
            /*Bomb Drop*/
            bomb_drop();
            bomb_travel();
            bomb_nullify();
            
 
            //alien movement
            alienMovementL();
            alienMovementR();
            
            //Condition for alien dropping one row down using rand function and count variable
            if(count!=0 && count%20==0)
            {
                alienDrop();
            }
 
            
            //Loop for player death(It has one bug)
            for(int x=0; x<col; x++)
            {   
                if(world[24][x]=='X' || world[23][x]=='@' || world[23][x]=='M')
                {
                    victory=0;
                    youLost();
 
                    Sleep(500);
                }
                //still in progress
                /*if(charPresent(world[24], 'A')==0 || charPresent(world[24],'X')==0)
                {
                    victory=0;
                    youLost();
 
                    Sleep(500);
                }*/
            
            }
 
        //conditon for winning the game    
        if(score==15950)
        {
            
            victory=0;
            youWon();
            Sleep(500);
        }
        count++;
    }
        
    print();   
}
 
 
//------------------------------------WELCOME SCREEN FUNCTION-------------------------------------------------------
void welcomeScreen()
{
    //-------------Game's Starting scene------------------------------------
    printf("WELCOME TO SPACE INVADERS \n\n");
    Sleep(1000);
    printf("ARE YOU READY TO EMBARK ON THIS EXHILARATING SPACE ADVENTURE\n\n");
    Sleep(1000);
    printf("DESTROY ENEMY SHIPS AND GAIN POINTS\n\n");
    Sleep(1000);
    printf("BUT BEWARE OF ENEMY LASERS\n\n");
    Sleep(1000);
 
 
    //------------------Menu---------------------------------------------------
    printf("Press 'M' for Menu ");
    //printf("Press any key to start");
    ch=getch();
    if(kbhit())
    {
        ch=getch();
    }
    if(ch== 'm')
    {   
        printf("m");
        system("cls");
        printf("\n\n******************************\n\n");
        printf("\n\n1. Play ");
        printf("\n\n2. Display Rules ");
        //printf("\n\n3. Show Score List ");
        printf("\n\n3. Exit \n\n");
        printf("\n\n******************************\n\n");
        printf("\n\nEnter your choice ");
 
        char ch= getch();
        /*if(kbhit())
        {
            c = getch();
        }
        else
        {
            c=' ';    
        }*/
        if(ch =='1')
        {
            printf("1");
            gamePlay();
        }
        if(ch == '2')
        {
            printf("2");
            system("cls");
            printf("Welcome to Space Invaders. Stop Alien's conquest by defeating them all.\n\n");
            printf("Rules are simple. You destroy an Alien Ship, You gain 100 points. You break through it's shield, you gain 50 points.\n");
            printf("Use keys A to move your ship left-ways and D to move your ship right-ways.\n ");
            printf("Use key M to shoot down aliens...\n\n\n");
            printf("BUT BEWARE OF ALIEN'S LASERS\n");
            printf("Enter 'b' to return to main menu ");
            char ch=getch();
            /*if(kbhit())
            {
                ch=getch();
            }
            else
            {
                ch= ' ';
            }*/
            if(ch=='b')
            {
                printf("b");
                system("cls");
                welcomeScreen();
            }
            
            
            /*else
            {
                
                ch=getch();
            }*/
 
        }
        /*if(ch == '3')
        {
            readFile(h_score);
        }*/
        if(ch == '3')
        {
            printf("3");
            Sleep(500);
            printf("\n\nYou Quit\n\n");
        } 
    }
    else
    {
        system("cls");
        welcomeScreen();
    }
 
}
 
 
int main()
{
    //FILE *h_score;
    //h_score = fopen("High Scores.txt", "a");
   /*displaying world*/
    welcomeScreen(); 
 
    //fputs(score, h_score);
    //fclose(h_score);
            
 
    return 0;
}