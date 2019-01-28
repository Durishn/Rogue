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

char * roomCreator (char * currentRoom) {

	/* Initialize a integer; 'roomsWidth' and 'roomLength' to hold the rooms length and width
	* 'elementCount' counts elements in the room, and 'doorCount' counts doors
	* Initialize a string; 'token' as a token buffer, 'hero' for hero coordinates 
	* Initialize a 2-D string; 'door' and 'element' to hold door and element coordinates
	*Initialize*/

	int roomWidth, roomLength, elementCount, doorCount;
	char * token, *hero, **door, **element;

	/*Set 'elementCount' and 'doorCount' equal to zero*/
	
	elementCount = 0;
	doorCount = 0;
	
	/*Malloc 6 char* slots for 'door' and 50 char* slots for 'element'
	*Print 'Out of Memory' and exit if either values returns NULL */
	
	door = malloc(sizeof(char*)*6);
	if(door==NULL) {  printf("Out of memory\n"); refresh(); exit(0);}
	element = malloc(sizeof(char*)*50);
	if(element==NULL) {  printf("Out of memory\n"); refresh(); exit(0);}

	/*Set token equal to tokenized 'currentRoom' with a space as the delimiter
	* Scan the token, set 'roomLength' equal to the first integer and 'roomWidth' the second
	* Set token equal to the next token in currentRoom */
	
	token = strtok(currentRoom, " ");
	sscanf(token, "%dX%d", &roomLength ,&roomWidth);
	token = strtok(NULL, " ");
	hero = token;
	/*While the token isn't Null. 
	* If the first slot is a 'd' then set door at doorCount equal to the token and increase
	* doorcount by 1. If its not 'd' than set element at elementCount eqaul to the token
	* and increase elementCount by 1. If it's 'h' than set 'hero' equal to the token  */
	
	while (token != NULL) {
	 	if (token[0] == 'd') {
			door[doorCount] = token;
			doorCount++;
		}
		else {
			element[elementCount] = token;
			elementCount++;
			if (token[0] == 'h')
				hero = token;
		}
		token = strtok(NULL, " ");
	}
	
	/*Call the functions roomDraw and elementDraw*/
	
	roomDraw (roomWidth, roomLength, door, doorCount);
	elementDraw(element, elementCount);
	
	/* Free door and element's memory. Refresh the screen and return 'hero' */
	
	free(door);
	free(element);
	refresh();
	return hero;
}

void roomDraw(int roomWidth, int roomLength, char ** door, int doorCount) {
	
	/*Initialize an integer; 'i', 'j' for counting and 'doorDist' for the doors wall location
	* Initialize a character; 'wall' for the doors respective wall*/
	
	int i, j, doorDist;
	char wall;

	/*Enter a loop starting with 'i' at 4, increases by one, until 'roomWidth' plus four
	* Add '-' to the coordinate given by 'roomLength' and 'i'
	* Add '-' to the coordinate given by 1 and 'i' */

	for (i=4; i<roomWidth+4; i++){     
		mvaddch (roomLength, i, '-');
		mvaddch (1, i, '-');
	}

	/*Enter a loop starting with 'i' at 2, increases by one, until 'roomLength'
	* Add '|' to the coordinate given by 'roomWidth' and 'i'
	* Add '|' to the coordinate given by 4 and 'i'*/

	for (i=2; i<roomLength; i++){    
		mvaddch (i, 4, '|');
		mvaddch (i, roomWidth+3, '|');  
	}

	/*Enter a loop starting with 'i' at 2, increases by one, until 'roomLength'
	* Enter a loop startin with 'j' at 5, increasing by one, until 'roomWidth +3)
	* Add '.' to the coordinate given by 'j' and 'i'*/

	for (i=2; i<roomLength; i++) {
		for (j=5; j<roomWidth+3; j++)
			mvaddch(i,j,'.');
	}
	
	/*Enter a loop starting with 'i' at 0, increases by one, until 'doorCount'
	* Scan the token, set wall equal to the second slot and 'doorDist' equal to the third*/

	for (i=0; i<doorCount; i++) {
		sscanf(door[i], "d%c%d" ,&wall ,&doorDist);
		
		/* Defend against impossible door positions.
		* While 'doorDist' is less than or equal to 1, increase 'doorDist' by one */
		
		while (doorDist <= 1)
			doorDist++;	

			/*If wall is 'n'. 
			* While 'doorDist is greater than or equal to 'roomWidth' decrease doorDist by 1.
			* add a '+' to the coordinates given by 1 and 'doorDist' plus 3 */
			
			switch (wall){
			case 'n':
			while (doorDist >= roomWidth)
				doorDist--;
			mvaddch(1, doorDist+3, '+');
			break;
			
			/*If wall is 'e'. 
			* While 'doorDist is greater than or equal to 'roomLength' decrease doorDist by 1.
			* add a '+' to the coordinates given by'doorDist' plus roomWidth plus 3*/
			
			case 'e':
			while (doorDist >= roomLength)
				doorDist--;
			mvaddch (doorDist, roomWidth+3, '+');
			break;
			
			/*If wall is 's'. 
			* While 'doorDist is greater than or equal to 'roomWidth' decrease doorDist by 1.
			* add a '+' to the coordinates given by roomLength and 'doorDist' plus 3 */
			
			case 's':
			while (doorDist >= roomWidth)
				doorDist--;
			mvaddch(roomLength, doorDist+3, '+');
			break;
			
			/*If wall is 'w'. 
			* While 'doorDist is greater than or equal to 'roomLength' decrease doorDist by 1.
			* add a '+' to the coordinates given by 'doorDist' and four */
			
			case 'w':
			while (doorDist >= roomLength)
				doorDist--;
			mvaddch (doorDist, 4, '+');
			break;
		}
	}
}

