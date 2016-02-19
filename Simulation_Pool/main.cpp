/**
 * @file
 * @author Dan Nixon
 */

#include <iostream>

#include <Entity.h>

int main(int argc, char *argv[])
{
  const size_t numEntities = 10;
  Entity *entities[numEntities];

  for (size_t i = 0; i < numEntities; i++)
    entities[i] = new Entity(10.0f);

  for (size_t i = 0; i < numEntities; i++)
  {
    Entity *a = entities[i];
    const float aAgroRange = a->aggroRange2();
    int &aNumInRange = a->entitiesInRangeRef();

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

  return 0;
}
