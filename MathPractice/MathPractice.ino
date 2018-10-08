/*
 Name:		MathPractice.ino
 Created:	8/31/2018 12:05:08 AM
 Author:	boardkeystown
*/

/*
To do:
-Clean up code
-Optimize
-add a challenge mode that mixes different operations together 
*/

//This is the Height For Numbers
#define Num_Height 10
#define Num_Width 7

//App mode
#define MODE_MENU 0
#define MODE_SETUP 1
#define MODE_PLAY 2
#define MODE_PAUSE 3
#define MODE_CORRECT_SPLASH_SCREEN 4
#define MODE_INCORRECT_SPLASH_SCREEN 5
#define MODE_END_SPLASH_SCREEN 6


//MENU Options
#define ADDITION 0
#define SUBTRACTION 1
#define MULTIPLICATION 2
#define DIVISION 3

//Display Menu Options
#define DISP_MENU_EXIT -1
#define DISP_MENU_DIFF_SET 0
#define DISP_MENU_RAN_SET 1
#define DISP_MENU_NUM_SET 2
#define DISP_MENU_START 3

//Pause Menu Options
#define PAUSE_MENU_NO 0
#define PAUSE_MENU_YES 1


//Button States  

//pressed
#define _NO_BUTTON   0
#define _A			 1
#define A_AND_LEFT   2
#define A_AND_UP	 3
#define A_AND_RIGHT  4
#define A_AND_DOWN   5
#define _B			 6
#define B_AND_LEFT   7
#define B_AND_UP	 8
#define B_AND_RIGHT  9
#define B_AND_DOWN   10
#define _UP			 11
#define _LEFT		 12
#define _RIGHT		 13
#define _DOWN		 14

//released  
#define _A_RELEASE			 15
#define A_AND_LEFT_RELEASE   16
#define A_AND_UP_RELEASE	 17
#define A_AND_RIGHT_RELEASE  18
#define A_AND_DOWN_RELEASE   19
#define _B_RELEASE			 20
#define B_AND_LEFT_RELEASE   21
#define B_AND_UP_RELEASE	 22
#define B_AND_RIGHT_RELEASE  23
#define B_AND_DOWN_RELEASE   24
#define _UP_RELEASE			 25
#define _LEFT_RELEASE		 26
#define _RIGHT_RELEASE		 27
#define _DOWN_RELEASE		 28

//Max number of digits that can be entered
#define MAX_DIGIT_COUNT 5


//Timer values for difficulty
#define EASY 60
#define MEDIUM 30
#define HARD 10

#include <Arduboy2.h>

//NUMBERS INVERT 0-9 Invert
const unsigned char zeroInvert[] PROGMEM = { 0xff, 0x1, 0x79, 0xfd, 0x79, 0x1, 0xff, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, };
const unsigned char oneInvert[] PROGMEM = { 0xff, 0xff, 0xf7, 0x3, 0x1, 0xff, 0xff, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, };
const unsigned char twoInvert[] PROGMEM = { 0xff, 0x73, 0x39, 0x19, 0x81, 0xc3, 0xff, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, };
const unsigned char threeInvert[] PROGMEM = { 0xff, 0x77, 0x73, 0xd9, 0x1, 0x3, 0xff, 0x3, 0x3, 0x2, 0x2, 0x2, 0x3, 0x3, };
const unsigned char fourInvert[] PROGMEM = { 0xff, 0x87, 0xb3, 0x39, 0x1, 0xdf, 0xff, 0x3, 0x3, 0x3, 0x2, 0x2, 0x3, 0x3, };
const unsigned char fiveInvert[] PROGMEM = { 0xff, 0x61, 0x61, 0xe9, 0x9, 0x9, 0xff, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2, 0x3, };
const unsigned char sixInvert[] PROGMEM = { 0xff, 0x1, 0x1, 0xd9, 0xd9, 0x19, 0xff, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, };
const unsigned char sevenInvert[] PROGMEM = { 0xff, 0xfd, 0xfd, 0xfd, 0x1, 0x1, 0xff, 0x3, 0x3, 0x3, 0x3, 0x2, 0x2, 0x3, };
const unsigned char eightInvert[] PROGMEM = { 0xff, 0x1, 0xcd, 0xcd, 0xcd, 0x1, 0xff, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, };
const unsigned char nineInvert[] PROGMEM = { 0xff, 0xc1, 0xc1, 0xdd, 0x1d, 0x1, 0xff, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, };


//NUMBERS 0-9
const unsigned char zero[] PROGMEM = { 0x00, 0xfe, 0x86, 0x2, 0x86, 0xfe, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, };
const unsigned char one[] PROGMEM = { 0x00, 0x00, 0x8, 0xfc, 0xfe, 0x00, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, };
const unsigned char two[] PROGMEM = { 0x00, 0x8c, 0xc6, 0xe6, 0x7e, 0x3c, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, };
const unsigned char three[] PROGMEM = { 0x00, 0x88, 0x8c, 0x26, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x1, 0x1, 0x1, 0x00, 0x00, };
const unsigned char four[] PROGMEM = { 0x00, 0x78, 0x4c, 0xc6, 0xfe, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1, 0x1, 0x00, 0x00, };
const unsigned char five[] PROGMEM = { 0x00, 0x9e, 0x9e, 0x16, 0xf6, 0xf6, 0x00, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x00, };
const unsigned char six[] PROGMEM = { 0x00, 0xfe, 0xfe, 0x26, 0x26, 0xe6, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, };
const unsigned char seven[] PROGMEM = { 0x00, 0x2, 0x2, 0x2, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x1, 0x00, };
const unsigned char eight[] PROGMEM = { 0x00, 0xfe, 0x32, 0x32, 0x32, 0xfe, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, };
const unsigned char nine[] PROGMEM = { 0x00, 0x3e, 0x3e, 0x22, 0xe2, 0xfe, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, };