void elementDraw(char ** element,int elementCount) {
	
	/*Initialize an integer; 'x' for x-coordinate, 'y' for y-coordinate, 'i' for counting
	* Initialize a character; 'elementType' for the type of element*/
	
	int x, y, i;
	char elementType;
	
	/*Enter a loop starting with 'i' at 0, increases by one, until 'elementCount' 
	*Scan the element[i]. Set 'elementType' to the first character, 'x' to the first integer
	* 'y' to the second integer. Move the cursor to position 'y' plus 2 and 'x' plus 5 */
	
	for (i=0; i<elementCount; i++) {
		sscanf(element[i], "%c%d,%d", &elementType, &x, &y);
		move (y+2,x+5);
			
			/*If 'elementType' is h. If the symbol at the cursor is not a '.' set 'x; and 'y' to 0
			* Move the cursor to position 'y' plus 2 and 'x' plus five
			* While the symbol at the cursor is not a '.' increase x by one and move the cursor.*/
			
	 		switch (elementType){
			case 'h':
				if (winch(stdscr) != '.') {
					x = 0;
					y = 0;
					move (y+2,x+5);
					while (winch(stdscr) != '.') {
						x++; 
						move (y+2, x+5);
					} 
				}	
				
				/*Turn on colour attribute BOLD and color pair 1
				* Add a '@' to 'y' plus 2 and 'x' plus 5
				*Turn off colour attribute BOLD and colour pair 1 */
				
				attron(A_BOLD);
				attron(COLOR_PAIR(1));
		 		mvaddch(y+2, x+5, '@');
				attroff(COLOR_PAIR(1));
				attroff(A_BOLD);
			break;
			
			/*If 'elementType' is m. If the symbol at the cursor is not a '.' set 'x; and 'y' to 0
			* Move the cursor to position 'y' plus 2 and 'x' plus five.
			* While the symbol at the cursor is not a '.' increase x by one and move the cursor
			* Add a 'M' to 'y' plus 2 and 'x' plus 5 .*/
			
			case 'm':
				if (winch(stdscr) != '.') {
					x = 0;
					y = 0;
					move (y+2,x+5);
					while (winch(stdscr) != '.') {
						x++;
						move (y+2, x+5);
					} 
				}
				mvaddch(y+2, x+5, 'M');
			break;
			
			/*If 'elementType' is t. If the symbol at the cursor is not a '.' set 'x; and 'y' to 0
			* Move the cursor to position 'y' plus 2 and 'x' plus five.
			* While the symbol at the cursor is not a '.' increase x by one and move the cursor
			* Add a '*' to 'y' plus 2 and 'x' plus 5 . */
			
			case 't':
			  if (winch(stdscr) != '.') {
					x = 0;
					y = 0;
					move (y+2,x+5);
					while (winch(stdscr) != '.') {
						x++;
						move (y+2, x+5);
					} 
				}
				mvaddch(y+2, x+5, '*');
			break;
			
			/*If 'elementType' is p. If the symbol at the cursor is not a '.' set 'x; and 'y' to 0
			* Move the cursor to position 'y' plus 2 and 'x' plus five.
			* While the symbol at the cursor is not a '.' increase x by one and move the cursor
			* Add a '!' to 'y' plus 2 and 'x' plus 5 . */
			
			case 'p':
			  if (winch(stdscr) != '.') {
					x = 0;
					y = 0;
					move (y+2,x+5);
					while (winch(stdscr) != '.') {
						x++;
						move (y+2, x+5);
					} 
				}
				mvaddch(y+2, x+5, '!');
			break;
			
			/*If 'elementType' is w. If the symbol at the cursor is not a '.' set 'x; and 'y' to 0
			* Move the cursor to position 'y' plus 2 and 'x' plus five.
			* While the symbol at the cursor is not a '.' increase x by one and move the cursor
			* Add a ')' to 'y' plus 2 and 'x' plus 5 .*/
			
			case 'w':
			  if (winch(stdscr) != '.') {
					x = 0;
					y = 0;
					move (y+2,x+5);
					while (winch(stdscr) != '.') {
						x++;
						move (y+2, x+5);
					} 
				}
				mvaddch(y+2, x+5, ')');
			break;
			
			/*If 'elementType' is not any of the above, print an error message and exit. */
			
			default:
				printf("ELEMENT PLACEMENT ERROR!"); exit(0);
			break;	
		}
  }
}

