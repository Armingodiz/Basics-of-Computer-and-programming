#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
    char type;
    int energy;
    int empty ;
} block;
struct  cell
{
    int x;
    int y;
    int energy;
    char name[50];
    int number_of_player;
    struct cell *next;
};
int number_of_cells,n,list1,list2;
void read_frome_file(block map[n+1][n+1],FILE *fp);
char visual_map[200][200];
void creat_map(int n,block a[n+1][n+1]);
void textcolor (int color);
void print_map(char visual_map[200][200],int n);
struct cell * create_cell(int x,int y,char *name,int number_of_player);
void add_end(struct cell *list, struct cell * new_node);
void creat_cell_list (int number,int n, block a[n+1][n+1],char visual_map[200][200],int number_of_player);
int show_list1 ();
int show_list2 ();
struct cell* show_and_choose_cell(int number_of_player);
void move_cell (struct cell *a,block map[n+1][n+1],int number_of_player);
void boost_energy (struct cell *a,block map[n+1][n+1]);
void split_cell (struct cell *a,block map[n+1][n+1]);
struct cell *header1,*header2,*choosen1,*choosen2;
int main()
{
    srand(time(0));
    FILE *fp;
    fp = fopen("map6.bin", "rb");
    fread(&n, sizeof(int), 1, fp);
    block map[n+1][n+1];
    read_frome_file(map,fp);
    switch(show_list1())
    {
    case 1:
        break;
    case 2:
        printf("PLEASE EMTER NUMBER OF CELLS : \n");
        scanf("%d",&number_of_cells);
        creat_cell_list(number_of_cells,n,map,visual_map,1);
        creat_cell_list(number_of_cells,n,map,visual_map,2);
        creat_map(n,map);
        print_map(visual_map,n);
        while(1)
        {
            int counter=0;
            choosen1=show_and_choose_cell((counter%2)+1);
            int z=show_list2();
            switch (z)
            {
            case 1:
                move_cell (choosen1, map,(counter%2)+1);
                counter++;
                break;
            case 2:
                split_cell(choosen1,map);
                counter++;
                break;
            case 3:
                boost_energy(choosen1,map);
                counter++;
                break;
            case 4:
                break;
            case 5:
                return 0;
                break;
            }
        }
        break;
    case 3:
        printf("PLEASE EMTER NUMBER OF CELLS : \n");
        scanf("%d",&number_of_cells);
        creat_cell_list(number_of_cells,n,map,visual_map,1);
        creat_map(n,map);
        print_map(visual_map,n);
        while(1)
        {
            int z=show_list2();
            choosen1=show_and_choose_cell(1);
            switch (z)
            {
            case 1:
                move_cell (choosen1, map,1);
                break;
            case 2:
                split_cell(choosen1,map);
                break;
            case 3:
                boost_energy(choosen1,map);
                break;
            case 4:
                break;
            case 5:
                return 0;
                break;
            }
        }
        break;
    case 4:
        return 0;
        break;
    }
    //-----------------------------------------------------------------------------------------------------------
    //show_list1();
    //show_list2 ();
    /*printf("PLEASE EMTER NUMBER OF CELLS : \n");
    scanf("%d",&number_of_cells);
    creat_cell_list(number_of_cells,n,map,visual_map,1);
    creat_cell_list(number_of_cells,n,map,visual_map,2);
    creat_map(n,map);
    print_map(visual_map,n);
    choosen1=show_and_choose_cell(1);
    split_cell(choosen1,map);
    show_and_choose_cell(1);
    boost_energy(choosen1,map);
    creat_map(n,map);
    print_map(visual_map,n);
    printf("%s",choosen1->name);
    move_cell (choosen1, map,1);
    creat_map(n,map);
    print_map(visual_map,n);
    choosen2=show_and_choose_cell(2);
    move_cell (choosen2, map,2);
    creat_map(n,map);
    print_map(visual_map,n);*/
    return 0;
}
void creat_map(int n,block a[n+1][n+1])
{
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
            if(a[i][j].empty==1)
            {
                visual_map[x_center][y_center]='X';
            }
            if(a[i][j].empty==2)
            {
                visual_map[x_center][y_center]='O';
            }

        }
    }
}
void print_map(char visual_map[200][200],int n)
{
    for(int i=0; i<5*n+3; i++)
    {
        for(int j=0; j<5*n; j++)
        {
            if(visual_map[i][j]=='X')
            {
                textcolor(240);
                printf("X ");
            }
            if(visual_map[i][j]=='O')
            {
                textcolor(240);
                printf("O ");
            }
            if(visual_map[i][j]=='1')
            {
                textcolor(192);
                printf("  ");
            }
            if(visual_map[i][j]=='2')
            {
                textcolor(240);
                printf("  ");
            }
            if(visual_map[i][j]=='3')
            {
                textcolor(40);
                printf("  ");
            }
            if(visual_map[i][j]=='4')
            {
                textcolor(17);
                printf("  ");
            }
            if(visual_map[i][j]=='0')
            {
                textcolor(15);
                printf("  ");
            }
            //printf(" %c ",visual_map[i][j]);}
        }
        printf("\n");
    }
    textcolor(15);
}
struct cell * create_cell(int x,int y,char *name,int numbe_of_player)
{
    struct cell * nn;
    nn = (struct cell *) malloc(sizeof(struct cell));
    nn->x = x;
    nn->y = y;
    strcpy(nn->name,name);
    nn->number_of_player=numbe_of_player;
    nn->energy=40;
    nn->next = NULL;
    return nn;
}
void add_end(struct cell *list, struct cell * new_node)
{
    struct cell *current;
    for(current = list; current-> next != NULL; current = current->next)
        ;
    current->next = new_node;
    new_node->next = NULL;
}
void creat_cell_list (int number,int n, block a[n+1][n+1],char visual_map[200][200],int number_of_player)
{
    int x,y;
    char s[50];
    printf("PLEAS ENTER NAME OF CELL :\n");
    scanf("%s",s);
    do
    {
        x=rand()%n;
        y=rand()%n;
        printf("1");
    }
    while (a[x][y].empty!=0 || a[x][y].type=='3');
    struct cell *list=create_cell(x,y,s,number_of_player);
    if(number_of_player==1)
    {
        header1=list;
    }
    else
    {
        header2=list;
    }
    a[x][y].empty=number_of_player;
    for(int i=0; i<number-1; i++)
    {
        printf("PLEAS ENTER NAME OF CELL :\n");
        scanf("%s",s);
        do
        {
            x=rand()%n;
            y=rand()%n;
        }
        while(a[x][y].type=='3' || a[x][y].empty!=0);
        add_end(list,create_cell(x,y,s,number_of_player));
        a[x][y].empty=number_of_player;
    }
}
void read_frome_file(block map[n+1][n+1],FILE *fp)
{
    char kind;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            fread(&kind, sizeof(kind), 1, fp);
            map[i][j].type=kind;
            if(kind=='1')
            {
                map[i][j].energy=100;
            }
            else
            {
                map[i][j].energy=0;
            }
            map[i][j].x=i;
            map[i][j].y=j;
            map[i][j].empty=0;
        }
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
int show_list1 ()
{
    printf("[1] Load \n[2 ]New Multiplayer game \n[3 ] New single player game \n[4 ] Exit\n");
    scanf("%d",&list1);
    return list1;
}
int show_list2 ()
{
    printf("[1 ] Move \n[2 ] Split a cell \n[3 ] Boost energy \n[4 ] Save \n[5 ] Exit\n");
    scanf("%d",&list2);
    return list2;
}
struct cell* show_and_choose_cell(int number_of_player)
{
    printf("Please choose one of your cells: \n");
    struct cell *current,*choosen_cell;
    int i=1,choosen,d=1;
    if(number_of_player==1)
    {
        current=header1;
        choosen_cell=header1;
    }
    else
    {
        current=header2;
        choosen_cell=header2;
    }
    for(; current!= NULL; current = current->next)
    {
        printf("%d) %s  [%d,%d]\n",i,current->name,current->x,current->y);
        i++;
    }
    scanf("%d",&choosen);
    while(d<choosen)
    {
        choosen_cell=choosen_cell->next;
        d++;
    }
    return choosen_cell;
}
void move_cell (struct cell *a,block map[n+1][n+1],int number_of_player)
{
    int t,flag=1;
    printf("PLEAS CHOOSE YOUR DIRECTION : \n");
    printf("[1 ] North \n[2 ] South \n[3 ] Northeast \n[4 ] Northwest \n[5 ] Southeast \n[6 ] Southwest\n");
    while(flag)
    {
        scanf("%d",&t);
        switch(t)
        {
        case 1:
            if(map[a->x][a->y+1].type!='3' && map[a->x][a->y+1].empty==0 && a->y+1<n)
            {
                flag=0;
                map[a->x][a->y+1].empty=number_of_player;
                map[a->x][a->y].empty=0;
                a->y+=1;
            }
            break;
        case 2:
            if(map[a->x][a->y-1].type!='3' && map[a->x][a->y-1].empty==0 && a->y-1>=0)
            {
                flag=0;
                map[a->x][a->y-1].empty=number_of_player;
                map[a->x][a->y].empty=0;
                a->y-=1;
            }
            break;
        case 3:
            if(map[a->x+1][a->y+1].type!='3' && map[a->x+1][a->y+1].empty==0 && a->x+1<n && a->y+1<n)
            {
                flag=0;
                map[a->x+1][a->y+1].empty=number_of_player;
                map[a->x][a->y].empty=0;
                a->y+=1;
                a->x+=1;
            }
            break;
        case 4:
            if(map[a->x-1][a->y+1].type!='3' && map[a->x-1][a->y+1].empty==0 && a->x-1>=0 && a->y+1<n)
            {
                flag=0;
                map[a->x-1][a->y+1].empty=number_of_player;
                map[a->x][a->y].empty=0;
                a->y+=1;
                a->x-=1;
            }
            break;
        case 5:
            if(map[a->x+1][a->y-1].type!='3' && map[a->x+1][a->y-1].empty==0 && a->x+1<n && a->y-1>=0)
            {
                flag=0;
                map[a->x+1][a->y-1].empty=number_of_player;
                map[a->x][a->y].empty=0;
                a->y-=1;
                a->x+=1;
            }
            break;
        case 6:
            if(map[a->x-1][a->y-1].type!='3' && map[a->x-1][a->y-1].empty==0 && a->x-1>=0 && a->y-1>=0)
            {
                flag=0;
                map[a->x-1][a->y-1].empty=number_of_player;
                map[a->x][a->y].empty=0;
                a->y-=1;
                a->x-=1;
            }
            break;
        }
    }
}
void boost_energy (struct cell *a,block map[n+1][n+1])
{
    if(map[a->x][a->y].type=='1' && a->energy<=85)
    {
        printf("%d\n",a->energy);
        printf("%d",map[a->x][a->y].energy);
        if(map[a->x][a->y].energy>=15)
        {
            a->energy+=15;
            map[a->x][a->y].energy-=15;
        }
        else
        {
            a->energy+=map[a->x][a->y].energy;
            map[a->x][a->y].energy=0;
            map[a->x][a->y].type='4';
        }
        printf("%d\n",a->energy);
    }
    else
    {
        if(map[a->x][a->y].type!='1')
            printf("YOUR CELL IS NOT IN BOOST BLOCK.\n");
        else
            printf("YOUR CELL HASE MAXIMUM ENERGY.\n");
    }
}
void split_cell (struct cell *a,block map[n+1][n+1])
{
    if(map[a->x][a->y].type=='2' && a->energy >=80 )
    {
        int x2,y2;
        for(int i=0; i<80; i++)
        {
            x2=(rand()%3) -1;
            y2=(rand()%3) -1;
            if(map[a->x+x2][a->y+y2].type!='3' && map[a->x+x2][a->y+y2].empty==0 && a->x+x2<n && a->x+x2>=0 && a->y+y2<n && a->y+y2>=0)
            {
                char s[50];
                printf("PLEAS ENTER NEW NAME FOR FIRST PART OF SPLITED CELL :\n");
                scanf("%s",s);
                a->energy=40;
                strcpy(a->name,s);
                printf("PLEAS ENTER NEW NAME FOR SECOND PART OF SPLITED CELL :\n");
                scanf("%s",s);
                if(a->number_of_player==1)
                {
                    add_end(header1,create_cell(a->x+x2,a->y+y2,s,a->number_of_player));
                }
                else
                {
                    add_end(header2,create_cell(a->x+x2,a->y+y2,s,a->number_of_player));
                }
                break;
            }
        }
    }
    else if(map[a->x][a->y].type!='2')
    {
        printf("YOUR CELL IS NOT IN MITOSIS BLOCK.\n");
    }
    else if(a->energy <80)
    {
        printf("YOUR CELL DOES NOT HAVE ENOUGH ENERGY.\n");
    }
}