//Math symbols 
const unsigned char plus[] PROGMEM = { 0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char minus[] PROGMEM = { 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char divide[] PROGMEM = { 0x00, 0x30, 0x30, 0xb4, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char multiply[] PROGMEM = { 0x00, 0xdc, 0xf8, 0x70, 0xf8, 0xdc, 0x00, 0x00, 0x1, 0x00, 0x00, 0x00, 0x1, 0x00, };
const unsigned char equal[] PROGMEM = { 0x00, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };


//Symbols
const unsigned char question_mark[] PROGMEM = { 0x00, 0xe, 0x6, 0x62, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x1, 0x1, 0x00, 0x00, };
const unsigned char vertical_bar[] PROGMEM = { 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3, 0x3, 0x3, 0x00, 0x00, };
const unsigned char horizontal_bar[] PROGMEM = { 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char less_than[] PROGMEM = { 0x00, 0x30, 0x78, 0xcc, 0x86, 0x2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x1, 0x00, };
const unsigned char greater_then[] PROGMEM = { 0x00, 0x2, 0x86, 0xcc, 0x78, 0x30, 0x00, 0x00, 0x1, 0x1, 0x00, 0x00, 0x00, 0x00, };
const unsigned char cursor[] PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, };
const unsigned char left_arrow[] PROGMEM = { 0x10, 0x38, 0x7c, 0xfe, 0xba, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char right_arrow[] PROGMEM = { 0x38, 0x38, 0xba, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char down_arrow[] PROGMEM = { 0x60, 0xc0, 0xff, 0xff, 0xff, 0xc0, 0x60, 0x00, 0x00, 0x1, 0x3, 0x1, 0x00, 0x00, };
const unsigned char up_arrow[] PROGMEM = { 0x18, 0xc, 0xfe, 0xff, 0xfe, 0xc, 0x18, 0x00, 0x00, 0x3, 0x3, 0x3, 0x00, 0x00, };
const unsigned char left_brace[] PROGMEM = { 0xff, 0xff, 0x1, 0x1, 0x00, 0x00, 0x00, 0x3, 0x3, 0x2, 0x2, 0x00, 0x00, 0x00, };
const unsigned char right_brace[] PROGMEM = { 0x00, 0x00, 0x00, 0x1, 0x1, 0xff, 0xff, 0x00, 0x00, 0x00, 0x2, 0x2, 0x3, 0x3, };
const unsigned char big_check_mark[] PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0xf, 0x7, 0x3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0xf, 0x7, 0x3, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x78, 0xfc, 0xfe, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0xf, 0x7, 0x3, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0xf, 0x7, 0x3, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x3, 0x7, 0x7, 0x7, 0x7, 0x3, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char big_x[] PROGMEM = { 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7c, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3f, 0x1f, 0xf, 0x7, 0x3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x83, 0xc7, 0xef, 0xff, 0xfe, 0x7c, 0xfe, 0xff, 0xef, 0xc7, 0x83, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0xf, 0x7, 0x3, 0x1, 0x00, 0x00, 0x00, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3e, 0x7c, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x1, 0x1, 0x1, 0x1, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x1, 0x1, 0x1, 0x1, };

//Outlines 
const unsigned char dpad[] PROGMEM = { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x78, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7, 0x4, 0x4, 0x4, 0x4, 0x4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x4, 0x4, 0x4, 0x4, 0x4, 0x7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
const unsigned char button[] PROGMEM = { 0xe0, 0x18, 0x4, 0x2, 0x2, 0x1, 0x1, 0x1, 0x1, 0x1, 0x2, 0x2, 0x4, 0x18, 0xe0, 0x7, 0x18, 0x20, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0x18, 0x7, };


//Arrays operations 
const unsigned char *mathOperationSymbols[] = { plus, minus, multiply, divide };
const unsigned char *numsInvert[] = { zeroInvert, oneInvert, twoInvert, threeInvert, fourInvert, fiveInvert, sixInvert, sevenInvert, eightInvert, nineInvert, };
const unsigned char *nums[] = { zero, one, two, three, four, five, six, seven, eight, nine, };
const unsigned char *math[]{ plus,minus, divide, multiply, equal, };


Arduboy2 arduboy;

//Current app state 
int mode = MODE_MENU;

//The button that is pressed used in update
int currentButton = _NO_BUTTON; 

//Current menu state
int menuSelect = 0;

//Current position of the cursor 
int cursorPosition = 0;

//Level of difficulty
int difficulty = 0;

//Used to track number of seconds that go by set with difficulty respectively
unsigned long timer = 0, save_timer;

//timePassed
unsigned long t = 0;

//full second used in func_timer
unsigned long fullSec = 1000;

//single second 
unsigned long sec = 1;

//duration 
unsigned long duration = EASY;

//Whether game is random numbers 
int doRandomNumbers = 0;  

//Is D-Pad held down
bool isDpadSet = false;

//Don't press A or B again
bool isAorBheldDown = false;

//Holds the current operation Mode +,-,*,
int operationMode = 0;

//Vales to hold numbers for play state and used in displaySetyup() "i op [(j=e)-9...e*10]"
int i = 1;  //Number used to do arithmetic 
int j = 1;  //Start of numbers to do arithmetic on
int e = 10; //End of numbers to do arithmetic on

//The arrow used in displaySetup 
int arrowOrientation = _NO_BUTTON;

//Flag if the Answer is negative used when checking ifcorrect()
bool isAnswernegative = false;

//Flag if Answer is set or not
bool isAnswerset = false;

//The answer that is used in MODE_PLAY and compared to solution 
long int answer = 0;

//The solution that is used in MODE_PLAY and compared to answer
long int solution = 0;

//Value for blink control of the cursor 
int blinkValue = 0;

//digit  track
int digitTrack = 0;

//splash screen counter
int splashScreencounter = 0;

//incorrect track
int incorrectTrack = 0;

//correct track
int correctTrack = 0;

void render();

//displays menu
void displayMenu();

//game setup display 
void displaySetup();

//Display arrow based to screen 
void arrowDisplay(int arrowOri, int xPos, int yPos);

//game
void displayPlay();

//big check mark on screen that indicates if you got answer correct
void correctSplashscreen();

//big "x"(s) on screen that indicates you got answer incorrect
void incorrectSplashscreen();

//end screen that tallies how many you got right and prints a message to screen
void endSplashScreen();

//returns true run out of time and displays incorrect screen 
bool runOutofTime();

//used to keep track of time passed 
void func_timer(unsigned long *timer, unsigned long duration);

//pause menu for game
void displayPause();

//draws outlines to displayPlay() 
void displayOutline();

//display current math question
void displayMathQuestion();

void displayNumber(int num);
void displayNumber(long int num);

void displayInput();

void cursorBlink(unsigned char *sym, int xPos, int yPos, int rateOfBlink);

void backspaceInput();

void getInput(int val);

bool isAnswercorrect();

//displays numbers over outline in displayPlay()
void displayNumbersInPlay();

void update();

//Sets the operation
void setOperationMode();

//adjust menu selections based on bounds
void menuSelectAdjust(int *val, int move, int min, int max);

//Resets values for return to menu
void valueReset();
 
void processInput();

//returns code for buttons/combination buttons pressed 
int getButtonPress();

void setup() {
	arduboy.begin();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(60);
}

void loop() {
	arduboy.clear();
	if (!(arduboy.nextFrame())) { return; }
	arduboy.pollButtons();

	func_timer(&timer, duration);
	render();
	update();
	processInput();

	arduboy.display();
}

void render() {

	switch (mode)
	{
	case MODE_MENU:
		displayMenu();
		break;
	case MODE_SETUP:
		displaySetup();
		break;
	case MODE_PLAY:
		displayPlay();
	    arduboy.setCursor(0, 0);
        arduboy.print(timer);
		break;
	case MODE_PAUSE:
		displayPause();
		break;
	case MODE_CORRECT_SPLASH_SCREEN:
		correctSplashscreen();
		break;
	case MODE_INCORRECT_SPLASH_SCREEN:
		incorrectSplashscreen();
		break;
	case MODE_END_SPLASH_SCREEN:
		endSplashScreen();
		break;
	default:
		break;
	}
	return;
}

void displayMenu() {
	arduboy.setCursor(20,0);
	arduboy.print(F("_Math Practice_"));
	if (menuSelect == ADDITION) { 
		arduboy.drawBitmap((int)5, (int)8, right_arrow, Num_Width, Num_Height, WHITE);
	}
	arduboy.setCursor(15, 10);
	arduboy.print(F("Addition"));
	if (menuSelect == SUBTRACTION) {
		arduboy.drawBitmap((int)5, (int)18, right_arrow, Num_Width, Num_Height, WHITE);
	}
	arduboy.setCursor(15, arduboy.getCursorY() + 10);
	arduboy.print(F("Subtraction"));
	if (menuSelect == MULTIPLICATION) {
		arduboy.drawBitmap((int)5, (int)28, right_arrow, Num_Width, Num_Height, WHITE);
	}
	arduboy.setCursor(15, arduboy.getCursorY() + 10);
	arduboy.print(F("Multiplication"));
	if (menuSelect == DIVISION) {
		arduboy.drawBitmap((int)5, (int)38, right_arrow, Num_Width, Num_Height, WHITE);
	}
	arduboy.setCursor(15, arduboy.getCursorY() + 10);
	arduboy.print(F("Division"));
	return;
} 

void displaySetup() {
	
	//Back to main menu
	if (cursorPosition == DISP_MENU_EXIT) {
		valueReset();
		return;
	}

	//Difficulty Set
	if (cursorPosition == DISP_MENU_DIFF_SET) {
		arduboy.drawBitmap((int)0, (int)0, greater_then, Num_Width, Num_Height, WHITE);
	}
	arduboy.setCursor(8, 1);
	arduboy.print(F("Difficulty: E  M  H"));
	if (difficulty == 0) { arduboy.drawBitmap((int)72, (int)0, right_arrow, Num_Width, Num_Height, WHITE); }
	else if (difficulty == 1) { arduboy.drawBitmap((int)90, (int)0, right_arrow, Num_Width, Num_Height, WHITE); }
	else if (difficulty == 2) { arduboy.drawBitmap((int)108, (int)0, right_arrow, Num_Width, Num_Height, WHITE); }

	//Random Set
	if (cursorPosition == DISP_MENU_RAN_SET) {
		arduboy.drawBitmap((int)0, (int)10, greater_then, Num_Width, Num_Height, WHITE);
	}
	arduboy.setCursor(8, 11);
	arduboy.print(F("Random: No  Yes"));
	if (doRandomNumbers == 0) { arduboy.drawBitmap((int)48, (int)10, right_arrow, Num_Width, Num_Height, WHITE); }
	else if (doRandomNumbers == 1) { arduboy.drawBitmap((int)72, (int)10, right_arrow, Num_Width, Num_Height, WHITE); }

	if (doRandomNumbers == 1) {
		//Shuffle numbers
		i = rand() % (11 - 1) + 1;
		e = (rand() % (11 - 1) + 1) * 10;
		j = e;
		j = j - 9;

		if (cursorPosition == DISP_MENU_NUM_SET) {
			//set difficulty timer 
			switch (difficulty)
			{
			case 0:
				timer = duration = EASY;
				break;
			case 1:
				timer = duration = MEDIUM;
				break;
			case 2:
				timer = duration = HARD;
				break;
			}
			mode = MODE_PLAY;
			return;
		}
	}
	else {
		if (operationMode == DIVISION || operationMode == SUBTRACTION) {
			//Flips operands to do DIVISON and SUBTRACION respectively to MUL and ADD
			arrowDisplay(arrowOrientation, (int)4, (int)27);
			//Number Set
			if (cursorPosition == DISP_MENU_NUM_SET) {
				arduboy.drawBitmap((int)12, (int)27, greater_then, Num_Width, Num_Height, WHITE);
			}
			// [j ... e ] op i
			//[
			arduboy.drawBitmap((int)21, (int)26, left_brace, Num_Width, Num_Height, WHITE);
			//j
			arduboy.setCursor(28, 28);
			arduboy.print(j);
			arduboy.setCursor(48, 28);
			arduboy.print(F("..."));
			//e
			arduboy.setCursor(65, 28);
			arduboy.print(e);
			//]
			arduboy.drawBitmap((int)85, (int)26, right_brace, Num_Width, Num_Height, WHITE);

			//op 
			arduboy.drawBitmap((int)98, (int)26, mathOperationSymbols[operationMode], Num_Width, Num_Height, WHITE);
			//i
			arduboy.setCursor(111, 28);
			arduboy.print(i);

		}
		else {

			arrowDisplay(arrowOrientation, (int)4, (int)27);
			//Number Set
			if (cursorPosition == DISP_MENU_NUM_SET) {
				arduboy.drawBitmap((int)12, (int)27, greater_then, Num_Width, Num_Height, WHITE);
			}
			//i op [j ... e ]
			//i
			arduboy.setCursor(21, 28);
			arduboy.print(i);
			arduboy.drawBitmap((int)38, (int)26, mathOperationSymbols[operationMode], Num_Width, Num_Height, WHITE);
			arduboy.drawBitmap((int)48, (int)26, left_brace, Num_Width, Num_Height, WHITE);
			//j
			arduboy.setCursor(55, 28);
			arduboy.print(j);
			arduboy.setCursor(75, 28);
			arduboy.print(F("..."));
			//e
			arduboy.setCursor(95, 28);
			arduboy.print(e);
			arduboy.drawBitmap((int)115, (int)26, right_brace, Num_Width, Num_Height, WHITE);
		
		}
	}

	//Directions Message 
	arduboy.setCursor(0, 48);
	arduboy.print(F("DPad:Change Value"));
	arduboy.setCursor(0, 57);
	arduboy.print(F("A:Select B:Back"));

	//Start Game
	if (cursorPosition == DISP_MENU_START) {
		//set difficulty timer 
		switch (difficulty)
		{
		case 0:
			timer = duration = EASY;
			break;
		case 1:
			timer = duration = MEDIUM;
			break;
		case 2:
			timer = duration = HARD;
			break;
		}
		mode = MODE_PLAY;
		return;
	}
}

void arrowDisplay(int arrowOri, int xPos, int yPos) {
	if (arrowOri == _UP) {
		arduboy.drawBitmap(xPos, yPos, up_arrow, Num_Width, Num_Height, WHITE);
	}
	else if (arrowOri == _DOWN) {
		arduboy.drawBitmap(xPos, yPos, down_arrow, Num_Width, Num_Height, WHITE);
	}
	else if (arrowOri == _LEFT) {
		arduboy.drawBitmap(xPos, yPos, left_arrow, Num_Width, Num_Height, WHITE);
	}
	else if (arrowOri == _RIGHT) {
		arduboy.drawBitmap(xPos, yPos, right_arrow, Num_Width, Num_Height, WHITE);
	}
}

void displayPlay() {
	cursorPosition = 0; //Sets cursorPosition to zero for pause menu
	displayOutline();
	displayNumbersInPlay();
	//solution = -1; // solution must never = answer at start of this

	
	if (operationMode == ADDITION) {
		solution = i + j;
	} 
	else if (operationMode == SUBTRACTION) {
		solution = j - i;
	}
	else if (operationMode == MULTIPLICATION) {
		solution = i * j;
	}
	else if (operationMode == DIVISION) {
		solution = j / i;

	}


	if (j < e) {
	
		if (incorrectTrack == 3) {
			mode = MODE_END_SPLASH_SCREEN;
			return;
		}
		if (runOutofTime() || isAnswercorrect()) {
			j++;

			//Clear ans
			isAnswernegative = false;
			isAnswerset = false;
			answer = 0;
			digitTrack = 0;

		} 
		displayMathQuestion();
		displayInput();
	}
	else {
		mode = MODE_END_SPLASH_SCREEN;
		return;
	}

	return;
}

void correctSplashscreen() {
	arduboy.setCursor(40, 0);
	arduboy.print(F("Correct!"));
	arduboy.drawBitmap(40,20,big_check_mark, 50, 35);
	
	//LED blink on
	arduboy.setRGBled(0, 80, 0);

	if (splashScreencounter++ > 35) {
		splashScreencounter = 0;
		arduboy.setRGBled(0, 0, 0);
		mode = MODE_PLAY;
	}
}

void incorrectSplashscreen() {
	//incorrectTrack must be reset after last call of incorrectSplashScreen
	arduboy.setCursor(30, 0);

	//LED blink on
	arduboy.setRGBled(80, 0, 0);

	switch (incorrectTrack){
		case 0:
			arduboy.print(F("Out of time!"));
			arduboy.drawBitmap(55, 20, big_x, 27, 25);
			if (splashScreencounter++ > 35) {
				++incorrectTrack;
				splashScreencounter = 0;
				arduboy.setRGBled(0, 0, 0);
				mode = MODE_PLAY;
			}
			break;
		case 1:
			arduboy.print(F("Out of time!"));
			arduboy.drawBitmap(40, 20, big_x, 27, 25);
			arduboy.drawBitmap(69, 20, big_x, 27, 25);
			if (splashScreencounter++ > 35) {
				++incorrectTrack;
				splashScreencounter = 0;
				arduboy.setRGBled(0, 0, 0);
				mode = MODE_PLAY;
			}
			break;
		case 2:
			arduboy.print(F("Game over..."));
			arduboy.setCursor(30, 10);
			arduboy.print(F("Keep practicing."));
			arduboy.drawBitmap(30, 20, big_x, 27, 25);
			arduboy.drawBitmap(59, 20, big_x, 27, 25);
			arduboy.drawBitmap(86, 20, big_x, 27, 25);
			if (splashScreencounter++ > 60) {
				++incorrectTrack;
				splashScreencounter = 0;
				arduboy.setRGBled(0, 0, 0);
				mode = MODE_PLAY;
			}
			break;
		default:
			break;
	}
	

}

void endSplashScreen() {
	char buffer[55];
	if (correctTrack == 9) {
		arduboy.setCursor(0, 10);
		sprintf(buffer, "Awesome you answered\n\n9 out of 9\n\ncorrect!");
		arduboy.print(buffer);
	} else if (correctTrack == 0) {
		arduboy.setCursor(0, 0);
		sprintf(buffer, "You answered\n\n0 out of 10\n\ncorrect...\n\nKeep practicing");
		arduboy.print(buffer);
	}
	else if (correctTrack >= 6) {
		arduboy.setCursor(0, 10);
		sprintf(buffer, "Good job you got\n\n%d out of 10\n\ncorrect.", correctTrack);
		arduboy.print(buffer);
	}
	else if (correctTrack <= 5) {
		arduboy.setCursor(0, 10);
		sprintf(buffer, "You got %d out of 10\n\ncorrect...\n\nKeep practicing", correctTrack);
		arduboy.print(buffer);
	}

	if (splashScreencounter++ > 80) {
		splashScreencounter = 0;
		valueReset();
	}
}

bool runOutofTime() {
	if (timer) { return false; }
	else { 
		mode = MODE_INCORRECT_SPLASH_SCREEN;
		return true; 
	}
}

void func_timer(unsigned long *timer, unsigned long duration) {
	//resets timer
	if (*timer <= 0) {
		*timer = duration;
	}
	
	//keeps counts down timer 
	if (millis() >= t) {
		arduboy.setCursor(15, 0);
		
		t = t + fullSec;
		*timer = *timer - sec;
	}
}

void displayNumbersInPlay() {
	arduboy.drawBitmap((int)49, (int)51, nums[0], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)6, (int)46, nums[1], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)12, (int)39, nums[2], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)18, (int)46, nums[3], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)12, (int)53, nums[4], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)69, (int)51, nums[5], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)104, (int)46, nums[6], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)110, (int)39, nums[7], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)116, (int)46, nums[8], Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)110, (int)53, nums[9], Num_Width, Num_Height, WHITE);
}