void printMessage (char * s) {
 
	/*Turn on the text attributes; bold and colour pair 2(black on white).									
	*Print the string s on line 29.																												
	* Turn off the text attributes, bold and colour pair 2.*/

	attron(A_BOLD);
	attron(COLOR_PAIR(2));
	mvwprintw (stdscr, 29, 0, s);
	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);

	/*Move the cursor to positions 0,0  and refresh the window.*/

	move(0,0);
	refresh ();
}

void updateInv (int roomNumber, int treasures,int weapons,int potions, int monsterKills) {
	
	/*Initialize a string (with 90 slots); 'msg' is used to store messages*/
	
	char msg [90];
	
	/*Turn on the text attribute colour pair 2(black on white).									
	*Set msg. Print the string msg on line 29.	Set msg. Print the string msg on line 34.																											
	* Turn off the text attribute colour pair 2.	*/
	
	attron(COLOR_PAIR(2));
	sprintf(msg, "----------------------------\n");
	mvwprintw (stdscr, 33, 0, msg);
	sprintf(msg, "        Treasure - %d        \n Weapons - %d    Potions - %d \n Level # - %d      Kills - %d "
	, treasures, weapons, potions, roomNumber, monsterKills);
	mvwprintw (stdscr, 34, 0, msg);
	attroff(COLOR_PAIR(2));

	/*Move the cursor to position 0,0 and refresh*/

	move(0,0);
	refresh ();
}

void updateHealth (int heroHealth, int monsterHealth) {
	
	/*Initialize a string (with 90 slots); 'msg' is used to store messages */
	
	char msg [90];
	
	/*Turn on the text attribute colour pair 2(black on white).									
	*Set msg. Print the string msg on line 30.	Set msg. Print the string msg on line 31.	
	* Set msg. Print the string msg on line 32.	
	* Turn off the text attribute colour pair 2 */
	
	attron(COLOR_PAIR(2));
	sprintf(msg, "----------------------------\n");
	mvwprintw (stdscr, 30, 0, msg);
	sprintf(msg, "    Hero Health:            \n");
	mvwprintw (stdscr, 31, 0, msg);
	sprintf(msg, " Monster Health:            \n");
	mvwprintw (stdscr, 32, 0, msg);
	attroff(COLOR_PAIR(2));


	/*Turn on the text attribute colour pair 3
	* When 'heroHealth' is ten set msg, when 'heroHealth' is nine set msg, when...
	* when 'heroHealth'is default set msg. Print the string msg on line 31, column 17.
	* Turn off the text attribute colour pair 3 */
	
	attron(COLOR_PAIR(3));
	switch (heroHealth){
	case 10: 
	  sprintf(msg, "0000000000");
	break;
	case 9: 
	  sprintf(msg, "000000000");
	break;
	case 8: 
	  sprintf(msg, "00000000");
	break;
	case 7: 
	  sprintf(msg, "0000000");
	break;
	case 6: 
	  sprintf(msg, "000000");
	break;
	case 5: 
	  sprintf(msg, "00000");
	break;
	case 4: 
	  sprintf(msg, "0000");
	break;
	case 3: 
	  sprintf(msg, "000");
	break;
	case 2: 
	  sprintf(msg, "00");
	break;
	case 1: 
	  sprintf(msg, "0");
	break;
	case 0: 
	break;
	default:
	  sprintf(msg, "error");
	break;		
	}
	mvwprintw (stdscr, 31, 17, msg);
	attroff(COLOR_PAIR(3));

	/*Turn on the text attribute colour pair 4
	* When 'heroHealth' is ten set msg, when 'heroHealth' is nine set msg, when...
	* when 'heroHealth'is default set msg. Print the string msg on line 32, column 17.
	* Turn off the text attribute colour pair 4 */

	attron(COLOR_PAIR(4));
	switch (monsterHealth){
	case 10: 
	  sprintf(msg, "0000000000");
	break;
	case 9: 
	  sprintf(msg, "000000000");
	break;
	case 8: 
	  sprintf(msg, "00000000");
	break;
	case 7: 
	  sprintf(msg, "0000000");
	break;
	case 6: 
	  sprintf(msg, "000000");
	break;
	case 5: 
	  sprintf(msg, "00000");
	break;
	case 4: 
	  sprintf(msg, "0000");
	break;
	case 3: 
	  sprintf(msg, "000");
	break;
	case 2: 
	  sprintf(msg, "00");
	break;
	case 1: 
	  sprintf(msg, "0");
	break;
	default:
	  sprintf(msg, "error");
	break;		
	}
	mvwprintw (stdscr, 32, 17, msg);
      attroff(COLOR_PAIR(4));

	/*Move the cursor to position 0,0 and refresh*/

	move(0,0);
	refresh ();
}

