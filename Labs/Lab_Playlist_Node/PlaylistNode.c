/*
 * PlaylistNode.c
 *
 *  Created on: Sep 14, 2021
 *      Author: user
 */
#include <stdio.h>
#include <string.h>
#include "PlaylistNode.h"


void SetPlaylistNode(PlaylistNode* thisNode, char idInit[], char songNameInit[],
		char artistNameInit[], int songLengthInit){
	strcpy(thisNode-> uniqueID, idInit);
	strcpy(thisNode-> songName, songNameInit);
	strcpy(thisNode-> artistName, artistNameInit);
	thisNode -> songLength = songLengthInit;
	thisNode ->nextNodePtr = NULL;


}

void PrintPlaylistNode(PlaylistNode* thisNode){

	printf("Unique ID: %s", thisNode -> uniqueID);
	printf("Song Name: %s", thisNode->songName);
	printf("Artist Name: %s", thisNode -> artistName);
	printf("Song Length (in seconds): %d\n", thisNode -> songLength);
	printf ("\n");
}

PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisNode){
	return thisNode->nextNodePtr;
}


