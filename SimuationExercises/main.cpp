/** @file */

#include "stdafx.h"

#include <iostream>

#include "Entity.h"
#include "SUVAT.h"

void w1_entity()
{
  const size_t numEntities = 10;
  Entity *entities[numEntities];

  for (size_t i = 0; i < numEntities; i++)
    entities[i] = new Entity(10.0f);

  for (size_t i = 0; i < numEntities; i++)
  {
    Entity *a = entities[i];
    const float aAgroRange = a->aggroRange2();
    int & aNumInRange = a->entitiesInRangeRef();

    for (size_t j = 0; j < numEntities; j++)
    {
      if (i == j)
        continue;

      Entity *b = entities[j];

      float dist2 = abs(Vector3::distance2(a->position(), b->position()));
      aNumInRange += (dist2 <= aAgroRange);
    }

    std::cout << *a << "\t In Range: " << a->entitiesInRange() << std::endl;
  }
}

void w2_calc()
{
  std::cout << "Calculate [v,s]: ";
  char option;
  std::cin >> option;

  Vector3 u, a;
  float t;
  
  std::cout << "u: ";
  std::cin >> u;

  std::cout << "a: ";
  std::cin >> a;

  std::cout << "t: ";
  std::cin >> t;

  Vector3 res;

  switch (option)
  {
  case 'v':
    res = SUVAT::getVfromUAT(u, a, t);
    std::cout << "s=";
    break;
  case 's':
    res = SUVAT::getSfromUAT(u, a, t);
    std::cout << "s=";
    break;
  }

  std::cout << res << std::endl;
}

int main(int argc, char *argv[])
{
  //w1_entity();
  w2_calc();
  return 0;
}