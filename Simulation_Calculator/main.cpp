/**
 * @file
 * @author Dan Nixon
 */

#include <iostream>

#include <Simulation_Physics/SUVAT.h>
#include <Engine_Maths/Vector3.h>

using namespace Engine::Maths;
using namespace Simulation::Physics;

int main(int argc, char *argv[])
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

  return 0;
}
