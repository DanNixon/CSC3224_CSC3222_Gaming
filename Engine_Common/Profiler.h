/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_COMMON_PROFILER_H_
#define _ENGINE_COMMON_PROFILER_H_

#include "Game.h"

namespace Engine
{
namespace Common
{
  /**
   * @class Profiler
   * @brief Utility class for measuring the performance of subsystems in timed
   *        loops of a Game.
   * @author Dan Nixon
   */
  class Profiler
  {
  public:
    /**
     * @var NUM_PROFILES
     * @brief Number of profiles that will be kept.
     *
     * Number of timed loops + 2.
     */
    static const int NUM_PROFILES = Game::MAX_TIMED_LOOPS + 2;

    /**
     * @var MAIN_LOOP
     * @brief Flag for querying performance of main game loop.
     */
    static const int MAIN_LOOP = Game::MAX_TIMED_LOOPS;

    /**
     * @var EVENTS
     * @brief Flag for querying performance of event handling.
     */
    static const int EVENTS = Game::MAX_TIMED_LOOPS + 1;

    Profiler(Engine::Common::Game *target);
    virtual ~Profiler();

    void computeStats(float dtMilliSec);

    float frameRate(int idx) const;
    float averageDuration(int idx) const;

    void outputToStream(std::ostream &o) const;

    /**
     * @brief Outputs friendly formatted performance statistics to a stream.
     * @param o Stream
     * @param p Profiler
     * @return Stream
     */
    friend std::ostream &operator<<(std::ostream &o, const Profiler &p)
    {
      p.outputToStream(o);
      return o;
    }

  private:
    friend class Engine::Common::Game;

    Game *m_target; //!< Game being profiled

    unsigned long m_loopUpdates[NUM_PROFILES]; //!< Counter of updates per time frame
    float m_duration[NUM_PROFILES];            //!< Cumulative duration of each loop per
                                               //! time frame

    float m_avgFrameRate[NUM_PROFILES]; //!< Average frame rate for each profile
    float m_avgDuration[NUM_PROFILES];  //!< Average duration for each profile
  };
}
}

#endif