void displayOutline() {
	int x, y, temp;
	x = 5;
	y = 2;
	for (int i = 0; i < 17; i++) {
		arduboy.drawBitmap(x, y, horizontal_bar, Num_Width, Num_Height, WHITE);
		x = x + 7;
	}
	x = x - 5;
	y = 9;
	for (int i = 0; i < 2; i++) {
		arduboy.drawBitmap(x, y, vertical_bar, Num_Width, Num_Height, WHITE);
		y = y + 8;
	}
	x = 3;
	y = 9;
	for (int i = 0; i < 2; i++) {
		arduboy.drawBitmap(x, y, vertical_bar, Num_Width, Num_Height, WHITE);
		y = y + 8;
	}
	x = 5;
	y = y - 2;
	for (int i = 0; i < 17; i++) {
		arduboy.drawBitmap(x, y, horizontal_bar, Num_Width, Num_Height, WHITE);
		x = x + 7;
	}
	x = 26;
	y = y + 7;
	temp = y;
	for (int i = 0; i < 2; i++) {
		arduboy.drawBitmap(x, y, vertical_bar, Num_Width, Num_Height, WHITE);
		y = y + 6;
	}
	y = temp;
	x = 96;
	for (int i = 0; i < 2; i++) {
		arduboy.drawBitmap(x, y, vertical_bar, Num_Width, Num_Height, WHITE);
		y = y + 6;
	}
	y = y - 3;
	x = 29;
	for (int i = 0; i < 10; i++) {
		arduboy.drawBitmap(x, y, horizontal_bar, Num_Width, Num_Height, WHITE);
		x = x + 7;
	}
	//LEFT dpad
	arduboy.drawBitmap(5, 38, dpad, 21, 26, WHITE);

	//Right dpad
	arduboy.drawBitmap(103, 38, dpad, 21, 26, WHITE);

	//Button A
	arduboy.drawBitmap(45, 48, button, 15, 16, WHITE);

	//Button B
	arduboy.drawBitmap(65, 48, button, 15, 16, WHITE);
	return;
}

