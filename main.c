#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

typedef struct
{
    int x;
    int y;
    char type;
    int energy;
    int empty;
} suck;
char visual_map[200][200];
void creat_map(int n,suck a[n+1][n+1]);
void textcolor (int color);
void print_map(char visual_map[200][200],int n);
int main()
{
    int n;
    char kind;
    FILE *fp;
    fp = fopen("map6.bin", "rb");
    fread(&n, sizeof(int), 1, fp);
    suck map[n+1][n+1];
    for(int i=0; i<5*n+3; i++)
    {
        for(int j=0; j<5*n; j++)
        {
            visual_map[i][j]='0';
        }
    }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                fread(&kind, sizeof(kind), 1, fp);
                map[i][j].type=kind;
                if(kind==1)
                {
                    map[i][j].energy=100;
                }
                else
                {
                     map[i][j].energy=0;
                }
                map[i][j].x=i;
                map[i][j].y=j;
            }
        }
        creat_map(n,map);
        print_map(visual_map,n);
        return 0;
    }
    void creat_map(int n,suck a[n+1][n+1])
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                int x_center=2+((n-1)*5)-(5*a[i][j].y);
                int y_center=2+(5*a[i][j].x);
                if(a[i][j].x%2!=0)
                    x_center+=3;
                for(int k=x_center-2; k<=x_center+2; k++)
                {
                    for(int d=y_center-2; d<=y_center+2; d++)
                    {
                        if(k>=0 && d>=0)
                        {
                            visual_map[k][d]=a[i][j].type;
                        }
                    }
                }
            }
        }
    }
    void print_map(char visual_map[200][200],int n)
    {
        getch();
        for(int i=0; i<5*n+3; i++)
        {
            for(int j=0; j<5*n; j++)
            {
                if(visual_map[i][j]=='1')
                {
                    textcolor(22);
                    printf("  ");
                }
                if(visual_map[i][j]=='2')
                {
                    textcolor(32);
                    printf("  ");
                }
                if(visual_map[i][j]=='3')
                {
                    textcolor(56);
                    printf("  ");
                }
                if(visual_map[i][j]=='4')
                {
                    textcolor(89);
                    printf("  ");
                }
                if(visual_map[i][j]=='0')
                {
                    textcolor(15);
                    printf("  ");
                }
                printf("%c",visual_map[i][j]);
            }
            printf("\n");
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
