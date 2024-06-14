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
void select_song();
void search_song();
int DFS(struct node *ptr, char *song, int position);
void delete_song();

void menu()
{
	system("cls");

	printf("\n\n\t\t\t<---------------- Welcome to Groovecho music player ---------------->\n");
	printf("\n\tOptions-\n\n");
	printf("\t1. Add songs to playlist\n");
	printf("\t2. Display songs from playlist\n");
	printf("\t3. Play songs in queue\n");
	printf("\t4. Select song from playlist\n");
	printf("\t5. Search song from playlist\n");
	printf("\t6. Delete song from playlist\n");
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
		printf("\n\n\tPlaylist is empty. Press any key to continue ... ");
		getch();
		menu();
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

void change_song(struct node *song)
{
	if (song == NULL)
	{
		printf("\n\tSong not found!\n");
		return;
	}
	while (1)
	{
		system("cls");

		printf("\n\n\tPlaying song: %s\n", song->song_name);
		PlaySound(song->song_path, NULL, SND_SYNC);

		printf("\n\n\tOptions:\n");
		printf("\t1. Play Previous Song\n");
		printf("\t2. Play Next Song\n");
		printf("\t3. Stop\n");

		int choice;
		printf("\n\tEnter your choice: ");
		scanf("%d", &choice);

		if (choice == 1)
		{
			struct node *prev = head;
			if (song != head)
			{
				while (prev->next != song)
				{
					prev = prev->next;
				}
				song = prev;
			}
			else
			{
				while (prev->next != NULL)
				{
					prev = prev->next;
				}
				song = prev;
			}
		}
		else if (choice == 2)
		{
			if (song->next != NULL)
			{
				song = song->next;
			}
			else
			{
				song = head;
			}
		}
		else if (choice == 3)
		{
			break;
		}
		else
		{
			printf("\n\tInvalid choice!\n");
		}
	}
	printf("\n\n\tPress any key to continue ... ");
	getch();
	menu();
}

void select_song()
{
	system("cls");

	if (counter == 0)
	{
		printf("\n\n\tPlaylist is empty\n");
		return;
	}
	printf("\n\n\tHere is your playlist: \n\n");

	struct node *ptr = head;

	int i = 1;
	while (ptr != NULL)
	{
		printf("\t%d. %s\n", i, ptr->song_name);
		i++;
		ptr = ptr->next;
	}

	printf("\n\n\tSelect song: ");
	int pos;
	scanf("%d", &pos);

	if (pos <= 0 || pos > counter)
	{
		printf("\n\tEnter valid position\n");
		return;
	}
	ptr = head;
	for (int j = 1; j < pos; j++)
	{
		ptr = ptr->next;
	}
	change_song(ptr);

	printf("\n\n\tPress any key to continue ... ");
	getch();
	menu();
}

void search_song()
{
	system("cls");

	printf("\n\n\tEnter song name to be searched: ");
	char song[40];
	scanf("%s", song);

	int position = DFS(head, song, 0);

	if (position != -1)
	{
		struct node *ptr = head;
		for (int i = 0; i < position; i++)
		{
			ptr = ptr->next;
		}
		printf("\n\n\tThe song is at position %d in the queue. Playing %s song...\n", position + 1, ptr->song_name);
		PlaySound(ptr->song_path, NULL, SND_SYNC);
	}
	else
	{
		printf("\n\n\tSong not found in your playlist.\n");
	}

	printf("\n\tPress any key to continue ... ");
	getch();
	menu();
}

int DFS(struct node *ptr, char *song, int position)
{
	if (ptr == NULL)
	{
		return -1;
	}
	if (strcmp(ptr->song_name, song) == 0)
	{
		return position;
	}
	return DFS(ptr->next, song, position + 1);
}

void delete_song()
{
	system("cls");

	char song_delete[40];
	printf("\n\n\tEnter the name of the song to delete:");
	scanf("%s", song_delete);

	struct node *ptr = head;
	struct node *ptr1 = NULL;
	int found = 0, position = 0;

	for (ptr = head; ptr != NULL; ptr = ptr->next)
	{
		if (strcmp(ptr->song_name, song_delete) == 0)
		{
			found = 1;
			break;
		}
		ptr1 = ptr;
		position++;
	}
	if (found == 1)
	{
		if (ptr1 == NULL)
			head = ptr->next;
		else
			ptr1->next = ptr->next;
		free(ptr);
		printf("\n\n\t \"%s\" song is successfully deleted from your playlist. Press any key to continue ... ", song_delete);
		counter--;
	}
	else
	{
		printf("\n\n\t \"%s\" song not found in your playlist. Press any key to continue ... ", song_delete);
	}

	getch();
	menu();
}

int main()
{
	system("color F8");

	int choice, pos;

	printf("\n\n\t\t\t<---------------- Welcome to Groovecho music player ---------------->\n");
	// PlaySound(".\\Audio\\welcome.WAV", NULL, SND_SYNC);

	printf("\n\tOptions-\n\n");
	printf("\t1. Add songs to playlist\n");
	printf("\t2. Display songs from playlist\n");
	printf("\t3. Play songs in queue\n");
	printf("\t4. Select song from playlist\n");
	printf("\t5. Search song from playlist\n");
	printf("\t6. Delete song from playlist\n");
	// PlaySound(".\\Audio\\info.WAV", NULL, SND_SYNC);

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

		case 5:
			search_song();
			break;

		case 6:
			delete_song();
			break;

		default:
			printf("\n\tInvalid choice !\n\n");
		}
	}

	return 0;
}