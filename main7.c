#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

struct  block
{
    int x;
    int y;
    char type;
    int energy;
    int empty ;
};
struct  cell
{
    int x;
    int y;
    int energy;
    char name[50];
    int number_of_player;
    struct cell *next;
};
int number_of_cells,n,list1,list2,tedad_player=1;
void read_frome_file(struct block map[40][40],FILE *fp);
char visual_map[200][200];
void creat_map(int n,struct block a[40][40]);
void textcolor (int color);
void print_map(char visual_map[200][200],int n);
struct cell * create_cell(int x,int y,char *name,int number_of_player,int energy);
void add_end(struct cell *list, struct cell * new_node);
void creat_cell_list (int number,int n,struct block a[40][40],char visual_map[200][200],int number_of_player);
int show_list1 ();
int show_list2 ();
struct cell* show_and_choose_cell(int number_of_player);
void move_cell (struct cell *a,struct block map[40][40],int number_of_player);
void boost_energy (struct cell *a,struct block map[40][40]);
void split_cell (struct cell *a,struct block map[40][40]);
int save_game(FILE *save1, FILE *save2, struct cell *header1,struct cell *header2,int number_of_cells,struct block map[40][40]);
int count_energy (struct cell *header);
void load_map();
void map_editor ();
void begining ();
void end_game (FILE *save1, FILE *save2, struct cell *header1,struct cell *header2,int number_of_cells,struct block map[40][40]);
struct cell *header1,*header2,*choosen1,*choosen2;
FILE *save1,*save2;
struct block map[40][40];
int main()
{
    begining();
    int w;
    header1=NULL;
    header2=NULL;
    srand(time(0));
    FILE *fp;
    printf("1) PLAY AVALIABLE MAP .\n2) CREAT NEW MAP .\n");
    scanf("%d",&w);
    switch(w)
    {
    case 1:
        printf("PLEAS ENTER NAME OF YOUR MAP :\n");
        char inname[60];
        scanf("%s",inname);
        fp = fopen(inname, "rb");
        fread(&n, sizeof(int), 1, fp);
        read_frome_file(map,fp);
        break;
    case 2:
        map_editor();
        printf("PLEAS ENTER NAME OF YOUR MAP :\n");
        scanf("%s",inname);
        fp = fopen(inname, "rb");
        fread(&n, sizeof(int), 1, fp);
        read_frome_file(map,fp);
        break;
    }
    switch(show_list1())
    {
    case 1:
        load_map();
        creat_map(n,map);
        print_map(visual_map,n);
        if(tedad_player==1)
        {
            while(1)
            {
                int z=show_list2();
                switch (z)
                {
                case 1:
                    choosen1=show_and_choose_cell(1);
                    move_cell (choosen1, map,1);
                    creat_map(n,map);
                    print_map(visual_map,n);
                    break;
                case 2:
                    choosen1=show_and_choose_cell(1);
                    split_cell(choosen1,map);
                    creat_map(n,map);
                    print_map(visual_map,n);
                    break;
                case 3:
                    choosen1=show_and_choose_cell(1);
                    boost_energy(choosen1,map);
                    creat_map(n,map);
                    print_map(visual_map,n);
                    break;
                case 4:
                    save_game(save1,save2,header1,header2,number_of_cells,map);
                    break;
                case 5:
                    end_game(save1,save2,header1,header2,number_of_cells,map);
                    return 0;
                    break;
                }
            }
        }
        else
        {
            int counter=0;
            while(1)
            {
                int z=show_list2();
                switch (z)
                {
                case 1:
                    choosen1=show_and_choose_cell((counter%2)+1);
                    move_cell (choosen1, map,(counter%2)+1);
                    creat_map(n,map);
                    print_map(visual_map,n);
                    counter++;
                    break;
                case 2:
                    choosen1=show_and_choose_cell((counter%2)+1);
                    split_cell(choosen1,map);
                    creat_map(n,map);
                    print_map(visual_map,n);
                    counter++;
                    break;
                case 3:
                    choosen1=show_and_choose_cell((counter%2)+1);
                    boost_energy(choosen1,map);
                    creat_map(n,map);
                    print_map(visual_map,n);
                    counter++;
                    break;
                case 4:
                    save_game(save1,save2,header1,header2,number_of_cells,map);
                    break;
                case 5:
                    end_game(save1,save2,header1,header2,number_of_cells,map);
                    return 0;
                    break;
                }
            }
        }
        break;
    case 2:
        tedad_player=2;
        printf("PLEASE ENTER NUMBER OF CELLS : \n");
        scanf("%d",&number_of_cells);
        creat_cell_list(number_of_cells,n,map,visual_map,1);
        creat_cell_list(number_of_cells,n,map,visual_map,2);
        creat_map(n,map);
        print_map(visual_map,n);
        int counter=0;
        while(1)
        {
            int z=show_list2();
            switch (z)
            {
            case 1:
                choosen1=show_and_choose_cell((counter%2)+1);
                move_cell (choosen1, map,(counter%2)+1);
                creat_map(n,map);
                print_map(visual_map,n);
                counter++;
                break;
            case 2:
                choosen1=show_and_choose_cell((counter%2)+1);
                split_cell(choosen1,map);
                creat_map(n,map);
                print_map(visual_map,n);
                counter++;
                break;
            case 3:
                choosen1=show_and_choose_cell((counter%2)+1);
                boost_energy(choosen1,map);
                creat_map(n,map);
                print_map(visual_map,n);
                counter++;
                break;
            case 4:
                save_game(save1,save2,header1,header2,number_of_cells,map);
                break;
            case 5:
                end_game(save1,save2,header1,header2,number_of_cells,map);
                return 0;
                break;
            }
        }
        break;
    case 3:
        tedad_player=1;
        printf("PLEASE EMTER NUMBER OF CELLS : \n");
        scanf("%d",&number_of_cells);
        creat_cell_list(number_of_cells,n,map,visual_map,1);
        creat_map(n,map);
        print_map(visual_map,n);
        while(1)
        {
            int z=show_list2();
            switch (z)
            {
            case 1:
                choosen1=show_and_choose_cell(1);
                move_cell (choosen1, map,1);
                creat_map(n,map);
                print_map(visual_map,n);
                break;
            case 2:
                choosen1=show_and_choose_cell(1);
                split_cell(choosen1,map);
                creat_map(n,map);
                print_map(visual_map,n);
                break;
            case 3:
                choosen1=show_and_choose_cell(1);
                boost_energy(choosen1,map);
                creat_map(n,map);
                print_map(visual_map,n);
                break;
            case 4:
                save_game(save1,save2,header1,header2,number_of_cells,map);
                break;
            case 5:
                end_game(save1,save2,header1,header2,number_of_cells,map);
                return 0;
                break;
            }
        }
        break;
    case 4:
        end_game(save1,save2,header1,header2,number_of_cells,map);
        break;
    }
    return 0;
}
void creat_map(int n,struct block a[40][40])
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
            else if(visual_map[i][j]=='O')
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
        }
        printf("\n");
    }
    textcolor(15);
}
struct cell * create_cell(int x,int y,char *name,int numbe_of_player,int energy)
{
    struct cell * nn;
    nn = (struct cell *) malloc(sizeof(struct cell));
    nn->x = x;
    nn->y = y;
    strcpy(nn->name,name);
    nn->number_of_player=numbe_of_player;
    nn->energy=energy;
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
void creat_cell_list (int number,int n,struct block a[40][40],char visual_map[200][200],int number_of_player)
{
    int x,y;
    char s[50];
    printf("PLEAS ENTER NAME OF CELL :\n");
    scanf("%s",s);
    do
    {
        x=rand()%n;
        y=rand()%n;
    }
    while (a[x][y].empty!=0 || a[x][y].type=='3');
    struct cell *list=create_cell(x,y,s,number_of_player,40);
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
        add_end(list,create_cell(x,y,s,number_of_player,40));
        a[x][y].empty=number_of_player;
    }
}
void read_frome_file(struct block map[40][40],FILE *fp)
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
    textcolor(12);
    printf("\n\n\n");
    printf("[1 ] Load \n[2 ] New Multiplayer game \n[3 ] New single player game \n[4 ] Exit\n");
    textcolor(15);
    scanf("%d",&list1);
    printf("\n\n\n");
    return list1;
}
int show_list2 ()
{
    textcolor(12);
    printf("\n\n\n");
    printf("[1 ] Move \n[2 ] Split a cell \n[3 ] Boost energy \n[4 ] Save \n[5 ] Exit\n");
    textcolor(15);
    scanf("%d",&list2);
    printf("\n\n\n");
    return list2;
}
struct cell* show_and_choose_cell(int number_of_player)
{
    printf("\n\n\n");
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
        printf("%d) %s  [%d,%d]      ENERGY = %d \n",i,current->name,current->x,current->y,current->energy);
        i++;
    }
    scanf("%d",&choosen);
    printf("\n\n\n");
    while(d<choosen)
    {
        choosen_cell=choosen_cell->next;
        d++;
    }
    return choosen_cell;
}
void move_cell (struct cell *a,struct block map[40][40],int number_of_player)
{
    int t,flag=1;
    while(flag)
    {
        if(flag==1)
        {
            printf("PLEAS CHOOSE YOUR DIRECTION : \n");
            printf("[1 ] North \n[2 ] South \n[3 ] Northeast \n[4 ] Northwest \n[5 ] Southeast \n[6 ] Southwest\n");
        }
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
            if(a->x%2==0)
            {
                if(map[a->x+1][a->y+1].type!='3' && map[a->x+1][a->y+1].empty==0 && a->x+1<n && a->y+1<n )
                {
                    flag=0;
                    map[a->x+1][a->y+1].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->x+=1;
                    a->y+=1;
                }
            }
            else
            {
                if(map[a->x+1][a->y].type!='3' && map[a->x+1][a->y].empty==0 && a->x+1<n )
                {
                    flag=0;
                    map[a->x+1][a->y].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->x+=1;
                }
            }
            break;
        case 4:
            if(a->x%2==0)
            {
                if(map[a->x-1][a->y+1].type!='3' && map[a->x-1][a->y+1].empty==0 && a->x-1>=0 && a->y+1<n)
                {
                    flag=0;
                    map[a->x-1][a->y+1].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->y+=1;
                    a->x-=1;
                }
            }
            else
            {
                if(map[a->x-1][a->y].type!='3' && map[a->x-1][a->y].empty==0 && a->x-1>=0)
                {
                    flag=0;
                    map[a->x-1][a->y].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->x+=1;
                }
            }
            break;
        case 5:
            if(a->x%2==0)
            {
                if(map[a->x+1][a->y].type!='3' && map[a->x+1][a->y].empty==0 && a->x+1<n)
                {
                    flag=0;
                    map[a->x+1][a->y].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->x+=1;
                }
            }
            else
            {
                if(map[a->x+1][a->y-1].type!='3' && map[a->x+1][a->y-1].empty==0 && a->x+1<n && a->y-1>=0)
                {
                    flag=0;
                    map[a->x+1][a->y-1].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->x+=1;
                    a->y-=1;
                }
            }
            break;
        case 6:
            if(a->x%2==0)
            {
                if(map[a->x-1][a->y].type!='3' && map[a->x-1][a->y].empty==0 && a->x-1>=0)
                {
                    flag=0;
                    map[a->x-1][a->y].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->x-=1;
                }
            }
            else
            {
                if(map[a->x-1][a->y-1].type!='3' && map[a->x-1][a->y-1].empty==0 && a->x-1>=0 && a->y-1>=0)
                {
                    flag=0;
                    map[a->x-1][a->y-1].empty=number_of_player;
                    map[a->x][a->y].empty=0;
                    a->x-=1;
                    a->y-=1;
                }
            }
            break;
        }
    }
}
void boost_energy (struct cell *a,struct block map[40][40])
{
    if(map[a->x][a->y].type=='1' && a->energy<=85)
    {
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
    }
    else
    {
        if(map[a->x][a->y].type!='1')
            printf("YOUR CELL IS NOT IN BOOST BLOCK.\n");
        else
            printf("YOUR CELL HASE MAXIMUM ENERGY.\n");
    }
}
void split_cell (struct cell *a,struct block map[40][40])
{
    if(map[a->x][a->y].type=='2' && a->energy >=80 )
    {
        int x2,y2;
        for(int i=0; i<100; i++)
        {
            if(a->x%2==0)
            {
                x2=(rand()%3) -1;
                if(x2==0)
                {
                    y2=rand()%3  -1;
                }
                else
                {
                    y2=rand()%2;
                }
            }
            else
            {
                x2=(rand()%3) -1;
                if(x2==0)
                {
                    y2=rand()%3  -1;
                }
                else
                {
                    y2=(rand()%2) -1;
                }
            }
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
                    add_end(header1,create_cell(a->x+x2,a->y+y2,s,a->number_of_player,40));
                }
                else
                {
                    add_end(header2,create_cell(a->x+x2,a->y+y2,s,a->number_of_player,40));
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
int save_game(FILE *save1, FILE *save2, struct cell *header1,struct cell *header2,int number_of_cells,struct block map[40][40])
{
    struct cell *current=header1;
    struct cell *current2=header2;
    save1 = fopen("game.bin", "wb");
    save2 = fopen("gamemap.bin", "wb");
    fwrite(&n,sizeof(int),1,save2);
    fwrite(map,sizeof(struct block),(n+10)*(n+10),save2);
    fclose(save2);
    fwrite(&number_of_cells,sizeof(int),1,save1);
    fwrite(&tedad_player,sizeof(int),1,save1);
    for(int j=0; j<number_of_cells; j++)
    {
        fwrite(current,sizeof(struct cell),1,save1);
        current=current->next;
    }
    if(header2!=NULL)
    {
        for(int k=0; k<number_of_cells; k++)
        {
            fwrite(current2,sizeof(struct cell),1,save1);
            current2=current2->next;
        }
    }
    fclose(save1);
    printf("saved\n");
    return 0;
}
int count_energy (struct cell *header)
{
    int sum=0;
    struct cell *current =header;
    for(current; current!=NULL; current=current->next)
    {
        sum+=current->energy;
    }
    return sum;
}
void load_map()
{
    save1=fopen("game.bin","rb");
    save2=fopen("gamemap.bin","rb");
    fread(&n,sizeof(int),1,save2);
    fread(&map,sizeof(struct block),(n+10)*(n+10),save2);
    fread(&number_of_cells,sizeof(int),1,save1);
    fread(&tedad_player,sizeof(int),1,save1);
    struct cell *temp;
    for(int i=0; i<number_of_cells; i++)
    {
        if(i==0)
        {
            fread(temp,sizeof(struct cell),1,save1);
            header1=create_cell(temp->x,temp->y,temp->name,1,temp->energy);
        }
        else
        {
            fread(temp,sizeof(struct cell),1,save1);
            add_end(header1,create_cell(temp->x,temp->y,temp->name,1,temp->energy));
        }
    }
    if(tedad_player==2)
    {
        for(int k=0; k<number_of_cells; k++)
        {
            if(k==0)
            {
                fread(temp,sizeof(struct cell),1,save1);
                header2=create_cell(temp->x,temp->y,temp->name,2,temp->energy);
            }
            else
            {
                fread(temp,sizeof(struct cell),1,save1);
                add_end(header2,create_cell(temp->x,temp->y,temp->name,2,temp->energy));
            }
        }
    }
    fclose(save2);
    fclose(save1);
}
void map_editor ()
{
    FILE *fp;
    char map_name[60],temp;
    int map_size;
    printf("PLEAS ENTER NAME OF YOUR MAP :\n");
    scanf("%s",map_name);
    fp=fopen(map_name,"wb");
    printf("PLEAS ENTER SIZE OF YOUR MAP :\n");
    scanf("%d",&map_size);
    fwrite(&map_size, sizeof(int), 1, fp);
    for(int i=0; i< map_size*map_size; i++)
    {
        getchar();
        scanf("%c",&temp);
        fwrite(&temp,sizeof(char),1,fp);
    }
    fclose(fp);
}
void begining ()
{
    char o,str[]= {"HELLOW!. WELCOME TO LONEL CELL GAME!!! :) :)"};
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
    printf("\n\n\n");
}
void end_game (FILE *save1, FILE *save2, struct cell *header1,struct cell *header2,int number_of_cells,struct block map[40][40])
{
    printf("TOTAL ENERGY OF YOUR FIRST PLAYER IS :\n \n\t\t %d\n\n",count_energy(header1));
    if(header2!=NULL)
    {
        printf("TOTAL ENERGY OF YOUR FIRST PLAYER IS :\n \n\t\t %d\n\n",count_energy(header2));
    }
    int e;
    printf("\n\n\n");
    printf("ARE YOU SURE YOU WANT TO EXIT WITHOUT SAVE ? \n\n");
    printf("1) YES !\n\n2) NO SAVE THE GAME FIRST.!\n\n");
    scanf("%d",&e);
    printf("\n\n\n");
    switch(e)
    {
    case 1:
        textcolor(14);
        printf("\n\n\n");
        printf("GOOD BYE !!!\n\n\n");
        break;
    case 2:
        textcolor(14);
        save_game(save1,save2,header1,header2,number_of_cells,map);
        printf("\n\n\nGOOD BYE !!!\n\n\n");
        break;
    }
}
