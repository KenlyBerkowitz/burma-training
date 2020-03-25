/*
Created by Kenly Berkowitz
--------------------------
This program is used as a training program for a local restaurant in Oakland, CA.
It has helped train people about their knowledge of the menu.The program features two types
of flash card programs, differing in menu size, and three tests to determine the
scores of employee knowledge.  It inputs the menu into a structured array from an external
.txt file. The program uses a class to keep track of the amount of times a dish is called
and returns a boolean to determine if the program should output the dish.  Furthermore, it
makes use of dynamically allocated arrays,object-oriented programming, various data structures
and STL vectors.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CheckFrequency.h"
#include "itemListStruct.h"

using namespace std;
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void readMenuFile(MenuItems[], int &, int);
void displayMenu();
void getSwitchChoice(int &);
void caseOption1(MenuItems[], int);
int getRandomNumber(MenuItems[], int);
int getUserGuess(MenuItems[], int);
void caseOption3(MenuItems[], int);
int caseOption4(MenuItems[], int);
void caseOption5(MenuItems[], int);
bool checkRandomNumber(vector<int> &, int);
void clearScreen();
void loopSleep();

int main()
{
  //data
  int userSwitchChoice;
  //empty menu list
  const int MAX_ITEMS = 100;  //max array value
  int itemIndex = 0;  //index for array and becomes new array size
  MenuItems menu[MAX_ITEMS];  //an array with the struct MenuItems and will get the whole menu
  float highScore = 0.0;
  int partMenu = 24;
  int *fullMenu = &itemIndex;

  srand(time(0));  //seeds random number function

  readMenuFile(menu, itemIndex, MAX_ITEMS);  //reads file that the menu is stored in and itemIndex gets changed
  clearScreen();
  displayMenu();  //display the options menu

  do
  {
    getSwitchChoice(userSwitchChoice);
    switch(userSwitchChoice)
    {
      case 1:
          caseOption1(menu, partMenu);  //menu option 1
          clearScreen();
          displayMenu();
          break;
      case 2:
          caseOption1(menu, *fullMenu);  //menu option 2
          clearScreen();
          displayMenu();
          break;
      case 3:
          caseOption3(menu, partMenu);  //menu option 3
          clearScreen();
          displayMenu();
          break;
      case 4:
          highScore = caseOption4(menu, *fullMenu);  //menu option 4
          clearScreen();
          displayMenu();
          break;
      case 5:
          if(highScore >= 80)
          {
            caseOption5(menu, *fullMenu);  //menu option 5
            clearScreen();
            displayMenu();
            break;
          }
          else
          {
            cout << "\nCannot Access. You must score higher than 80% on test 4. " << endl;
            cout << "High score: " << highScore << endl << endl;
            loopSleep();
            clearScreen();
            displayMenu();
            break;
          }
      default: cout << "Thanks for training to be the next superstar. \n";
    }//switch
  }while(userSwitchChoice != 0);

  return 0;
}//main

void readMenuFile(MenuItems menu1[], int &index, int max_Items)
{
  ifstream fin;
  MenuItems aDish;
  fin.open("menuList.txt");
  if(fin)  //checks if menu item
  {
    while(fin.good())
    {
      getline(fin, aDish.dishName);  //inputs dishName

      fin >> aDish.dishNum;  //inputs dishNumber
      fin.ignore(1000, 10);

      getline(fin, aDish.dishDescrip);  //inputs a dish description

      fin.ignore(1000,10);  //skips line

      if(index < max_Items)
        menu1[index++] = aDish;
    }
    index--;
  }

  else
    cout << "Error opening file.";

}//readMenuFile

void displayMenu()
{
  cout << "\t\t  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **" << endl
       << "\t\t   ** ** ARE YOU THE NEXT BURMA SUPERSTAR? ** ** " << endl
       << "\t\t  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **" << endl << endl
       << "\t\tSelect a number from the menu to enter that program. \n\n"
       << "1. Practice guessing the numbers assigned to salads, soups, and appetizers. (Beginner) \n"
       << "2. Practice guessing the numbers assigned to dishes on the whole menu. \n"
       << "3. TEST - Take a test for the numbers assigneed to salads, soups, and appetizers. (Beginner) \n"
       << "4. TEST - Take a test for the numbers assigned to the dish names on the whole menu. \n"
       << "5. TEST - Take a test for the numbers assigned to the dish descriptions on the whole menu. \n"
       << "          (Advanced- Must score above 80 % on option 4 TEST to enter) \n\n"
       << "0. Enter zero to quit the whole program" << endl << endl;
}//displayMenu

void getSwitchChoice(int &userChoice)
{
  cout << "Select a number from the option menu above [ex: 1] : ";
  do
  {
    cin >> userChoice;
    cin.ignore(1000, 10);
    if(userChoice < 0 && userChoice > 5)
    {
      cout << endl << "Invalid input.\n Please enter another number 0 - 4 : ";
    }
  }while(userChoice < 0 && userChoice > 5);  //dowhile
}//getSwitchChoice

//*******************************
// menu option 1 & 2
//*******************************

void caseOption1(MenuItems menu1[], int pMenu)  //might not need max_size here. I should be able to duplicate for case 2
{
  //data
  int randIndex;
  int userGuess;
  CheckFrequency Check(menu1, pMenu);  //initalize object to keep track of the frequency of numbers called

  clearScreen();

  cout << "This program will give you the name of a dish and you\nwill enter the number that is associated with it." << endl << endl;
  do
  {
    do
    {
      randIndex = getRandomNumber(menu1, pMenu);
    }while(Check.checkFreq(menu1, randIndex, pMenu));

    cout << "If you want to quit, enter 0 for your guess." << endl << endl;
    cout << "Dish name: " << menu1[randIndex].dishName << endl;

    do
    {
      userGuess = getUserGuess(menu1, pMenu);
      if(userGuess == 0)
        break;

      if(userGuess == randIndex)
      {
        if(randIndex % 2 == 0)            //gives a different response to make the responses more random
          cout << "\nCorrect!!\n";
        else
          cout << "\nYou got it!\n";
      }//if
      else
      {
        if(randIndex % 2 == 0)                 //gives a different response to make the responses more random
          cout << "\nSorry, guess again.\n";
        else
          cout << "\nIncorrect guess.\n";
      }
      loopSleep();
      clearScreen();
    }while(userGuess != randIndex);
  }while(userGuess != 0);
}//caseOption1

int getRandomNumber(MenuItems menu2[], int menuSize)  //sends in the menu and menuSize if for the validation if the guess needs to be part or full menu
{
  int randNum;

  if(menuSize == 24)
  {
    do
    {
      randNum = (rand() % 24);  // creates a random number 1 to 23
    }while(menu2[randNum].dishName == "No Dish Name");
  }//if
  else
  {
    do
    {
      randNum = (rand() % 101);  // creates a random number 1 to 100
    }while(menu2[randNum].dishName == "No Dish Name");
  }//else

  return randNum;
}//getRandomNumber

int getUserGuess(MenuItems menu3[], int menuSize2)  //sends in the menu and menuSize if for the validation if the guess needs to be part or full menu
{
  int uGuess;
  if(menuSize2 == 24)
  {
    do
    {
      cout << "Enter number: ";
      cin >> uGuess;
      if(menu3[uGuess].dishName == "No Dish Name")
        cout << "There is no number " << uGuess << " ." << endl;
      if(uGuess < 0 || uGuess >= 24)
        cout << "Number needs to be between 0 - 23. ";
      if(uGuess == 0)
        break;
    }while(( uGuess < 0 || uGuess >= 24) || (menu3[uGuess].dishName == "No Dish Name"));
  }
  else
  {
    do
    {
      cout << "Enter number: ";
      cin >> uGuess;
      if(menu3[uGuess].dishName == "No Dish Name")
        cout << "There is no number " << uGuess << " ." << endl;
      if(uGuess < 0 || uGuess >= 101)
        cout << "Number needs to be between 0 - 100. ";
      if(uGuess == 0)
        break;
    }while((uGuess < 0 || uGuess >= 101) || (menu3[uGuess].dishName == "No Dish Name"));
  }

  return uGuess;
}

//*******************************
// menu option 3
//*******************************

void caseOption3(MenuItems menu5[], int pMenu)
{
  float correct = 0;
  int questionCount = 0;
  int testCount = 0;
  int randNum;
  int userGuess1;
  float score = 0.0;
  vector<int> numAsked3;

  clearScreen();

  cout << "This test will give you a dish name \nand you will give the number that is associated with it. " << endl << endl;

  for(int i = 0; i < pMenu; i++)
  {
    if(menu5[i].dishName == "No Dish Name")
      testCount++;
  }

  while(testCount < pMenu)
  {
    clearScreen();
    do
    {
      randNum = getRandomNumber(menu5, pMenu);
    }while(checkRandomNumber(numAsked3,randNum));

    questionCount++;
    testCount++;
    cout << endl << questionCount << ") Dish name: " << menu5[randNum].dishName << endl;
    userGuess1 = getUserGuess(menu5, pMenu);

    if(menu5[randNum].dishNum == userGuess1)
      correct++;
  }
  score = (correct/questionCount) * 100;
  cout << endl << "Your score is %" << score << endl;

  cout << "Press any key to continue..." << endl;
  cin.ignore(1000,10);
  cin.get();
}

//*******************************
// menu option 4
//*******************************

int caseOption4(MenuItems menu6[], int pMenu)
{
  float correct = 0;
  int questionCount = 0;
  int testCount = 0;
  int randNum;
  int userGuess1;
  float score1;
  vector<int> numAsked2;

  clearScreen();

  cout << "This test will give you a dish name \nand you will give the number that is associated with it. " << endl << endl;

  for(int i = 0; i < pMenu; i++)
  {
    if(menu6[i].dishName == "No Dish Name")
      testCount++;
  }

  while(testCount < pMenu)
  {
    do
    {
      randNum = getRandomNumber(menu6, pMenu);
    }while(checkRandomNumber(numAsked2,randNum));

    questionCount++;
    testCount++;
    cout << endl << questionCount << ") Dish name: " << menu6[randNum].dishName << endl;
    userGuess1 = getUserGuess(menu6, pMenu);

    if(menu6[randNum].dishNum == userGuess1)
      correct++;
  }
  score1 = (correct/questionCount) * 100;
  cout << endl << "Your score is %" << score1 << endl;

  cout << "Press any key to continue..." << endl;
  cin.ignore(1000,10);
  cin.get();

  return score1;
}

//*******************************
// menu option 5
//*******************************

void caseOption5(MenuItems menu7[], int pMenu)
{
  float correct = 0;
  int questionCount = 0;
  int testCount = 0;
  int randNum;
  int userGuess1;
  float score = 0.0;
  vector<int> numAsked2;

  cout << "This test will give you a dish name \nand you will give the number that is associated with it. " << endl << endl;

  for(int i = 0; i < pMenu; i++)
  {
    if(menu7[i].dishName == "No Dish Name")
      testCount++;
  }

  while(testCount < pMenu)
  {
    do
    {
      randNum = getRandomNumber(menu7, pMenu);
    }while(checkRandomNumber(numAsked2,randNum));

    questionCount++;
    testCount++;
    cout << endl << questionCount << ") Dish name: " << menu7[randNum].dishDescrip << endl;
    userGuess1 = getUserGuess(menu7, pMenu);

    if(menu7[randNum].dishNum == userGuess1)
    {
      correct++;
    }
  }
  score = (correct/questionCount) * 100;
  cout << endl << "Your score is %" << score << endl;

  cout << "Press any key to continue..." << endl;
  cin.ignore(1000,10);
  cin.get();
}

bool checkRandomNumber(vector<int> &numbersAsked1, int randNum1)
{
  if(numbersAsked1.empty())
  {
    numbersAsked1.push_back(randNum1);
    return false;
  }
  else
  {
    for(int i = 0; i < numbersAsked1.size(); i++)
    {
      if(numbersAsked1[i] == randNum1)
        return true;
    }
    numbersAsked1.push_back(randNum1);
    return false;
  }
}

void clearScreen()
{
  #ifdef _WIN32
    system("CLS");
  #else
    system("clear");
  #endif

  cout <<"\n\n\n" << endl;
}

void loopSleep()
{
  #ifdef _WIN32
  Sleep(1500);
  #else
  usleep(1500000);
  #endif
}
