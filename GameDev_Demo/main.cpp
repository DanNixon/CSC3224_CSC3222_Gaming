/**
 * @file
 * @author Dan Nixon
 */

#include <string>

#include "DemoGame.h"

#include <DemoKeyboardHandler.h>

using namespace Engine::Input;

int main(int argc, char *args[])
{
  DemoGame g;

  g.init();

  // Demo input handlers
  DemoKeyboardHandler kbh;
  g.addEventHandler(&kbh);

  g.run();

  return 0;
}
