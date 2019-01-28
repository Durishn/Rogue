/*************************************roguefunctions.c**************************************
Student Name: Nic Durish                        Student Number:  0757227
Date: Mar 4, 2013                         Course Name: Intermediate Programming
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
*******************************************************************************************/
#include "rogue.h"

void gameIntro() {
	
	/* Print the Game introduction, controls, and legend then get an input from the user*/
	
	printf(".............................\n");
	printf(".__....___...___.........___.\n");
	printf("|  \\ .| _ |.| __|.||.||.| __|\n");
	printf("| | |.||.||.||__..||.||.||__.\n");
	printf("|  /..||.||.||_ |.||.||.| __|\n");
	printf("||\\\\..||_||.||_||.||_||.||__.\n");
	printf("||.||.|___|.|___|.|___|.|___|\n");
	printf(".............................\n");
	printf("....-LIKE COMPUTER GAME......\n");
	printf("*****************************\n");
	printf(".see readme for instructions.\n");
	printf("*****************************\n");
	printf("...........CONTROLS..........\n");
	printf("...[h] left......[j] down....\n");
	printf("...[l] right.....[k] up......\n");
	printf("...[q] quit...[n] next-room..\n");
	printf("*****************************\n");
	printf("............LEGEND...........\n");
	printf("..[@] hero.......[M] monster.\n");
	printf("..[*] treasure...[+] door....\n");
	printf("..[)] weapon.....[|] wall....\n");
	printf("..[!] potion.....[.] floor...\n");
	printf("*****************************\n");
	printf(".....Hit [Enter] To Start....\n");
	getchar();
}

void initCurses() {
	
	/* Initialize the ncurses settings*/
	
	initscr ();
	cbreak ();
	noecho ();
	keypad (stdscr, TRUE);
}

char ** readFile (FILE *inputFile) {
	
	/*Initialize an integer; 'i' is a counter
	* Initialize a 2-d String; 'roomsList' is all the room information
	* Initialize a string; lineBuffer is a buffer for reading each line in the file*/
	
	int i;
	char ** roomsList;	
	char lineBuffer[200];
	
	/*Malloc 9 char * slots for roomsList, exit if no memory is allocated*/

	roomsList = malloc(sizeof(char*) * 9);
	if(roomsList==NULL) {  printf("Out of memory\n"); refresh(); exit(0);}
	
	/*If inputFile is NULL print an error message and exit program*/
	
	if (inputFile == NULL) {
		printf ( "Error: Could not find input file\n");
		exit(1);
	}	

	/*If inputFile isn't NULL start a for loop using 'i' starting at 0 to 9
	* Set lineBuffer as the i'th line in the file. Malloc memory for roomsList
	* Copy the contents of lineBuffer into roomsList[i] */

	else {
		for (i = 0; i < 9; i++) {
			fgets (lineBuffer, 200, inputFile);
			 roomsList[i]= malloc(sizeof(char) * (strlen(lineBuffer)+1));
			  strcpy(roomsList[i], lineBuffer);
		}
	} 

	/*Return the 2-D string 'roomsList' to main*/

	return roomsList;
}

void quitClose () {
	
	/*Print an ANSCI banner, exclaiming that the user quit */
	
	printf("*****************************\n");
	printf("...You abandoned your hero...\n");
	printf(".............................\n");
	printf(".......  ---     ---  .......\n");
	printf(".......    _______    .......\n");
	printf(".......   /       \\   .......\n");	
	printf(".............................\n");
}

void deadClose () {
	
	/*Print an ANSCI banner, exclaiming that the hero died */
	
	printf("*****************************\n");
	printf("...........You died..........\n");
	printf(".............................\n");
	printf(".......   \\/     \\/   .......\n");
	printf(".......   /\\     /\\   .......\n");
	printf(".......    _______    .......\n");
	printf(".............................\n");

}

void winClose () {
	
	/*Print an ANSCI banner, exclaiming that the hero escaped */
	
	printf("*****************************\n");
	printf("...You escaped the dungeon!..\n");
	printf(".............................\n");
	printf(".......   A       A   .......\n");
	printf(".......   _________   .......\n");	
	printf(".......   \\_______/   .......\n");
	printf(".............................\n");

}

void gameClose (int roomNumber, int treasures, int weapons, int potions, int monsterKills) {
	
	/*Print the game statistics; treasures, weapons, potions, kills & level*/
	
	printf("*****************************\n");
	printf("............STATS............\n");
	printf("........Treasures - %d........\n", treasures);
	printf("..Weapons - %d....Potions - %d.\n", weapons, potions);
	printf("....Level - %d....Kills - %d...\n", roomNumber, monsterKills);
	printf("*****************************\n");
}