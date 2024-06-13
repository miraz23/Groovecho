#include <stdio.h>
#include <windows.h>
#include <MMsystem.h>
#include <stdlib.h>
#include <string.h>


struct node
{
	char song_name[30];
	char song_path[40];
	struct node *next;

} *head = NULL;


int counter = 0;
void add_song();


void add_song()
{   
    system("cls");
    
    struct node *start;
	start = (struct node *)malloc(sizeof(struct node));
	start->next = NULL;

	printf("\n\n\tEnter the name of song: ");
	scanf("%s", start->song_name);
	printf("\tEnter the path of the song: ");
	scanf("%s", start->song_path);

	if (head == NULL)
	{
		head = start;
	}
	else
	{
		struct node *ptr = head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = start;
	}
	counter++;
}






int main()
{
    system("color F8");
	int choice, pos;

	printf("\n\n\t\t\t<---------------- Welcome to Groovecho music player ---------------->\n");
	PlaySound(".\\Audio\\welcome.WAV", NULL, SND_SYNC);

	printf("\n\tOptions-\n\n");
	printf("\t1. Add song to playlist\n");
	PlaySound(".\\Audio\\info.WAV", NULL, SND_SYNC);

	while (1)
	{
		printf("\n\n\tEnter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			add_song();
			break;

		default:
			printf("\tInvalid choice !\n\n");
		}
	}

	return 0;
}