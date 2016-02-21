/**
 * @file
 * @author Dan Nixon
 */

#include <string>

#include "DemoGame.h"
#include "DemoKeyboardHandler.h"
#include "DemoMouseHandler.h"
#include "DemoJoystickHandler.h"

int main(int argc, char *args[])
{
  DemoGame g;

  g.init();

  DemoKeyboardHandler kbh;
  g.addEventHandler(&kbh);

  DemoMouseHandler mh;
  g.addEventHandler(&mh);

  DemoJoystickHandler jsh;
  g.addEventHandler(&jsh);

  g.run();

  return 0;
}