void displayMathQuestion() {
	arduboy.setCursor(30, 13);
	if (operationMode == SUBTRACTION || operationMode == DIVISION) {
		// j op i
		displayNumber(j);
		arduboy.drawBitmap((int)40, (int)13, mathOperationSymbols[operationMode], Num_Width, Num_Height, WHITE);
		arduboy.setCursor(60, 13);
		displayNumber(i);
		arduboy.drawBitmap((int)70, (int)13, equal, Num_Width, Num_Height, WHITE);
		arduboy.drawBitmap((int)80, (int)13, question_mark, Num_Width, Num_Height, WHITE);
		arduboy.setCursor(101, 13);
	}
	else {
	// i op j
	displayNumber(i);
	arduboy.drawBitmap((int)40, (int)13, mathOperationSymbols[operationMode], Num_Width, Num_Height, WHITE);
	arduboy.setCursor(60, 13);
	displayNumber(j);
	arduboy.drawBitmap((int)70, (int)13, equal, Num_Width, Num_Height, WHITE);
	arduboy.drawBitmap((int)80, (int)13, question_mark, Num_Width, Num_Height, WHITE);
	arduboy.setCursor(101, 13);
	//displayNumber(37); // should be set to solution if timer runs out then delay(50) 
	}
}

void displayNumber(int num) {
	//need to set CursourPos before use
	//Maybe come up with a case for negative ???
	int _num = num % 10;
	num = num / 10;
	if (num == 0) {
		arduboy.drawBitmap(arduboy.getCursorX(), arduboy.getCursorY(), nums[_num], Num_Width, Num_Height, WHITE);
		arduboy.setCursor(arduboy.getCursorX() - Num_Width, arduboy.getCursorY());
		return;
	} 
	arduboy.drawBitmap(arduboy.getCursorX(), arduboy.getCursorY(), nums[_num], Num_Width, Num_Height, WHITE);
	arduboy.setCursor(arduboy.getCursorX() - Num_Width, arduboy.getCursorY());
	displayNumber(num);
}

