#ifndef CHECKFREQUENCY_H
#define CHECKFREQUENCY_H

#include "itemListStruct.h"

//using namespace std;

class CheckFrequency
{
  private:
    int* arrFreq;

  public:
    CheckFrequency(struct MenuItems anItem[], int size);
    ~CheckFrequency();
    void initArr(struct MenuItems anItem[], int size);
    bool checkFreq(struct MenuItems anItem[], int num, int size);
};
#endif
