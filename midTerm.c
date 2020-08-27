COP And Rubber.c#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

void first_location (int copst);
void show_map ();
void robber_movement ();
void cops_movement (int copst);
int check_awareness (int x,int copst);
void awareness (int copst);
void cops_movement (int copst);
void textcolor (int color);
int safe (int xprime, int yprime, int u);

int map[100][100], robx, roby, cop_count[100], i, j, cops[100][100][2], flag, aware_cop[100][10],rubmove=0,copmove=0,copst,winner[10],nrob,robbers[10][2];

int main()
{
    srand(time(0));
    char o,str[]= {"HELLOW!. WELCOME TO COPS AND ROBBER GAME!!! :) :)"};
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t");
    for(int u=0; u<strlen(str); u++)
    {
        textcolor(u+1);
        if(u>33)
        {
            textcolor(u-33);
        }
        else if(u>27)
        {
            textcolor(u-27);
        }
        else if(u>18)
        {
            textcolor(u-18);
        }
        else if(u>9)
        {
            textcolor(u-9);
        }
        printf("%c",str[u]);
        usleep(50000);
    }
    usleep(500000);
    printf("\n\n");
    textcolor(13);
    printf("ENTER ANY KEY TO CONTINUE.\n");
    scanf("%c",&o);
    int copst,time_past=0;
    printf("ENTER SIZE OF MAP:\n");
    scanf("%d %d",&i,&j);
    for(int f=0; f<100; f++)
    {
        for(int h=0; h<100; h++)
        {
            map[f][h]=-200;
        }
    }
    for(int m=0; m<i; m++)
    {
        for(int d=0; d<j; d++)
        {
            map[m][d]=-100;
        }
    }
    textcolor(4);
    printf("ENTER NUMBER OF ROBBERS : \n");
    scanf("%d",&nrob);
    textcolor(2);
    printf("ENTER NUMBER OF POLLICE STATION :\n");
    scanf("%d",&copst);
    for(int q=0; q<copst; q++)
    {
        textcolor(1);
        printf("ENTER NUMBER OF COPS IN STATION %d :\n",q+1);
        scanf("%d",&cop_count[q]);
    }
    first_location(copst);
    printf("FIRST LOOK AT PLAYGROUND : \n");
    show_map();
    usleep(900000);
    //system("cls");
    while(1)
    {
        system("cls");
        robber_movement();
        //show_map();
        cops_movement(copst);
        show_map();
        time_past++;
        printf("time : %d\n",time_past);
        usleep(900000);
        int r=0;
        for(int q=0; q<i; q++)
        {
            for(int m=0; m<j; m++)
            {
                if(map[q][m]==-1)
                {
                    r++;
                }
            }
        }
        if(r==0)
        {
            break;
        }
    }
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\a");
    textcolor(1);
    printf("TIME PAST : ");
    textcolor(6);
    printf("%d\n",time_past);
    textcolor(1);
    printf("ROBBER MOVEMENTS : ");
    textcolor(6);
    printf("%d\n",rubmove);
    textcolor(1);
    printf("COPS MOVEMENTS : ");
    textcolor(6);
    printf("%d\n",copmove);
    textcolor(1);
    printf("TOTAL MOVEMENTS : ");
    textcolor(6);
    printf("%d\n",rubmove+copmove);
    textcolor(1);
    for(int e=0; e<nrob; e++)
    {
        printf("ROBBER %d CAPTURED BY STATION : ",e+1);
        textcolor(2);
        printf("%d\n",winner[e]);
        textcolor(1);
    }
    textcolor(8);
    printf("\n\n\n");
    return 0;
}
void show_map ()
{
    for(int q=0; q<i; q++)
    {
        for(int m=0; m<j; m++)
        {
            if(map[q][m]==-1)
            {
                textcolor(4);
                printf("  R ");
            }
            else if(map[q][m]>0)
            {
                textcolor(2);
                printf(" P%d ",map[q][m]);
            }
            else
            {
                textcolor(14);
                printf(" .. ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
void robber_movement ()
{
    int xprime, yprime;
    for(int u=0; u<nrob; u++)
    {
        if(robbers[u][0]!=-2000)
        {
            for(int f=0; f<100; f++)
            {
                xprime=(rand()%3)-1;
                yprime=(rand()%3)-1;
                if(map[robbers[u][0]+xprime][robbers[u][1]+yprime]==-100 )
                {
                    if(!safe(xprime, yprime, u))
                    {
                        map[robbers[u][0]][robbers[u][1]]=-100;
                        map[robbers[u][0]+xprime][robbers[u][1]+yprime]=-1;
                        robbers[u][0]+=xprime;
                        robbers[u][1]+=yprime;
                        rubmove++;
                        break;
                    }
                }
            }
        }
    }
}
void first_location (int copst)
{
    int x1, y1;
    for(int u=0; u<nrob; u++)
    {
        while(1)
        {
            robbers[u][0]=rand()%i;
            robbers[u][1]=rand()%j;
            if(map[robbers[u][0]][robbers[u][1]]==-100)
            {
                map[robbers[u][0]][robbers[u][1]]=-1;
                break;
            }
        }
    }
    for(int q=0; q<copst; q++)
    {
        for(int m=0; m<cop_count[q]; m++)
        {
            do
            {
                x1=rand()%i;
                y1=rand()%j;
            }
            while(map[x1][y1]!=-100);
            map[x1][y1]=q+1;
            cops[q+1][m+1][0]=x1;
            cops[q+1][m+1][1]=y1;
        }
    }
}
void awareness (int copst)
{
    for(int x=0; x<copst; x++)
    {
        for(int r=0; r<cop_count[x]; r++)
        {
            for(int u=0; u<nrob; u++)
            {
                if((cops[x+1][r+1][0]-robbers[u][0])*(cops[x+1][r+1][0]-robbers[u][0])+(cops[x+1][r+1][1]-robbers[u][1])*(cops[x+1][r+1][1]-robbers[u][1]))
                {
                    aware_cop[x][u]=x+1;
                    break;
                }
            }
        }
    }
}
int check_awareness (int x,int copst)
{
    int counter=0;
    for(int u=0; u<nrob; u++)
    {
        if(aware_cop[x][u]==x+1)
        {
            return u;
            break;
            counter++;
        }
    }
    if(counter==0)
    {
        return -1;
    }
}
void textcolor (int color)
{
    static int __BACKGROUND;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 2));
}
void cops_movement (int copst)
{
    for(int x=0; x<copst; x++)
    {
        for(int r=0; r<cop_count[x]; r++)
        {
            int xprime, yprime;
            for(int u=0; u<nrob; u++)
            {
                if(fabs(cops[x+1][r+1][0]-robbers[u][0])<=1 && fabs(cops[x+1][r+1][1]-robbers[u][1])<=1 && flag!=1)
                {
                    if(map[robbers[u][0]][robbers[u][1]]==-1)
                    {
                        map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                        map[robbers[u][0]][robbers[u][1]]=x+1;
                        cops[x+1][r+1][0]=robbers[u][0];
                        cops[x+1][r+1][1]=robbers[u][1];
                        robbers[u][0]=-2000;
                        robbers[u][1]=-2000;
                        winner[u]=x+1;
                        break;
                    }
                }
            }
            if(check_awareness(x,copst)>=0)//aware cops moving
            {
                int deltax,deltay;
                deltax=cops[x+1][r+1][0]-robbers[check_awareness(x,copst)][0];
                deltay=cops[x+1][r+1][1]-robbers[check_awareness(x,copst)][1];
                if(deltax==0)
                {
                    if(deltay>0)
                    {
                        if(map[cops[x+1][r+1][0]][cops[x+1][r+1][1]-1]==-100)
                        {
                            map[cops[x+1][r+1][0]][cops[x+1][r+1][1]-1]=x+1;
                            cops[x+1][r+1][1]-=1;
                            map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                        }
                    }
                    else
                    {
                        if(map[cops[x+1][r+1][0]][cops[x+1][r+1][1]+1]==-100)
                        {
                            map[cops[x+1][r+1][0]][cops[x+1][r+1][1]+1]=x+1;
                            cops[x+1][r+1][1]+=1;
                            map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                        }
                    }
                }
                else if(deltay==0)
                {
                    if(deltax>0)
                    {
                        if(map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]]==-100)
                        {
                            map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]]=x+1;
                            cops[x+1][r+1][0]-=1;
                            map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                        }
                    }
                    else
                    {
                        if(map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]]==-100)
                        {
                            map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]]=x+1;
                            cops[x+1][r+1][0]+=1;
                            map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                        }
                    }
                }
                else
                {
                    if(deltax>0)
                    {
                        if(deltay>0)
                        {
                            if(map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]-1]=-100)
                            {
                                map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]-1]=x+1;
                                cops[x+1][r+1][0]-=1;
                                cops[x+1][r+1][1]-=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]]=-100)
                            {
                                map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]]=x+1;
                                cops[x+1][r+1][0]-=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]][cops[x+1][r+1][1]-1]=-100)
                            {
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]-1]=x+1;
                                cops[x+1][r+1][1]-=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                        }
                        else//deltay<0 && deltax>0
                        {
                            if(map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]+1]=-100)
                            {
                                map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]+1]=x+1;
                                cops[x+1][r+1][0]-=1;
                                cops[x+1][r+1][1]+=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]]=-100)
                            {
                                map[cops[x+1][r+1][0]-1][cops[x+1][r+1][1]]=x+1;
                                cops[x+1][r+1][0]-=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]][cops[x+1][r+1][1]+1]=-100)
                            {
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]+1]=x+1;
                                cops[x+1][r+1][1]+=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                        }
                    }
                    else//deltax<0
                    {
                        if(deltay>0)
                        {
                            if(map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]-1]=-100)
                            {
                                map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]-1]=x+1;
                                cops[x+1][r+1][0]+=1;
                                cops[x+1][r+1][1]-=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]]=-100)
                            {
                                map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]]=x+1;
                                cops[x+1][r+1][0]+=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]][cops[x+1][r+1][1]-1]=-100)
                            {
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]-1]=x+1;
                                cops[x+1][r+1][1]-=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                        }
                        else//deltay<0 && deltax<0
                        {
                            if(map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]+1]=-100)
                            {
                                map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]+1]=x+1;
                                cops[x+1][r+1][0]+=1;
                                cops[x+1][r+1][1]+=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]]=-100)
                            {
                                map[cops[x+1][r+1][0]+1][cops[x+1][r+1][1]]=x+1;
                                cops[x+1][r+1][0]-=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                            else if(map[cops[x+1][r+1][0]][cops[x+1][r+1][1]+1]=-100)
                            {
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]+1]=x+1;
                                cops[x+1][r+1][1]+=1;
                                map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                            }
                        }
                    }//end deltax<0
                }
            }//end of smart move
            else//random move for cops
            {
                do
                {
                    xprime=(rand()%3)-1;
                    yprime=(rand()%3)-1;
                    /*if(map[cops[x+1][r+1][0]+xprime][cops[x+1][r+1][1]+yprime]==-1)
                    {
                        map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                        map[cops[x+1][r+1][0]+xprime][cops[x+1][r+1][1]+yprime]=x+1;
                        flag=0;
                        winner=x+1;
                        break;
                    }*/
                }
                while(map[cops[x+1][r+1][0]+xprime][cops[x+1][r+1][1]+yprime]!=-100 && map[cops[x+1][r+1][0]+xprime][cops[x+1][r+1][1]+yprime]==-200);
                if(map[cops[x+1][r+1][0]+xprime][cops[x+1][r+1][1]+yprime]==-100)
                {
                    map[cops[x+1][r+1][0]][cops[x+1][r+1][1]]=-100;
                    map[cops[x+1][r+1][0]+xprime][cops[x+1][r+1][1]+yprime]=x+1;
                    cops[x+1][r+1][0]+=xprime;
                    cops[x+1][r+1][1]+=yprime;
                }
            }
            copmove++;
        }
    }//end of copst for
}//end of cops movement
int safe (int xprime, int yprime, int u)
{
    for(int w=robbers[u][0]-1;w<robbers[u][0]+2;w++)
    {
        for(int p=robbers[u][1]-1;p<robbers[u][1]+2;p++)
        {
            if(map[w][p]>0)
            {
                return 1;
            }
        }
    }
    return 0;
}