void displayNumber(long int num) {
	long int _num = num % 10;
	num = num / 10;
	if (num == 0) {
		arduboy.drawBitmap(arduboy.getCursorX(), arduboy.getCursorY(), nums[_num], Num_Width, Num_Height, WHITE);
		arduboy.setCursor(arduboy.getCursorX() - Num_Width, arduboy.getCursorY());
		return;
	}
	arduboy.drawBitmap(arduboy.getCursorX(), arduboy.getCursorY(), nums[_num], Num_Width, Num_Height, WHITE);
	arduboy.setCursor(arduboy.getCursorX() - Num_Width, arduboy.getCursorY());
	displayNumber(num);
}

void displayInput() {
	if (isAnswernegative) { arduboy.drawBitmap(40, 30, minus, Num_Width, Num_Height, WHITE); } //Display negative 

	if (answer == 0) {
		arduboy.setCursor(47 + (digitTrack*Num_Width), 30);
		if (isAnswerset) { 
			displayNumber(answer); 
			cursorBlink(cursor, 47 + ((digitTrack + 1)*Num_Width), 30, 50);

		}
		else { cursorBlink(cursor, 40 + ((digitTrack + 1)*Num_Width), 30, 50); }
	}
	else {
		arduboy.setCursor(40 + (digitTrack*Num_Width), 30);
		displayNumber(answer);
		if (digitTrack < MAX_DIGIT_COUNT) {
			cursorBlink(cursor, 40 + ((digitTrack + 1)*Num_Width), 30, 50);
		}
	}
}

