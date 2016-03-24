/**
 * @file
 * @author Dan Nixon
 */

#ifndef _GAMEDEV_DEMO_CONTROLS_H_
#define _GAMEDEV_DEMO_CONTROLS_H_

namespace GameDev
{
namespace Demo
{
  /**
   * @enum Controls
   * @brief Enumeration of all control states required in the demo.
   * @author Dan Nixon
   */
  enum Controls
  {
    A_PITCH,
    A_ROLL,
    A_YAW,
    A_THROT,
    S_INCTHROT,
    S_DECTHROT,
    S_YAWCW,
    S_YAWCCW,
    S_FPV,
    S_OPENMENU
  };
}
}

#endif
