#include <stdio.h>
#include <stdlib.h>

int print_grid(char grid[][10],int Start[], int End[])
{
	for(int i = 0; i<10; i++)
	{
		for(int j = 0; j<10; j++)
		{
			if((i==Start[1] && j==Start[0]) || (i==End[1] && j==End[0]))
			{
				printf("\033[0;33m%c",grid[i][j]);
				printf("\033[0m"); 
			}
			else
			{
				printf("%c",grid[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}

int len(char word[])
{
    int l = 0;
    while(word[l]!=0)
    {
        l++;
    }
    return l;
}

int find_word(char grid[][10], char word[], int End[2], int i, int j, int vx, int vy)
{
	printf("i,j = %i,%i   vx,vy = %i,%i\n",i,j,vx,vy);
	i+=vx;
	j+=vy;
	for(size_t k = 2; k<len(word); k++)
	{
		if((i>=0 && i<10) && (j>=0 && j<10) && grid[i][j]==word[k])
		{
			i += vx;
			j += vy;
		}
		else
		{
			return 1;
		}
	}
	printf("DB %i,%i\n",vy,vx);
	End[0] = j-vy;
	End[1] = i-vx;
	return 0;
}

int find_second_letter(char grid[][10], char word[], int End[2], int x, int y)
{
	for(int i = x-1; i<=x+1; i++)
	{
		for(int j = y-1; j<=y+1; j++)
		{
			if((i>=0 && i<10) && (j>=0 && j<10))
			{
				printf("l(%i,%i):%c\n",i,j,grid[i][j]);
				if(grid[i][j]==word[1])
				{
					if(find_word(grid,word,End,i,j,i-x,j-y)==0)
					{
						return 0;
					}
				}
			}
		}
	}

	return 1;
}


int solve_grid(char grid[][10], char word[], int Start[2],int End[2])
{
	for(size_t x = 0; x<10; x++)
	{
		for(size_t y = 0; y<10; y++)
		{
			if(grid[x][y]==word[0])
			{
				Start[0] = y;
				Start[1] = x;
				if(find_second_letter(grid,word,End,x,y)==0)
					return 0;
			}
		}
	}
	return 1;
}


int read_grid(char filename[],char grid[][10])
{
	FILE *fichier = fopen(filename,"r");

	if(fichier == NULL)
	{
		printf("ERROR: open file\n");
		return 1;
	}

	char ligne[256];
	size_t x = 0;

	while(fgets(ligne, sizeof(ligne), fichier) != NULL)
	{
		size_t y = 0;
		while(ligne[y]!=0)
		{
			grid[x][y] = ligne[y];
			y++;
		}
		x++;
	}

	return 0;
}

int solver(char word[])
{
	char filename[] = "data.txt";
	char grid[10][10];
	int word_len = len(word);
	int grid_len = 10;
	
	read_grid(filename,grid);

	int Start[2] = {};
	int End[2] = {};

	int e = solve_grid(grid,word,Start,End);
	if(e==1)
	{
		printf("ERROR: le mot n'existe pas\n");
	}
	else
	{
		printf("Start = (%i,%i)\n",Start[0],Start[1]);
		printf("End = (%i,%i)\n",End[0],End[1]);
		printf("(%i,%i)(%i,%i)\n",Start[0],Start[1],End[0],End[1]);
	}

	print_grid(grid,Start,End);
	return 0;
}

int main(int argc, char *argv[])
{
	printf("%s\n",argv[1]);
	return solver(argv[1]);
}
