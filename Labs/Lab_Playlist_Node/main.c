#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PlaylistNode.h"




void PrintMenu(char playlistTitle[]) {
   printf("%s PLAYLIST MENU\n", playlistTitle);
   printf("a - Add song\n");
   printf("r - Remove song\n");
   printf("o - Output full playlist\n");
   printf("q - Quit\n\n");
}

PlaylistNode* ExecuteMenu(char option, char playlistTitle[], PlaylistNode* headNode) {
	char uniqueID[50];
	char songName[50];
	char artistName[50];
	int songLength;
	PlaylistNode* head = headNode;


   switch (option) {
      case 'a':

         /* Add a song */
    	  printf("ADD SONG\n" );
    	  printf("Enter song's unique ID:\n");
    	  fgets(uniqueID,50,stdin);
    	  fgets(uniqueID,50,stdin);
    	  printf("Enter song's name:\n");
    	  fgets(songName,50,stdin);
    	  printf("Enter artist's name:\n");
    	  fgets(artistName,50,stdin);
    	  printf("Enter song's length (in seconds):\n\n");
    	  scanf("%d", &songLength);
    	  PlaylistNode* newNode =(PlaylistNode*)malloc(sizeof(PlaylistNode));
    	  SetPlaylistNode(newNode, uniqueID, songName, artistName, songLength);


    	  if (head == NULL){

    		  headNode =newNode;


    	  }
    	  else {

    		  while (head->nextNodePtr != NULL){
    			  head=head->nextNodePtr;


    		  }
    		  //head next
    		  head->nextNodePtr=newNode;



    	  }
         break;

      case 'r':
         /* Remove a song */
         break;

      case 'o':
         /* Print all songs in the list */
    	  printf("%s - OUTPUT FULL PLAYLIST\n", playlistTitle);

    	  if (head==NULL){
    		  printf("Playlist is empty\n\n");
    	  }
    	  else {
    		  int counter =	1;
    		  while (head != NULL){
    			  printf("%d.\n",counter);
    			  PrintPlaylistNode(head);
    			  counter++;
    			  head=head->nextNodePtr;
    		  }
    	  }
         break;
   }
   return headNode;


}

int main(void) {
	char playlistTitle [50];
	char menuOp;
	PlaylistNode* head = NULL;

   // Prompt user for playlist title

   printf("Enter playlist's title:\n");
   fgets(playlistTitle, 50, stdin);
   printf("\n");

   // Eliminate end-of-line char
   playlistTitle[strlen(playlistTitle) - 1] = '\0';



   // Output play list menu options
   PrintMenu(playlistTitle);


   while(menuOp != 'q') {
      printf("Choose an option:\n");
      scanf(" %c", &menuOp);
      if (menuOp == 'a' || menuOp == 'r' || menuOp == 'o') {
         head = ExecuteMenu(menuOp, playlistTitle, head);
         PrintMenu(playlistTitle);
      }
   }


   return 0;
}