void cursorBlink(unsigned char *sym, int xPos, int yPos, int rateOfBlink) {
	menuSelectAdjust(&blinkValue, 1, 0, rateOfBlink);
	if (blinkValue < (rateOfBlink/2)) {
		arduboy.drawBitmap(xPos, yPos, sym, Num_Width, Num_Height, WHITE);
	}
}

void backspaceInput() {
	if (digitTrack > 0) {
		answer = answer / 10;
		digitTrack--;
	}
}

void getInput(int val) {
	//Already set to 0
	if (val == 0 && digitTrack == 0) {
		return;
	}
	else if (digitTrack < MAX_DIGIT_COUNT) {
		answer = (answer * 10) + val;
		digitTrack++;
	}
}

bool isAnswercorrect() {
	if (isAnswerset) {
		if (isAnswernegative)
		{
			if (answer*(-1) == solution) {
				//resets timer
				switch (difficulty)
				{
				case 0:
					timer = EASY;
					break;
				case 1:
					timer = MEDIUM;
					break;
				case 2:
					timer = HARD;
					break;
				}
				++correctTrack;
				mode = MODE_CORRECT_SPLASH_SCREEN;
				return true;
			}
		}
		else if (answer == solution)
		{
			//resets timer
			switch (difficulty)
			{
			case 0:
				timer = EASY;
				break;
			case 1:
				timer = MEDIUM;
				break;
			case 2:
				timer = HARD;
				break;
			}
			++correctTrack;
			mode = MODE_CORRECT_SPLASH_SCREEN;
			return true;
		}
	}
	return false; 
}   

void displayPause() {
	arduboy.setCursor(36, 5);
	arduboy.print(F("_ PAUSE _"));
	arduboy.setCursor(20, 18);
	arduboy.print(F("Return To Start?"));
	if (cursorPosition == PAUSE_MENU_NO) { arduboy.drawBitmap((int)30, (int)32, greater_then, Num_Width, Num_Height, WHITE); }
	arduboy.setCursor(39, 33);
	arduboy.print(F("No"));
	if (cursorPosition == PAUSE_MENU_YES) { arduboy.drawBitmap((int)65, (int)32, greater_then, Num_Width, Num_Height, WHITE); }
	arduboy.setCursor(73, 33);
	arduboy.print(F("Yes"));
}

void update() {
	switch (currentButton)
	{
//Button pressed down
	case A_AND_LEFT:
		
		if (mode == MODE_PLAY) { 
			arduboy.drawBitmap((int)6, (int)46, nums[1], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)6, (int)46, numsInvert[1], Num_Width, Num_Height, WHITE); 
		}
		break;
	case A_AND_UP:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)12, (int)39, nums[2], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)12, (int)39, numsInvert[2], Num_Width, Num_Height, WHITE);
		}
		
		break;
	case A_AND_RIGHT:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)18, (int)46, nums[3], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)18, (int)46, numsInvert[3], Num_Width, Num_Height, WHITE);
		}
		
		break;
	case A_AND_DOWN:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)12, (int)53, nums[4], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)12, (int)53, numsInvert[4], Num_Width, Num_Height, WHITE);
		}
		break;
	case  B_AND_LEFT:
		if (mode == MODE_PLAY) {
		
			arduboy.drawBitmap((int)104, (int)46, nums[6], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)104, (int)46, numsInvert[6], Num_Width, Num_Height, WHITE);

		}
		break;
	case B_AND_UP:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)110, (int)39, nums[7], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)110, (int)39, numsInvert[7], Num_Width, Num_Height, WHITE);
		}
		break;
	case B_AND_RIGHT:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)116, (int)46, nums[8], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)116, (int)46, numsInvert[8], Num_Width, Num_Height, WHITE);
		}
		break;
	case B_AND_DOWN:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)110, (int)53, nums[9], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)110, (int)53, numsInvert[9], Num_Width, Num_Height, WHITE);
		}
		break;
	case _A:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)49, (int)51, nums[0], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)49, (int)51, numsInvert[0], Num_Width, Num_Height, WHITE);
		}
		break;
	case _B:
		if (mode == MODE_PLAY) {
			arduboy.drawBitmap((int)69, (int)51, nums[5], Num_Width, Num_Height, BLACK);
			arduboy.drawBitmap((int)69, (int)51, numsInvert[5], Num_Width, Num_Height, WHITE);
		}
		break;
	case _UP:
		if (mode == MODE_SETUP) {
			if (cursorPosition == DISP_MENU_NUM_SET) { 
				arrowOrientation = _UP;
				menuSelectAdjust(&i, 1, 1, 100); //Number used to do arithmetic 
				delay(60);
			}
		}


		break;
	case _LEFT:
		if (mode == MODE_SETUP) {
			if (cursorPosition == DISP_MENU_NUM_SET) { 
				arrowOrientation = _LEFT; 
				e = e - 10;
				if (e <= 0) {
					e = 100;
				}
				j = e; 
				j = j - 9;
				delay(80);
			}
		}

		break;
	case _RIGHT:
		if (mode == MODE_SETUP) {
			if (cursorPosition == DISP_MENU_NUM_SET) { 
				arrowOrientation = _RIGHT; 
				e = e + 10;
				if (e > 100) {
					e = 10;
				}
				j = e;
				j = j - 9;
				delay(80);
			}
		}
	
		

		break;
	case _DOWN:
		if (mode == MODE_SETUP) {
			if (cursorPosition == DISP_MENU_NUM_SET) { 
				arrowOrientation = _DOWN; 
				menuSelectAdjust(&i, -1, 1, 100); //Number used to do arithmetic 
				delay(60);
			}

	
		}
		break;
