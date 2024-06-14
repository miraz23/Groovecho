#include <stdio.h>
#include <conio.h>
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
void menu();
void add_songs();
void display_songs();
void play_songs();

void menu()
{
	system("cls");

	printf("\n\n\t\t\t<---------------- Welcome to Groovecho music player ---------------->\n");
	printf("\n\tOptions-\n\n");
	printf("\t1. Add songs to playlist\n");
	printf("\t2. Display songs from playlist\n");
	printf("\t3. Play songs in queue\n");
	printf("\t4. Select song from playlist\n");
}

void add_songs()
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

	display_songs();
}

void display_songs()
{
	system("cls");

	struct node *ptr = head;

	if (counter == 0)
	{
		printf("\n\n\tPlaylist is empty\n");
		return;
	}

	printf("\n\n\tHere is your playlist: \n\n");

	int i = 1;
	while (ptr != NULL)
	{
		printf("\t%d. ", i);
		i = i + 1;
		printf("%s\n", ptr->song_name);
		ptr = ptr->next;
	}
	printf("\n");

	printf("\n\tPress any key to continue ... ");
	getch();
	menu();
}

void play_songs()
{
	system("cls");

	if (head == NULL)
	{
		printf("\n\n\tPlaylist is empty!\n\n");
		return;
	}

	struct node *ptr = head;
	
	printf("\n\n\tPlaying all songs-\n\n");
	while (ptr != NULL)
	{
		printf("\tPlaying song: %s\n", ptr->song_name);
		PlaySound(ptr->song_path, NULL, SND_SYNC);
		ptr = ptr->next;
	}

	printf("\n\n\tReached end of playlist. Press any key to continue ... ");
	getch();
	menu();
}

void select_song(int pos)
{
	system("cls");

	struct node *ptr = head;

	if (counter == 0)
	{
		printf("\n\n\tPlaylist is empty\n");
		return;
	}

	printf("\n\n\tHere is your playlist: \n\n");

	int i = 1;
	while (ptr != NULL)
	{
		printf("\t%d. ", i);
		i = i + 1;
		printf("%s\n", ptr->song_name);
		ptr = ptr->next;
	}
	printf("\n");



	printf("\n\n\tSelect song: ");
	scanf("%d", &pos);

	int j = 0;
	if (pos <= 0 || pos > counter)
	{
		printf("\n\tEnter valid position\n");
		return;
	}

	struct node *newptr = head;
	while (j < pos - 1)
	{
		newptr = newptr->next;
		j++;
	}


	printf("\n\n");
	while (newptr != NULL)
	{
		printf("\tPlaying song: %s\n", newptr->song_name);
		PlaySound(newptr->song_path, NULL, SND_SYNC);
		newptr = newptr->next;
	}

	printf("\n\n\tReached end of playlist. Press any key to continue ... ");
	getch();
	menu();
}

int main()
{
	system("color F8");

	int choice, pos;

	printf("\n\n\t\t\t<---------------- Welcome to Groovecho music player ---------------->\n");
	PlaySound(".\\Audio\\welcome.WAV", NULL, SND_SYNC);

	printf("\n\tOptions-\n\n");
	printf("\t1. Add songs to playlist\n");
	printf("\t2. Display songs from playlist\n");
	printf("\t3. Play songs in queue\n");
	printf("\t4. Select song from playlist\n");
	PlaySound(".\\Audio\\info.WAV", NULL, SND_SYNC);

	while (1)
	{
		printf("\n\n\tEnter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			add_songs();
			break;

		case 2:
			display_songs();
			break;

		case 3:
			play_songs();
			break;

		case 4:
			if (counter != 0)
			{
				select_song(pos);
			}
			break;

		default:
			printf("\tInvalid choice !\n\n");
		}
	}

	return 0;
}