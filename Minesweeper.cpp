/*
	Started: 26.03.2019
	Finished: 05.05.2019
	Actual time spent on project: ~15 hours
	Was too busy to finish when wanted
*/

#include <iostream> // output
#include <cstdlib> // for randomizing bomb placements
#include <ctime> // for randomizing bomb placements
#include <Windows.h> // for coloring text
#include <conio.h> // for getting the direction symbol
#include "resource.h" // for app icon

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for colors
enum ConsoleColor { // replaces a number with a word so it's easier to look at
	Black = 0,
	DarkBlue = 1, // 
	DarkGreen = 2,
	DarkCyan = 3,
	DarkRed = 4,
	DarkPink = 5,
	Brown = 6,
	LightGray = 7,
	Gray = 8,
	Blue = 9,
	Green = 10,
	Cyan = 11,
	Red = 12,
	Pink = 13,
	Yellow = 14,
	White = 15
};

// Class that has all Tile info
class Tile {
private:
	bool m_IsOpened; // true if the tile is opened
	bool m_IsBombed; // true if the tile has a bomb in it
	bool m_IsUnderCursor; // true if the tile is under cursor
	bool m_IsFlaged; // true if the tile is flaged
	int m_bombsAround; // amount of bombs around the tile
public:
	// Default constructor, everything false
	Tile() {
		m_IsBombed = false;
		m_IsOpened = false;
		m_IsUnderCursor = false;
		m_IsFlaged = false;
		m_bombsAround = 1;
	}

	// Access functions for every member, returns true if the member is true or the number of bombs around
	bool IsBombed() {
		if (m_IsBombed)
			return true;
		return false;
	}
	bool IsOpened() {
		if (m_IsOpened)
			return true;
		return false;
	}
	bool IsUnderCursor() {
		if (m_IsUnderCursor)
			return true;
		return false;
	}
	bool IsFlaged() {
		if (m_IsFlaged)
			return true;
		return false;
	}
	int BombsAround() {
		return m_bombsAround;
	}

	// Setting functions, makes members true (or false) or sets bomb amount
	void SetBombed() {
		m_IsBombed = true;
	}
	void SetOpened() {
		m_IsOpened = true;
	}
	void SetUnderCursor() {
		m_IsUnderCursor = true;
	}
	void SetNotUnderCursor() {
		m_IsUnderCursor = false;
	}
	void SetFlaged() {
		m_IsFlaged = true;
	}
	void SetNotFlaged() {
		m_IsFlaged = false;
	}
	void SetBombsAround(int amount) {
		m_bombsAround = amount;
	}
};

// Prints tiles and allows to easily chage colors of everything
void PrintTile(char inside, int insideColor, int bracketColor = LightGray, int backgroundColor = Black) {
	SetConsoleTextAttribute(hConsole, (WORD)((backgroundColor << 4) | bracketColor));
	std::cout << "[";
	SetConsoleTextAttribute(hConsole, (WORD)((backgroundColor << 4) | insideColor));
	std::cout << inside;
	SetConsoleTextAttribute(hConsole, (WORD)((backgroundColor << 4) | bracketColor));
	std::cout << "]";
}