//Button released 
	case A_AND_LEFT_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(1); //Enter number 1
			}
		}
		break;
	case A_AND_UP_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(2); //Enter number 2
			}
		}
		break;
	case A_AND_RIGHT_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(3); //Enter number 3
			}
		}
		break;
	case A_AND_DOWN_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(4); // Enter number 4
			}
		}
		break;
	case  B_AND_LEFT_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(6); // Enter number 6
			}
		}
		break;
	case B_AND_UP_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(7); // Enter number 7
			}
		}
		break;
	case B_AND_RIGHT_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(8); // Enter number 8
			}
		}
		break;
	case B_AND_DOWN_RELEASE:
		if (mode == MODE_PLAY) {
			if (!isDpadSet) {
				isAnswerset = true;
				isDpadSet = true;
				getInput(9); // Enter number 9
			}
		}
		break;
	case _A_RELEASE:
		if (mode == MODE_MENU) {
			//Select for menu
			mode = MODE_SETUP;
			setOperationMode();
		} 
		else if (mode == MODE_SETUP) {
			menuSelectAdjust(&cursorPosition, 1, DISP_MENU_EXIT, DISP_MENU_START);
		}
		else if (mode == MODE_PAUSE) {
			if (cursorPosition == PAUSE_MENU_NO) {
				//restore timer
				timer = save_timer;

				mode = MODE_PLAY;
			}
			else if (cursorPosition == PAUSE_MENU_YES) {
				valueReset();
				mode = MODE_MENU;
			}
		}
		else if (mode == MODE_PLAY) {
			if (!isAorBheldDown) {
				isAnswerset = true;
				getInput(0); // Enter number 0
			}
			else { isAorBheldDown = false; }
		}
		break;
	case _B_RELEASE:
		if (mode == MODE_MENU) {
			//Select for menu
			mode = MODE_SETUP;
			setOperationMode();
		}
		else if (mode == MODE_SETUP) {
			menuSelectAdjust(&cursorPosition, -1, DISP_MENU_EXIT, DISP_MENU_START);
		}
		else if (mode == MODE_PAUSE) {
			if (cursorPosition == PAUSE_MENU_NO) {
				//restore timer
				timer = save_timer;

				mode = MODE_PLAY;
			}
			else if (cursorPosition == PAUSE_MENU_YES) {
				valueReset();
				mode = MODE_MENU;
			}
		}
		else if (mode == MODE_PLAY) {
			if (!isAorBheldDown) {
				isAnswerset = true;
				getInput(5); // Enter number 5
			}
			else { isAorBheldDown = false; }
		}
		break;
	case _UP_RELEASE:
		if (mode == MODE_MENU) {
			menuSelectAdjust(&menuSelect, -1, ADDITION, DIVISION);
		}
		else if (mode == MODE_PLAY) {
			//pause game
			mode = MODE_PAUSE;
			//save timer
			save_timer = timer;
		}
		break;
	case _LEFT_RELEASE:
		if (mode == MODE_SETUP) {
			if (cursorPosition == DISP_MENU_DIFF_SET) { 
				menuSelectAdjust(&difficulty, -1, 0, 2);
			} 
			else if (cursorPosition == DISP_MENU_RAN_SET) {
				menuSelectAdjust(&doRandomNumbers, -1, 0, 1);
			}
		}
		else if (mode == MODE_PAUSE) {
			menuSelectAdjust(&cursorPosition, -1, PAUSE_MENU_NO, PAUSE_MENU_YES);
		}
		else if (mode == MODE_PLAY) {
			/*
			Sets the negative or removes number 
			*/

			if (digitTrack == 0) {
				isAnswernegative = true;
			}
			else {
				//move back a number from input and clear negative 
				backspaceInput();
				//sets Answers to not set
				if (digitTrack == 0 || answer == 0) {
					isAnswerset = false;
				}
			}
			
		}
		break;
	case _RIGHT_RELEASE:
		if (mode == MODE_SETUP) {
			if (cursorPosition == DISP_MENU_DIFF_SET) {
				menuSelectAdjust(&difficulty, 1, 0, 2);
			}
			else if (cursorPosition == DISP_MENU_RAN_SET) {
				menuSelectAdjust(&doRandomNumbers, 1, 0, 1);
			}
		}
		else if (mode == MODE_PLAY) {
			//pause game
			mode = MODE_PAUSE;
			//save the timer 
			save_timer = timer;

		}
		else if (mode == MODE_PAUSE) {
			menuSelectAdjust(&cursorPosition, 1, PAUSE_MENU_NO, PAUSE_MENU_YES);
		}

		break;
	case _DOWN_RELEASE:
		if (mode == MODE_MENU) {
			menuSelectAdjust(&menuSelect, 1, ADDITION, DIVISION);
		}
		else if (mode == MODE_PLAY) {
			//move back a number from input and clear negative 

			backspaceInput();
			//sets Answers to not set
			if (digitTrack == 0 || answer == 0) {
				isAnswerset = false;
			}
			//removes negative number
			if (digitTrack == 0 && answer == 0) {
				isAnswernegative = false;
			}
		}
		break;

	default:
		if (mode == MODE_SETUP) {
			arrowOrientation = _NO_BUTTON;
		}

		break;
	}
	return;
}

