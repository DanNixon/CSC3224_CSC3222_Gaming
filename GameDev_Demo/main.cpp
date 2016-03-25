/**
 * @file
 * @author Dan Nixon
 */

#include "DemoGame.h"

#include <Random.h>
#include <test.h>

int main(int argc, char *args[])
{
  Engine::Utility::Random r("function = Gaussian, width = 2, mean = 5 ");

  for (int i = 0; i < 100; i++)
    std::cout << i << ": " << r() << std::endl;

  return 0;

  // GameDev::Demo::DemoGame g;
  // return g.run();
}
