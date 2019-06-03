#include "pch.h"
#include "Random.h"
#include <time.h>
#include <cstdlib>

void RandomInit()
{
  srand((unsigned)time(NULL));
}

int RandomRange(const int rangeMin, const int rangeMax)
{
  int randNum = (rand() % (rangeMax - rangeMin + 1)) + rangeMin;
  return randNum;
}