int main() {
	system("title Minesweeper"); // changes the title of console window to Minesweeper
	SetConsoleCP(1251); // for russian symbols imput
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); // beginning color for everything is black background, white symbols

															  //---------------------------USER INTEFRACE and SETTING THE PLAYFIELD----------------------------
	char repeatChoice; // your answer when you decide to repeat or not
	do {
		int offsetHeight = 0, offsetWidth = 0; // the offset from [0][0]  position, used in CURSOR MOVEMENT

		system("mode con cols=42 lines=8"); // changes the size of the console window for user interaction screen
		int difficultyChoice = 0; // the chosen difficulty level

								  // PLAYFIELD PARAMETERS
		int width = 0, height = 0; // width and height of the playfield
		int bombsAmount = 0; // amount of bombs on the playfield
		int flagAmount = 0; // amount of flags a player can place

							// User interface
		std::cout << "Welcome to Minesweeper!" << std::endl;
		std::cout << "Choose difficulty" << std::endl
			<< "                   Height  Width  Bombs " << std::endl
			<< "(1) Beginner:         9       9      10  " << std::endl
			<< "(2) Intermediate:     16      16     40  " << std::endl
			<< "(3) Expert:           16      30     99  " << std::endl
			<< "(4) Custom:          you choose yourself" << std::endl;
		std::cout << "Your choice (choose the number): ";
		std::cin >> difficultyChoice;

		system("cls");

		switch (difficultyChoice)
		{
		case 1: { // Beginner
				  // Assigns all values
			height = 9;
			width = 9;
			bombsAmount = 10;
			flagAmount = bombsAmount;

			// States the chosen difficulty, playfield parameters, controls and starts the game
			system("mode con cols=37 lines=9"); // changes the size of the console window for stating diff screen
			std::cout << "Chosen difficulty: Beginner" << std::endl
				<< "Height: " << height << std::endl
				<< "Width: " << width << std::endl
				<< "Amount of bombs: " << bombsAmount << std::endl;
			std::cout << "Controls:" << std::endl
				<< "WASD - move the cursor" << std::endl
				<< "F - plase a flag" << std::endl
				<< "Space - open the tile" << std::endl;

			// Waits for player's input to start the game
			std::cout << "Press any button to start playing";
			_getch();

			// Changes the size of the console window to game screen
			system("mode con cols=28 lines=13");

			break;
		}
		case 2: { // Intermediate
				  // Assigns all values
			height = 16;
			width = 16;
			bombsAmount = 40;
			flagAmount = bombsAmount;

			// States the chosen difficulty and playfield parameters and starts the game
			system("mode con cols=37 lines=5"); // changes the size of the console window for stating diff screen
			std::cout << "Chosen difficulty: Expert" << std::endl
				<< "Height: " << height << std::endl
				<< "Width: " << width << std::endl
				<< "Amount of bombs: " << bombsAmount << std::endl;
			// Waits for player's input to start the game
			std::cout << "Press any button to start playing";
			_getch();

			// Changes the size of the console window to game screen
			system("mode con cols=49 lines=20");

			break;
		}
		case 3: {// Expert
				 // Assigns all values
			height = 16;
			width = 30;
			bombsAmount = 99;
			flagAmount = bombsAmount;

			// States the chosen difficulty and playfield parameters and starts the game
			system("mode con cols=37 lines=9"); // changes the size of the console window for stating diff screen
			std::cout << "Chosen difficulty: Intermediate" << std::endl
				<< "Height: " << height << std::endl
				<< "Width: " << width << std::endl
				<< "Amount of bombs: " << bombsAmount << std::endl;
			std::cout << "Controls:" << std::endl
				<< "WASD - move the cursor" << std::endl
				<< "F - plase a flag" << std::endl
				<< "Space - open the tile" << std::endl;
			// Waits for player's input to start the game
			std::cout << "Press any button to start playing";
			_getch();

			// Changes the size of the console window to game screen
			system("mode con cols=91 lines=20");

			break;
		}
		case 4: { // Custom
			system("mode con cols=34 lines=13"); // changes the size of the console window for stating diff screen

			// States the chosen difficulty and allow player to choose all parameters
			std::cout << "Chosen difficulty: Custom" << std::endl
				<< "Choose the paremeters" << std::endl
				// Parameters restrictions
				// Height can't be higher than 17 and Width can't be higher than 31
				// Otherwise it will work slowly
				// Amount of bombs can't be higher then bombs amount otherwise it nothing
				<< "1 < height < 17" << std::endl
				<< "0 < width < 31" << std::endl
				<< "0 < bombs < tiles amount:" << std::endl;

			// Choosing height
			std::cout << "Height: ";
			std::cin >> height;
			// Makes sure parameters restrictions are kept
			while (height <= 1 || height > 16) {
				system("cls");
				std::cout << "Chosen difficulty: Custom" << std::endl
					<< "Choose the paremeters" << std::endl
					<< "1 < height < 17" << std::endl
					<< "0 < width < 31" << std::endl
					<< "0 < bombs < tiles amount:" << std::endl;

				std::cout << "Height: ";
				std::cin >> height;
			}

			// Choosing width
			std::cout << "Width: ";
			std::cin >> width;
			// Makes sure parameters restrictions are kept
			while (width <= 0 || width > 30) {
				system("cls");
				std::cout << "Chosen difficulty: Custom" << std::endl
					<< "Choose the paremeters" << std::endl
					<< "1 < height < 17" << std::endl
					<< "0 < width < 31" << std::endl
					<< "0 < bombs < tiles amount:" << std::endl;

				std::cout << "Height: " << height << std::endl;

				std::cout << "Width: ";
				std::cin >> width;
			}

			// Choosing bombs amount
			std::cout << "Amount of bombs: ";
			std::cin >> bombsAmount;
			// Makes sure parameters restrictions are kept
			while (bombsAmount <= 0 || bombsAmount >= width * height) {
				system("cls");
				std::cout << "Chosen difficulty: Custom" << std::endl
					<< "Choose the paremeters" << std::endl
					<< "1 < height < 17" << std::endl
					<< "0 < width < 17" << std::endl
					<< "0 < bombs < tiles amount:" << std::endl;

				std::cout << "Height: " << height << std::endl;
				std::cout << "Width: " << width << std::endl;

				std::cout << "Amount of bombs: ";
				std::cin >> bombsAmount;
			}
			flagAmount = bombsAmount;

			std::cout << "Controls:" << std::endl
				<< "WASD - move the cursor" << std::endl
				<< "F - plase a flag" << std::endl
				<< "Space - open the tile" << std::endl;

			// Waits for player's input to start the game
			std::cout << "Press any button to start playing";
			_getch();

			// Changes the size of the console window to game screen
			// depending on the size of the playfield
			if (width < 7 && height < 7)
				system("mode con cols=20 lines=10");
			else {
				if (width < 11 && height < 11)
					system("mode con cols=33 lines=14");
				else {
					if (width < 17 && height < 17)
						system("mode con cols=49 lines=20");
					else {
						if (width < 31 && height < 17)
							system("mode con cols=91 lines=20");
					}
				}
			}

			break;
		}
		}

		// The playfield itself, you can choose how big it is
		Tile **PlayField = new Tile*[height];
		for (int i = 0; i < height; i++) {
			PlayField[i] = new Tile[width];
		}
		//----------------------------------------------------------------

		//----------------------SETTING BOMB POSITIONS ON THE PLAYFIELD----------
		srand((unsigned)time(0)); // automatically randomizes rand() values

								  // Randomly places bomb in tiles
		for (int i = 0; i < bombsAmount; i++) {
			int placeHeight = rand() % ((height - 1) - 0 + 1); // Height coordinate of the bomb
			int placeWidth = rand() % ((width - 1) - 0 + 1); // Width coordinate of the bomb

															 // Checks if a tile of those coordinates already has a bomb
															 // If it has, re-randoms it until it's not and places a bomb
			if (PlayField[placeHeight][placeWidth].IsBombed()) {
				while (PlayField[placeHeight][placeWidth].IsBombed()) { // re-randoming loop
					placeHeight = rand() % ((height - 1) - 0 + 1);
					placeWidth = rand() % ((width - 1) - 0 + 1);
				}
				PlayField[placeHeight][placeWidth].SetBombed(); // places the bomb in new coordiantes
			}
			else
				PlayField[placeHeight][placeWidth].SetBombed(); // places the bomb in set coordinates
		}
		//------------------------------------------------------------------------

		//----------------------COUNTING HOW MANY BOMBS ARE AROUND EVERY TILE-------------
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int bombsAround = 0; // the amount of bombs around the tile

									 // Counts how many bombs are around the tile
									 // Special cases for tiles what are on the edges or last lines
									 // so the don't use a tile that doen't exist
				if (i == 0) { // first vertical line, can't do left
					if (j == 0) { // 0-0 tile
						if (PlayField[i + 1][j].IsBombed())
							bombsAround++;
						if (PlayField[i + 1][j + 1].IsBombed())
							bombsAround++;
						if (PlayField[i][j + 1].IsBombed())
							bombsAround++;
					}
					else {
						if (j == (width - 1)) { // 0-last tile
							if (PlayField[i + 1][j].IsBombed())
								bombsAround++;
							if (PlayField[i + 1][j - 1].IsBombed())
								bombsAround++;
							if (PlayField[i][j - 1].IsBombed())
								bombsAround++;
						}
						else { // only first vertical line
							if (PlayField[i + 1][j].IsBombed())
								bombsAround++;
							if (PlayField[i + 1][j + 1].IsBombed())
								bombsAround++;
							if (PlayField[i + 1][j - 1].IsBombed())
								bombsAround++;
							if (PlayField[i][j - 1].IsBombed())
								bombsAround++;
							if (PlayField[i][j + 1].IsBombed())
								bombsAround++;
						}
					}
				}
				else {
					if (i == (height - 1)) { // last vertical line, can't do right
						if (j == 0) { // last-0 tile
							if (PlayField[i - 1][j].IsBombed())
								bombsAround++;
							if (PlayField[i - 1][j + 1].IsBombed())
								bombsAround++;
							if (PlayField[i][j + 1].IsBombed())
								bombsAround++;
						}
						else {
							if (j == (width - 1)) { // last-last tile
								if (PlayField[i - 1][j].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j - 1].IsBombed())
									bombsAround++;
								if (PlayField[i][j - 1].IsBombed())
									bombsAround++;
							}
							else { // only last vertical line
								if (PlayField[i - 1][j].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j + 1].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j - 1].IsBombed())
									bombsAround++;
								if (PlayField[i][j - 1].IsBombed())
									bombsAround++;
								if (PlayField[i][j + 1].IsBombed())
									bombsAround++;
							}
						}
					}
					else {
						if (j == 0) { // only first horizontal line, can't do up
							if (PlayField[i + 1][j].IsBombed())
								bombsAround++;
							if (PlayField[i + 1][j + 1].IsBombed())
								bombsAround++;
							if (PlayField[i - 1][j + 1].IsBombed())
								bombsAround++;
							if (PlayField[i - 1][j].IsBombed())
								bombsAround++;
							if (PlayField[i][j + 1].IsBombed())
								bombsAround++;

						}
						else {
							if (j == (width - 1)) { // only first horizontal line, can't do down
								if (PlayField[i + 1][j].IsBombed())
									bombsAround++;
								if (PlayField[i + 1][j - 1].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j - 1].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j].IsBombed())
									bombsAround++;
								if (PlayField[i][j - 1].IsBombed())
									bombsAround++;
							}
							else { // no restrictions
								if (PlayField[i + 1][j].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j].IsBombed())
									bombsAround++;
								if (PlayField[i][j + 1].IsBombed())
									bombsAround++;
								if (PlayField[i][j - 1].IsBombed())
									bombsAround++;
								if (PlayField[i + 1][j + 1].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j + 1].IsBombed())
									bombsAround++;
								if (PlayField[i + 1][j - 1].IsBombed())
									bombsAround++;
								if (PlayField[i - 1][j - 1].IsBombed())
									bombsAround++;
							}
						}
					}
				}

				// Sets tile's bomb amount of the tile itself
				PlayField[i][j].SetBombsAround(bombsAround);
			}
		}
		//--------------------------------------------------------------------

		//-----------------------GAME'S LOOP-------------------
		bool GameWon = false; // true if you won the game
		bool GameLost = false; // true if you lost the game

		PlayField[0][0].SetUnderCursor(); // Sets the cursor to the beginning position

		do {
			//--------------PRINTING CURRENT GAME STATE-------------------------
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); // beginning color for everything is black background, white symbols
			std::cout << "Bombs left: " << flagAmount << std::endl;
			//------------------------------------------------------------------

			//----------------------------PRINTING THE PLAYFIELD----------------
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (PlayField[i][j].IsUnderCursor()) { // Prints the cursor (down arrow symbol)
						PrintTile((char)537, Pink, Pink);
					}
					else {
						if (PlayField[i][j].IsFlaged()) { // Prints flaged tile
							PrintTile('F', Yellow);
						}
						else {
							// Prints every tile
							if (PlayField[i][j].IsOpened()) {
								// Every number of bombs has a different color
								switch (PlayField[i][j].BombsAround()) {
								case 0: { // 0 - white
									PrintTile('0', LightGray);
									break;
								}
								case 1: { // 1 - blue
									PrintTile('1', DarkCyan);
									break;
								}
								case 2: { // 2 - green
									PrintTile('2', Green);
									break;
								}
								case 3: { // 3 - red
									PrintTile('3', Red);
									break;
								}
								case 4: { // 4 - dark blue
									PrintTile('4', Blue);
									break;
								}
								case 5: { // 5 - brown
									PrintTile('5', Brown);
									break;
								}
								case 6: { // 6 - cyan
									PrintTile('6', Cyan);
									break;
								}
								case 7: { // 7 - black
									PrintTile('7', Gray);
									break;
								}
								case 8: { // 8 - grey
									PrintTile('8', LightGray);
									break;
								}
								}

								continue;
							}
							else { // if the tile is not openetd, prints an unopened tile
								PrintTile(' ', Black, White);
							}
						}

					}

				}
				std::cout << std::endl;
			}
			//-------------------------------------------------------------------------------------

			//-------------------------------CURSOR MOVEMENT----------------------------
			//static int offsetHeight = 0, offsetWidth = 0; // the offset from [0][0]  position
			char playerInput = _getch(); //  the direction of movement of the cursor

										 // Does things depending on the player input
			switch (playerInput) {
				// MOVEMENT
			case 'w': { //  w - up
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight--;
				break;
			}
			case 's': { // s - down
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight++;
				break;
			}
			case 'a': { // a - left
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth--;
				break;
			}
			case 'd': { // d - right
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth++;
				break;
			}
					  // For CAPS lock
			case 'W': { //  W - up
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight--;
				break;
			}
			case 'S': { // S - down
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight++;
				break;
			}
			case 'A': { // A - left
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth--;
				break;
			}
			case 'D': { // D - right
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth++;
				break;
			}
					  // Russian symbols
			case 'ö': { // ö = w - up
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight--;
				break;
			}
			case 'û': { // û = s - down
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight++;
				break;
			}
			case 'ô': { // ô = a - left
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth--;
				break;
			}
			case 'â': { // â = d - right
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth++;
				break;
			}
					  // For CAPS lock russian symbols
			case 'Ö': { //  Ö = W - up
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight--;
				break;
			}
			case 'Û': { // Û = S - down
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetHeight++;
				break;
			}
			case 'Ô': { // Ô = A - left
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth--;
				break;
			}
			case 'Â': { // Â = D - right
				PlayField[offsetHeight][offsetWidth].SetNotUnderCursor();
				offsetWidth++;
				break;
			}

					  // PLACING A FLAG
			case 'f': {
				// If the tile is not flaged, it puts a flag in it, if it is, it removes it
				if (!PlayField[offsetHeight][offsetWidth].IsFlaged()) {
					if (flagAmount == 0) {} // if you have no flags left, it does nothing
					else {
						PlayField[offsetHeight][offsetWidth].SetFlaged();
						flagAmount--;
					}
				}
				else {
					PlayField[offsetHeight][offsetWidth].SetNotFlaged();
					flagAmount++;
				}
				break;
			}
					  // For CAPS lock
			case 'F': {
				// If the tile is not flaged, it puts a flag in it, if it is, it removes it
				if (!PlayField[offsetHeight][offsetWidth].IsFlaged()) {
					if (flagAmount == 0) {} // if you have no flags left, it does nothing
					else {
						PlayField[offsetHeight][offsetWidth].SetFlaged();
						flagAmount--;
					}
				}
				else {
					PlayField[offsetHeight][offsetWidth].SetNotFlaged();
					flagAmount++;
				}
				break;
			}
					  // For russian symbols
			case 'à': {
				// If the tile is not flaged, it puts a flag in it, if it is, it removes it
				if (!PlayField[offsetHeight][offsetWidth].IsFlaged()) {
					if (flagAmount == 0) {} // if you have no flags left, it does nothing
					else {
						PlayField[offsetHeight][offsetWidth].SetFlaged();
						flagAmount--;
					}
				}
				else {
					PlayField[offsetHeight][offsetWidth].SetNotFlaged();
					flagAmount++;
				}
				break;
			}
					  // For CAPS lock russian symbols
			case 'À': {
				// If the tile is not flaged, it puts a flag in it, if it is, it removes it
				if (!PlayField[offsetHeight][offsetWidth].IsFlaged()) {
					if (flagAmount == 0) {} // if you have no flags left, it does nothing
					else {
						PlayField[offsetHeight][offsetWidth].SetFlaged();
						flagAmount--;
					}
				}
				else {
					PlayField[offsetHeight][offsetWidth].SetNotFlaged();
					flagAmount++;
				}
				break;
			}

					  // OPENNIG THE TILE
			case ' ': {
				// If the tile is flaged, it doesn't open it and does nothing, otherwise it does
				if (PlayField[offsetHeight][offsetWidth].IsFlaged()) {}
				else {
					// Checks whether there is a bomb in the chosen tile to end the game or open the tile
					if (PlayField[offsetHeight][offsetWidth].IsBombed())
						GameLost = true; // GAME LOSING CONDITION
					else
						PlayField[offsetHeight][offsetWidth].SetOpened();
				}
				break;
			}
			}

			// If the cursor moves to the edge of the playfield, teleport it to the other side
			if (offsetHeight > (height - 1))
				offsetHeight = 0;
			if (offsetWidth > (width - 1))
				offsetWidth = 0;
			if (offsetHeight < 0)
				offsetHeight = (height - 1);
			if (offsetWidth < 0)
				offsetWidth = (width - 1);

			// Places the cursor
			PlayField[offsetHeight][offsetWidth].SetUnderCursor();
			//--------------------------------------------------------------------------------

			//---------------OPENING ALL TILES AROUND THE TILE WITH 0 BOMBS AROUND------------
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					// Checks if the tile is open and has 0 bombs around it to open all tiles around
					if (PlayField[i][j].IsOpened() && (PlayField[i][j].BombsAround() == 0)) {
						// Special cases for tiles what are on the edges or last lines
						// so the don't use a tile that doen't exist
						if (i == 0) { // first vertical line, can't do left
							if (j == 0) {// 0-0 tile
								PlayField[i + 1][j].SetOpened();
								PlayField[i + 1][j + 1].SetOpened();
								PlayField[i][j + 1].SetOpened();
							}
							else {
								if (j == (width - 1)) { // 0-last tile
									PlayField[i + 1][j].SetOpened();
									PlayField[i + 1][j - 1].SetOpened();
									PlayField[i][j - 1].SetOpened();
								}
								else { // only first vertical line
									PlayField[i + 1][j].SetOpened();
									PlayField[i + 1][j + 1].SetOpened();
									PlayField[i + 1][j - 1].SetOpened();
									PlayField[i][j - 1].SetOpened();
									PlayField[i][j + 1].SetOpened();
								}
							}
						}
						else {
							if (i == (height - 1)) { // last vertical line, can't do right
								if (j == 0) { // last-0 tile
									PlayField[i - 1][j].SetOpened();
									PlayField[i - 1][j + 1].SetOpened();
									PlayField[i][j + 1].SetOpened();
								}
								else {
									if (j == (width - 1)) { // last-last tile
										PlayField[i - 1][j].SetOpened();
										PlayField[i - 1][j - 1].SetOpened();
										PlayField[i][j - 1].SetOpened();
									}
									else { // only last vertical line
										PlayField[i - 1][j].SetOpened();
										PlayField[i - 1][j + 1].SetOpened();
										PlayField[i - 1][j - 1].SetOpened();
										PlayField[i][j - 1].SetOpened();
										PlayField[i][j + 1].SetOpened();
									}
								}
							}
							else {
								if (j == 0) { // only first horizontal line, can't do up
									PlayField[i + 1][j].SetOpened();
									PlayField[i + 1][j + 1].SetOpened();
									PlayField[i - 1][j + 1].SetOpened();
									PlayField[i - 1][j].SetOpened();
									PlayField[i][j + 1].SetOpened();
								}
								else {
									if (j == (width - 1)) { // only last horizontal line, can't do down
										PlayField[i + 1][j].SetOpened();
										PlayField[i + 1][j - 1].SetOpened();
										PlayField[i - 1][j - 1].SetOpened();
										PlayField[i - 1][j].SetOpened();
										PlayField[i][j - 1].SetOpened();
									}
									else { // no restrictions
										PlayField[i + 1][j].SetOpened();
										PlayField[i - 1][j].SetOpened();
										PlayField[i][j + 1].SetOpened();
										PlayField[i][j - 1].SetOpened();
										PlayField[i + 1][j + 1].SetOpened();
										PlayField[i - 1][j + 1].SetOpened();
										PlayField[i + 1][j - 1].SetOpened();
										PlayField[i - 1][j - 1].SetOpened();
									}
								}
							}
						}
					}
				}
			}
			//--------------------------------------------------------------------

			//------------------GAME WINNING CONDITION-----------------------
			int openedTilesWithoutBomb = 0; // a counter of how many non-bombed tiles are opened

											// Counts how many non-bombed tiles are opened
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if ((!PlayField[i][j].IsBombed() && PlayField[i][j].IsOpened()))
						openedTilesWithoutBomb++;
				}
			}

			// If counter's value is the same as possible amount of non-bombed tiles, you win 
			if (openedTilesWithoutBomb == ((height * width) - bombsAmount)) {
				GameWon = true;
			}
			//------------------------------------------------------------------

			system("cls"); // clears the playfield to show changes

		} while (!GameLost && !GameWon);
		//--------------------------------------------------------------------

		//------------------ENDING SCREEN------------------------------------------------
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); // beginning color for everything is black background, white symbols

																  // Prints ending message depending on whether you lost or won
		if (GameLost)
			std::cout << "You have lost :(" << std::endl;
		else {
			if (GameWon)
				std::cout << "You have won! :)" << std::endl;
		}

		// Shows the whole playfield
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (PlayField[i][j].IsFlaged()) {
					if (PlayField[i][j].IsBombed())
						// Prints the check mark if you successfully placed a flag
						PrintTile('V', Yellow);
					else
						// Prints a cross if you unsuccessfully placed a flag
						PrintTile('X', DarkRed);
				}
				else {
					// Prints the bomb
					if (PlayField[i][j].IsBombed()) {
						PrintTile('B', Gray);
					}
					else {
						// Prints every tile
						// Every number of bombs has a different color
						switch (PlayField[i][j].BombsAround()) {
						case 0: { // 0 - white
							PrintTile('0', LightGray);
							break;
						}
						case 1: { // 1 - blue
							PrintTile('1', DarkCyan);
							break;
						}
						case 2: { // 2 - green
							PrintTile('2', Green);
							break;
						}
						case 3: { // 3 - red
							PrintTile('3', Red);
							break;
						}
						case 4: { // 4 - dark blue
							PrintTile('4', Blue);
							break;
						}
						case 5: { // 5 - brown
							PrintTile('5', Brown);
							break;
						}
						case 6: { // 6 - cyan
							PrintTile('6', Cyan);
							break;
						}
						case 7: { // 7 - black
							PrintTile('7', Gray);
							break;
						}
						case 8: { // 8 - grey
							PrintTile('8', LightGray);
							break;
						}
						}
					}
				}
			}
			std::cout << std::endl;
		}

		// Asks you whether you want to play another game or not
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); // beginning color for everything is black background, white symbols
		std::cout << "Wanna play another?" << std::endl << "(y/n):";
		std::cin >> repeatChoice;

		//---------------------------------------------------------------------------------------------------------

		// Places the cursor back to [0][0] position 
		offsetHeight = 0;
		offsetWidth = 0;

		// Deletes the playfield
		delete[] PlayField;
	} while (repeatChoice == 'y');

	// Last message before leaving
	std::cout << "Thanks for playing!";
	_getch();
	_getch();

	return 0;
}