int moveHero(int dir, char * hero) {
  
	/*Initialize an integer; 'heroX' and 'heroY' for the hero's x and y position
	* 'element' for the element type */

	int heroX, heroY, element;
	
	/*Scan the 'hero'. Set 'heroX' to the first integer and 'heroY' to the second integer*/

	sscanf(hero, "h%d,%d", &heroX, &heroY);  

	/*If 'dir' is UP. Move the cursor to heroY plus 1 and heroX plus 5. 
	* If the symbol at the cursor is '.', '*', ')', '!' or '+' enter the loop
	* If the symbol is '*' set element equal to TREASURE. If the symbol is ')' set element 
	* equal to WEAPON. If '!' set to POTION. If '+' set to DOOR */
	
	switch (dir) {
	case UP:
	      move(heroY+1, heroX+5);
	      if ((winch(stdscr) == '.')||(winch(stdscr) == '*')||
		(winch(stdscr) == ')')||(winch(stdscr) == '!')||(winch(stdscr) == '+')) {
			if (winch(stdscr) == '*')
				element = TREASURE;
			if (winch(stdscr) == ')')
				element = WEAPON;
			if (winch(stdscr) == '!')
				element = POTION;
			if (winch(stdscr) == '+')
				element = DOOR;
			
			/*Turn on the text attributes; Bold and color pair 1.
			* Add @ to the position, heroY plus 1 and heroX plus 5
			* Turn off the text attributes; bold and color pair 1 
			* Add a . to the position heroY plus 2 and heroX plus 5. Decrease heroY by 1*/	
				
			attron(A_BOLD);
			attron(COLOR_PAIR(1));	 
			mvaddch(heroY+1, heroX+5, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroY--;
		}
	
		/*If the symbol at the cusor is 'M' then set element to MONSTER */
	
		else if (winch(stdscr) == 'M') 
			element = MONSTER;
		break;

	/*If 'dir' is DOWN. Move the cursor to heroY plus 3 and heroX plus 5. 
	* If the symbol at the cursor is '.', '*', ')', '!' or '+' enter the loop
	* If the symbol is '*' set element equal to TREASURE. If the symbol is ')' set element 
	* equal to WEAPON. If '!' set to POTION. If '+' set to DOOR */

	case DOWN:
		move(heroY+3, heroX+5);
		if ((winch(stdscr) == '.')||(winch(stdscr) == '*')||
		   (winch(stdscr) == ')')||(winch(stdscr) == '!')||(winch(stdscr) == '+')) {
			if (winch(stdscr) == '*')
				element = TREASURE;
			if (winch(stdscr) == ')')
				element = WEAPON;
			if (winch(stdscr) == '!')
				element = POTION;
			if (winch(stdscr) == '+')
				element = DOOR;
				
			/*Turn on the text attributes; Bold and color pair 1.
			* Add @ to the position, heroY plus 3 and heroX plus 5
			* Turn off the text attributes; bold and color pair 1 
			* Add a . to the position heroY plus 2 and heroX plus 5. Increase heroY by 1*/	
				
			attron(A_BOLD);
			attron(COLOR_PAIR(1));	 
			mvaddch(heroY+3, heroX+5, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroY++;
		}
		
		/*If the symbol at the cusor is 'M' then set element to MONSTER */
		
		else if (winch(stdscr) == 'M')
		  element = MONSTER;
		break;

	/*If 'dir' is DOWN. Move the cursor to heroY plus 2 and heroX plus 4. 
	* Then repeat the same steps as above, but instead with heroY plus 2 and heroX plus 4*/

	case LEFT:
	      move(heroY+2, heroX+4);
	      if ((winch(stdscr) == '.')||(winch(stdscr) == '*')||
	      (winch(stdscr) == ')')||(winch(stdscr) == '!')||(winch(stdscr) == '+')) {
			if (winch(stdscr) == '*')
				element = TREASURE;
			if (winch(stdscr) == ')')
				element = WEAPON;
			if (winch(stdscr) == '!')
				element = POTION;
			if (winch(stdscr) == '+')
				element = DOOR;
			attron(A_BOLD);
	  	attron(COLOR_PAIR(1));	 
			mvaddch(heroY+2, heroX+4, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroX--;
		}
		else if (winch(stdscr) == 'M')
		  element = MONSTER;
		break;

	/*If 'dir' is RIGHT. Move the cursor to heroY plus 2 and heroX plus 6. 
	* Then repeat the same steps as above, but instead with heroY plus 2 and heroX plus 6*/

	case RIGHT:
		move(heroY+2, heroX+6);
		if ((winch(stdscr) == '.')||(winch(stdscr) == '*')||
		(winch(stdscr) == ')')||(winch(stdscr) == '!')||(winch(stdscr) == '+')) {
			if (winch(stdscr) == '*')
				element = TREASURE;
			if (winch(stdscr) == ')')
				element = WEAPON;
			if (winch(stdscr) == '!')
				element = POTION;
			if (winch(stdscr) == '+')
				element = DOOR;
			attron(A_BOLD);
	  	attron(COLOR_PAIR(1));	 
			mvaddch(heroY+2, heroX+6, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroX++;
	  }
		else if (winch(stdscr) == 'M')
			element = MONSTER;
	break;
	}

	/*Change the hero string so that in contains the hero's new coordinates
	* Move to position 0,0. Refresh the page. Return element */
	
	sprintf(hero, "h%d,%d", heroX, heroY);
	move(0,0);
	refresh ();
	return element;
}

void monsterKill(int dir, char * hero) {
	
	/*Initialize an integer; 'heroX' and 'heroY' for the hero's x and y coordinates*/
	int heroX, heroY;

	/*Scan the 'hero'. Set 'heroX' to the first integer and 'heroY' to the second integer*/

	sscanf(hero, "h%d,%d", &heroX, &heroY);

	/*If dir is UP. Turn on the text attributes; Bold and color pair 1.
	* Add @ to the position, heroY plus 1 and heroX plus 5
	* Turn off the text attributes; bold and color pair 1 
	* Add a . to the position heroY plus 2 and heroX plus 5. Decrease heroY by 1*/

	switch(dir){
		case UP:
		 	attron(A_BOLD);
			attron(COLOR_PAIR(1));	 
			mvaddch(heroY+1, heroX+5, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroY--;
		break;
		
		/*If dir is DOWN. Turn on the text attributes; Bold and color pair 1.
		* Add @ to the position, heroY plus 3 and heroX plus 5
		* Turn off the text attributes; bold and color pair 1 
		* Add a . to the position heroY plus 2 and heroX plus 5. Increase heroY by 1*/
		
		case DOWN:
		 	attron(A_BOLD);
			attron(COLOR_PAIR(1));	 
			mvaddch(heroY+3, heroX+5, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroY++;
		break;
		
		/*If dir is LEFT. Do the same as above with coordinate heroY plus 2 and heroX plus 4.
		* Instead of increasing heroY, Decrease heroX by 1*/
		
		case LEFT:
		 	attron(A_BOLD);
			attron(COLOR_PAIR(1));	 
			mvaddch(heroY+2, heroX+4, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroX--;
		break;
		
		/*If dir is RIGHT. Do the same as above with coordinate heroY plus 2 and heroX plus 6.
		* Instead of decreasing heroX, Increase heroX by 1*/
		
		case RIGHT:
		 	attron(A_BOLD);
			attron(COLOR_PAIR(1));	 
			mvaddch(heroY+2, heroX+6, '@');
			attroff(COLOR_PAIR(1));
			attroff(A_BOLD);
			mvaddch(heroY+2, heroX+5, '.');
			heroX++;
		break;
	}
	
	/*Change the hero string so that in contains the hero's new coordinates
	* Move to position 0,0. Refresh the page.*/
	
	sprintf(hero, "h%d,%d", heroX, heroY);
	move(0,0);
	refresh ();
}
