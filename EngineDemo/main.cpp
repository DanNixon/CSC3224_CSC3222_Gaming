/** @file */

#include "stdafx.h"

#include <string>

#include "DemoGame.h"

int main(int argc, char *args[])
{
  DemoGame g;

  g.init();
  g.run();

  return 0;
}