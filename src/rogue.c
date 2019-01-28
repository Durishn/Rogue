/***************************************rogue.c***************************************
Student Name: Nic Durish                        Student Number:  0757227
Date: March 4, 2013                         Course Name: Intermediate Programming
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

int main(int argc, char * argv[]) {
	
	/*Initializing integers;
	*-'i' for counting, 'roomNumber' for keeping track of the current room,
	*'dir' for the desired direction, 'element' for the current element,
	*'potions', 'weapons', and 'treasures' keeps track of the amount of the element
	*'monsterKills' tracks the number of kilss
	*'monsterHealth' and 'heroHealth' track the hero and monsters lifepoints out of ten*/
	
	int i, roomNumber, dir, element, potions, weapons, treasures;
	int  monsterKills, monsterHealth, heroHealth;
	
	/*Initializing characters;
	* - (2-D string) 'roomsList' for holding the entire input file
	* (string) 'currentRoom' for holding one rooms info, (string) 'hero' for holding the
 	* hero's coordinates, (150 slot string) 'msg' to hold a specified message
	*'inputChar' to hold the users inputed character */
	
	char ** roomsList, *currentRoom, *hero, msg[150], inputChar;
	
	 /*Initializing a file 'inputFile' is the file inputed by the user during excecution*/
	
	FILE *inputFile = NULL;	
	
	/*Defence against the absence of an argument or argument overflow*/
	if (argc != 2) {
	printf("Error: Please supply the program with the name of one input file\n");
	exit (1); }

	/*Set inputFile equal to the file inputed by the user
 	* Set roomsList equal to the return of the function readFile
	* close inputFile*/

        inputFile = fopen (argv[1], "r");
	roomsList = readFile(inputFile);
        fclose(inputFile);
  
	/*Call the functions gameIntro, initCurses, and start_color
	*Initialize four colour pairs; Yellow on Black (1), Black on White (2), Green on Green (3)
	*	ad Red on Red (4)*/

	gameIntro();
	initCurses();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_RED, COLOR_RED);
	
	/*Set variables. Set 'treasures', 'weapons', 'potions' and 'monsterKills' as 0
	* Set 'monsterHealth' and 'heroHealth' equal to 10. Set 'inputChar' equal to ' '*/
	
	treasures = 0;
	weapons = 0;
	potions = 0;
	monsterKills = 0;
	monsterHealth = 10;
	heroHealth = 10;
	inputChar = ' ';
	
	/*Enter a for loop. set 'roomNumber' equal to 1 and increase by 1 each iteration til 9
	*  Set element equal to zero, clear the screen and set currentRoom equal to the 
	*  current rooms information. */
	
	for(roomNumber = 1; roomNumber <= 9; roomNumber++) {
		element = 0;
		clear();
		currentRoom = roomsList[roomNumber - 1];
		
		/*Set hero equal to the return of roomCreator
		* Set a msg*/
		
		hero = roomCreator(currentRoom);
		sprintf(msg, "   Welcome  to  Level  %d    ", roomNumber);
	
		/*Call the functions, printMessage, updateInv, and updateHealth */
	
		printMessage(msg);
		updateInv(roomNumber, treasures, weapons, potions, monsterKills);
		updateHealth (heroHealth, monsterHealth);

		/*Set inputChar equal to the user character input
		* while inputChar doesn't equal q, and element doesn't equal DOOR and heroHealth
		*	doesn't equal zero than enter a loop*/

		while (((inputChar = getch()) != 'q') && (element != DOOR) && (heroHealth != 0)) {
			
			/*If  inputChar is 'n' break from the loop*/
			
			if (inputChar == 'n')
				break;		
				
			/*If inputChar is 'k' set dir to UP, if 'j' set dir to DOWN, if 'h' set LEFT
			*if 'l' set RIGHT. If anything else set dir as 0, set a msg and call printMessage*/	
					
			switch (inputChar) {
			case 'k': 
				dir = UP;
				break;
			case 'j': 
				dir = DOWN;
				break;	
			case 'h': 
				dir = LEFT;
				break;
			case 'l': 
				dir = RIGHT;
				break;
			default:
				sprintf (msg, "        Invalid  Entry.     ");
				printMessage(msg);
				dir = 0;
				break;
			}	

			/*Set element equal to the return of moveHero */

			element = moveHero(dir, hero);
    
			/*If dir is not 0. If element is POTION. Increase 'potion' by one and 'heroHealth'
			* by two*/

			if (dir != 0) {
				switch (element) {
				case POTION:
					potions++;
					heroHealth += 2;
						
					/*If heroHealth is less greater than ten, set heroHealth to ten
					* Call function updateHealth. Set a msg and call printMessage */
						
					if (heroHealth >10)
						heroHealth = 10;
					updateHealth (heroHealth, monsterHealth);
					sprintf (msg, " Found A Potion! +2 Health");
					printMessage(msg);
				break;
						
				/*If element is WEAPON. Increase 'weapons' by one. Set a msg and call printMessage
				* If it's TREASURE. Increase 'treasures' by one. Set a msg and call printMessage*/
					
				case WEAPON:
					weapons++;
					sprintf (msg, "  Found A Weapon!  +1 Dmg ");
					printMessage(msg);
					break;
				case TREASURE:
					treasures++;
					sprintf (msg, "      Found Treasure!      ");
					printMessage(msg);
					break;
					
				/*If element is MONSTER. Decrease 'heroHealth' by one. 
				*If 'weapons; is not 0. Set 'monsterHealth' equal to monsterHealth minus weapons
				* If monsterHealth' is greater than zero. Set msg and call printMessage*/
					
				case MONSTER:
					heroHealth--;
					if (weapons != 0) {
						monsterHealth = monsterHealth - weapons;				
						if (monsterHealth > 0){
							sprintf (msg, "Attack for %ddmg. Took 1 dmg", weapons);
							printMessage(msg);
						}
				
						/*If monsterhealth is less than or equal to zero. Call monsterKill.
						* Increase'monsterKills' by one. Set monsterHealth to ten. Set msg,
						* call printMessage */
					
						else {
							monsterKill(dir, hero);
							monsterKills++;
							monsterHealth = 10;
							sprintf (msg, "    You Killed A Monster!   ");
							printMessage(msg);
						}	 
					}
			
					/*If weapons equals zero. Set msg and call printMessage.
					* Call updateHealth*/
			
					else {
						sprintf(msg, "   You Need A Weapon - )    ");
						printMessage(msg);
					}
					updateHealth (heroHealth, monsterHealth);		
					break;

				/*If element is not one of the prementions, set msg and call printMessage
				* Call updateInv. */

				default:
					sprintf (msg, "                            ");
					printMessage(msg);
					break;
				}
				updateInv(roomNumber, treasures, weapons, potions, monsterKills);
			}
		
			/*If 'heroHealth' equals zero, break from the room loop
			* If 'inputChar' equals 'q' or 'heroHealth' is zero break from the game loop
			* End the ncurses window. */
			
			
			if (heroHealth == 0)
				break;
		}
		if ((inputChar == 'q') || (heroHealth == 0))
			break;
 	}   
	endwin();
	
	/*If 'inputChar' equals q call quitClose. If 'heroHealth' is zero call deadClose.
	* Else call winClose. Call gameClose*/
	
	if (inputChar == 'q') 
		quitClose();
	else if (heroHealth == 0)	
		deadClose();
	else
		winClose();	
	gameClose (roomNumber, treasures, weapons, potions, monsterKills);  
	
	/*Enter a for loop. Set 'i' equal to 0 and increase by 1 each iteration til 9
	* Free the memory in each room. Then free the memory for the entire 2-D string.
	* Return 0 to the OS*/
	
	for(i = 0; i < 9; i++) {
		free(roomsList[i]);
	}
	free(roomsList);
	return 0;	
}