void setOperationMode() {
	if (menuSelect == ADDITION) {
		operationMode = ADDITION;
	}
	else if (menuSelect == SUBTRACTION) {
		operationMode = SUBTRACTION;
	}
	else if (menuSelect == MULTIPLICATION) {
		operationMode = MULTIPLICATION;
	}
	else if (menuSelect == DIVISION) {
		operationMode = DIVISION;
	}

}

void menuSelectAdjust(int *val, int move, int min, int max) {
	*val = *val + move;
	if (*val < min) {
		*val = max;
	}
	else if (*val > max) {
		*val = min;
	}
}

void processInput() {
	currentButton = getButtonPress();
	return;
}

int getButtonPress() {

	/**/
	//A BUTTON
	if (arduboy.justReleased(A_BUTTON)) {
		return _A_RELEASE;
	}
	else if (arduboy.pressed(A_BUTTON)) {
		if (arduboy.pressed(LEFT_BUTTON)) {   
			return A_AND_LEFT;
		}
		else if (arduboy.pressed(RIGHT_BUTTON))
		{
			return A_AND_RIGHT;
		}
		else if (arduboy.pressed(UP_BUTTON))
		{
			return A_AND_UP;
		}
		else if (arduboy.pressed(DOWN_BUTTON))
		{
			return A_AND_DOWN;
		}
		//Release 
		else if (arduboy.justReleased(LEFT_BUTTON)) {
			/*these two flags stop the dpad from pressing multiple times 
			and the A or B button from pressing while its held down.
			Which is why they need to be set and unset for each dpad press.
			There is probably a better way to this but I can't think of it rn.
			What do you suggest?*/
			isDpadSet = false;     
			isAorBheldDown = true; 
			return A_AND_LEFT_RELEASE;
		}
		else if (arduboy.justReleased(RIGHT_BUTTON))
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return A_AND_RIGHT_RELEASE;
		}
		else if (arduboy.justReleased(UP_BUTTON))
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return A_AND_UP_RELEASE;
		}
		else if (arduboy.justReleased(DOWN_BUTTON))
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return A_AND_DOWN_RELEASE;
		}
		else {
			return _A;
		}
	}
	//B BUTTON
	else if (arduboy.justReleased(B_BUTTON)) {
		return _B_RELEASE;
	}
	else if (arduboy.pressed(B_BUTTON)) {
		if (arduboy.pressed(LEFT_BUTTON)) {
			return B_AND_LEFT;
		}
		else if (arduboy.pressed(RIGHT_BUTTON))
		{
			return B_AND_RIGHT;
		}
		else if (arduboy.pressed(UP_BUTTON))
		{
			return B_AND_UP;
		}
		else if (arduboy.pressed(DOWN_BUTTON))
		{
			return B_AND_DOWN;
		}
		//Release 
		else if (arduboy.justReleased(LEFT_BUTTON)) 
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return B_AND_LEFT_RELEASE;
		}
		else if (arduboy.justReleased(RIGHT_BUTTON))
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return B_AND_RIGHT_RELEASE;
		}
		else if (arduboy.justReleased(LEFT_BUTTON))
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return B_AND_LEFT_RELEASE;
		}
		else if (arduboy.justReleased(UP_BUTTON))
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return B_AND_UP_RELEASE;
		}
		else if (arduboy.justReleased(DOWN_BUTTON))
		{
			isDpadSet = false;
			isAorBheldDown = true;
			return B_AND_DOWN_RELEASE;
		}
		else {
			return _B;
		}
	}
	//DPAD
	else if (arduboy.justReleased(UP_BUTTON)) {
		return _UP_RELEASE;
	}
	else if (arduboy.justReleased(DOWN_BUTTON)) {
	return _DOWN_RELEASE;
	}
	else if (arduboy.justReleased(LEFT_BUTTON)) {
	return _LEFT_RELEASE;
	}
	else if (arduboy.justReleased(RIGHT_BUTTON)) {
	return _RIGHT_RELEASE;
	}
	else if (arduboy.pressed(UP_BUTTON)) {
	return _UP;
	}
	else if (arduboy.pressed(DOWN_BUTTON)) {
	return _DOWN;
	}
	else if (arduboy.pressed(LEFT_BUTTON)) {
	return _LEFT;
	}
	else if (arduboy.pressed(RIGHT_BUTTON)) {
	return _RIGHT;
	}
	else {
		return _NO_BUTTON;
	}

}

void valueReset() {
	mode = MODE_MENU;
	currentButton = _NO_BUTTON;
	menuSelect = 0;
	cursorPosition = 0;
	difficulty = 0;
	doRandomNumbers = 0;
	isDpadSet = false;
	isAorBheldDown = false;
	operationMode = 0;
	i = 1;
	j = 1;
	e = 10;
	arrowOrientation = _NO_BUTTON;
	isAnswernegative = false;
	isAnswerset = false;
	answer = 0;
	solution = 0;
	blinkValue = 0;
	digitTrack = 0;
	incorrectTrack = 0;
	correctTrack = 0;
	timer = 0;
	//t = 0; //I don't think I need to set this to zero because it rolls over with millis()
	duration = EASY;
}