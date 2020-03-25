#include "CheckFrequency.h"
#include <iostream>
#include <string>

using namespace std;

CheckFrequency::CheckFrequency(struct MenuItems anItem[], int size)
{
  initArr(anItem, size);
}

CheckFrequency::~CheckFrequency()
{
  delete [] arrFreq;  //deletes memory and frees pointer
  arrFreq = nullptr;
}

//initializes the dynamically allocated array to zeros and 5 to dishes with no name
void CheckFrequency::initArr(struct MenuItems anItem[], int size)
{
  arrFreq = new int[size];

  for(int i = 0; i < size; i++)
  {
    arrFreq[i] = 0;
    if(anItem[i].dishName == "No Dish Name")
      arrFreq[i] = 5;
  }
}

bool CheckFrequency::checkFreq(struct MenuItems anItem[], int num, int size)
{
  int i = 0;
  bool flag = true;

  //checks whether the item num index is less than 5 and if it is not, Return true to keep looping through random number generator
  if(arrFreq[num] < 5)
  {
    arrFreq[num]++;
    while(i < size)
    {
      if(arrFreq[i] < 5)
        flag = false;
      i++;
    }
    if(flag == true)  //if all numbers is equal to 5, flag is true and the memory from arrFreq is deleted and reinitialize the array
    {
      delete [] arrFreq;

      initArr(anItem, size);
    }
    return false;
  }
  else
    return true;

}
