#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
int main ()
{
    int p, n, nop, i=1, j=1;
    struct cell *current=NULL, temp;
    struct block map;
    char address[20];
    printf ("enter the map name\n");
    scanf("%s", address);
    FILE* bin_map=fopen(address, "rb");
    printf ("enter the player file name\n");
    scanf("%s", address);
    FILE *bin_players=fopen(address, "rb");
    printf ("enter the output map name\n");
    scanf("%s", address);
    FILE *txt_map=fopen(address, "w");
    printf ("enter the output player file name\n");
    scanf("%s", address);
    FILE *txt_players=fopen(address, "w");
    fread(&n, sizeof(int), 1, bin_map);
    fprintf(txt_map, "map size=%d\n", n);
    for (i=0; i<n+10; i++)
        for (j=0; j<n+10; j++)
    {
        fread(&map, sizeof(struct block), 1, bin_map);
        fprintf(txt_map, "map [%d][%d]={type='%c', energy=%d, empty=%d}\n", i, j, map.type, map.energy, map.empty);

    }
            fclose(bin_map);
            fclose(txt_map);
    fread(&p, sizeof(int), 1, bin_players);
    fread(&nop, sizeof(int), 1, bin_players);
    fprintf(txt_players, "number of players=%d\n", nop);
    for (int i=0; i<nop; i++)
    {
        for (j=0; j<p; j++)
        {
            fread(&temp, sizeof(struct cell), 1, bin_players);
            fprintf(txt_players, "cell [%d][%d]={x=%d y=%d energy=%d name=%s number of player=%d}\n", i+1, j, temp.x, temp.y, temp.energy, temp.name,temp.number_of_player);
        }
    }
    fclose(bin_players);
    fclose(txt_players);
}
