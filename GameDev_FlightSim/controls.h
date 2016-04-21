/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _GAMEDEV_DEMO_CONTROLS_H_
#define _GAMEDEV_DEMO_CONTROLS_H_

namespace GameDev
{
  namespace FlightSim
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
    A_ENGINE,
    S_INCTHROT,
    S_DECTHROT,
    S_YAWCW,
    S_YAWCCW,
    S_ENGINEOFF,
    S_ENGINE1,
    S_ENGINE2,
    S_FPV,
    S_OPENMENU
  };
}
}

#endif
