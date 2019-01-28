/*Include the ncurses.h library to add cursor functions.    															
* Include the stdlib.h library to add memory allocating functions.												
* Include the string.h library to add string manipulating functions.											
* Define the words UP, DOWN, LEFT and RIGHT as 1,2,3 and 4 respectively.									
* Define the words POTION, WEAPON, TREASURE, MONSTER, DOOR as 1,2,3,4 and 5 respectivel   
* -This will allow us to send directions and elements as words instead of numbers.*/ 

#include <ncurses.h> 
#include <stdlib.h>
#include <string.h>
#define UP	1
#define DOWN	2
#define LEFT	3
#define RIGHT	4
#define POTION 1
#define WEAPON 2
#define TREASURE 3
#define MONSTER 4
#define DOOR 5

/* Rogue Introduction Screen Function.																										
* -This function prints the game title, controls and legend 															
* -It prompts the user to hit [enter] to play the game */

void gameIntro();

/* Curses Initialization Function.																												
* -This function initializes curses mode																									
* -Takes input chars individual																														
* -Enables keyboard mapping*/

void initCurses();

/* File Reading Function.																																
*	 -This function copies the files contents into a 2-Dimensional array	              		
*	 -It takes a file as input and returns the 2-Dimensional array*/

char ** readFile(FILE*);

/* Room Information Organizing Function												   													
*  -This function splits an array into different elements and coordinates and then sends  
*  them to their respective drawing function.				  																		
*	 -It takes the current room (array) as input and returns the hero token.*/

char * roomCreator(char *);

/* Room Drawing Function																		
*	-This function draws the rooms; floor, walls and doors
*	-It takes the rooms; Length, Width, Door Coordinates, and number of doors*/

void roomDraw(int, int, char **, int);

/* Element Drawing Function																
*	 -This function draws the elements within the room.
*	-It takes the element Coordinates and number of elements as input*/

void elementDraw(char**,int);

/* Message Printing Function
*	-This function prints the announcements at the bottom of the screen
* -It takes the message as an input*/

void printMessage(char*);

/* Inventory Updating	Function														
*	-This function updates the visual inventory at the bottom of the screen
*	-It takes the room number, treasures collected, weapons collected, potions collected
* and monsters killed as input*/

void updateInv(int, int, int, int, int);

/* Health Updating Function																
*	-This function updates the visual health bars at the bottom of the screen				
*	-It takes the hero's health and the monsters health as input*/

void updateHealth(int, int);

/* Hero Movement Function																	
*	-This function moves the hero to the specified direction, replacing its previous
* position with a '.' .				
*	-It takes the hero's coordinates and the direction as input.
* -It returns the element that the hero interacted with*/

int moveHero(int, char *);

/* Monster Killing Function																
*	-This function kills a monster and puts the hero into the monsters position
* -It takes the hero's coordinates and the direction as input*/

void monsterKill(int, char*);

/* Quit-Game Closing Statement Function
*	 -This function prints a message exclaiming to the user that he abandoned his hero!*/

void quitClose();

/* Lose-Game Closing Statement Function
* -This function prints a message exclaiming to the user that he has died.*/

void deadClose();

/* Win-Game Closing Statement Function
* -This function prints a message exclaiming that the user has reached the last room.*/

void winClose();

/* Game Stats Function
* -This function prints the game stats.
* -It takes the room number, treasures collected, weapons collected, potions collected
* and monsters killed as input*/

void gameClose(int, int, int, int, int);