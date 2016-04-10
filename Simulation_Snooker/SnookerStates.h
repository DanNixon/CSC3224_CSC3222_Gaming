/**
 * @file
 * @author Dan Nixon
 */

#ifndef _SIMULATION_SNOOKER_STATES_H_
#define _SIMULATION_SNOOKER_STATES_H_

#include <string>

#include <Engine_Graphics/LineMesh.h>
#include <Engine_Maths/VectorOperations.h>

#include <Simulation_AI/CompletableActionState.h>
#include <Simulation_AI/FunctionalState.h>
#include <Simulation_AI/IState.h>
#include <Simulation_AI/StateMachine.h>

#include "SnookerControls.h"
#include "SnookerSimulation.h"

namespace Simulation
{
namespace Snooker
{
  class PlayerState : public Simulation::AI::FunctionalState
  {
  public:
    PlayerState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine, int playerNumber)
        : FunctionalState("player_" + std::to_string(playerNumber), parent, machine)
        , m_playerNumber(playerNumber)
        , m_score(0)
    {
    }

    inline int playerNumber() const
    {
      return m_playerNumber;
    }

    inline int score() const
    {
      return m_score;
    }

    inline void addToScore(int points)
    {
      m_score += points;

      // TODO: dev only
      std::cout << "Player " << m_playerNumber << " score: " << m_score << std::endl;
    }

    PlayerState *otherPlayer() const
    {
      std::string name = "game/running/player_" + std::to_string((m_playerNumber + 1) % 2);
      return dynamic_cast<PlayerState *>(m_machine->rootState()->findState(name).back());
    }

  protected:
    virtual void onEntry(IState *last)
    {
      if (last->name() == "pot_cue_ball" || last->name() == "running")
        findState("place_cue_ball").back()->setActivation(true, this, this);
      else
        findState("take_shot").back()->setActivation(true, this, this);
    }

  private:
    int m_playerNumber; //!< Player number (0 or 1)
    int m_score;        //!< Players score
  };

  class WaitForShotState : public Simulation::AI::IState
  {
  public:
    WaitForShotState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine,
                     SnookerSimulation *simulation)
        : IState("wait_for_shot", parent, machine)
        , m_simulation(simulation)
        , m_targetBallPoints(-1)
    {
    }

    inline void setTargetBallPoints(int points)
    {
      m_targetBallPoints = points;
    }

    inline int targetBallPoints() const
    {
      return m_targetBallPoints;
    }

    inline Ball *lastPotted()
    {
      if (m_potted.empty())
        return nullptr;
      else
        return m_potted.back();
    }

    inline std::vector<Ball *> &potted()
    {
      return m_potted;
    }

  protected:
    virtual IState *testTransferFrom() const
    {
      if (m_simulation->physics.atRest())
      {
        // Cue ball was potted
        if (std::find(m_potted.begin(), m_potted.end(), m_simulation->balls[0]) != m_potted.end())
          return m_parent->findState("after_shot/foul/pot_wrong_ball/pot_cue_ball").back();

        // No ball was touched
        if (m_firstCueBallTouched == nullptr)
          return m_parent->findState("after_shot/foul/hit_nothing").back();

        // A specific correct ball was potted
        if (m_potted.size() == 1 && m_potted[0]->points() == m_targetBallPoints)
        {
          if (m_targetBallPoints == 1)
            return m_parent->findState("after_shot/legal/pot_red").back();
          else
            return m_parent->findState("after_shot/legal/pot_sequence_colour").back();
        }

        // Any colour was potted
        if (m_potted.size() == 1 && m_potted[0]->points() > 1 && m_targetBallPoints == 0)
          return m_parent->findState("after_shot/legal/pot_any_colour").back();

        // Wrong ball was potted
        if (!m_potted.empty())
          return m_parent->findState("after_shot/foul/pot_wrong_ball").back();

        // Hit incorrect ball
        if (m_targetBallPoints != m_firstCueBallTouched->points() ||
            (m_targetBallPoints == 0 && m_firstCueBallTouched->points() == 1))
          return m_parent->findState("after_shot/foul/hit_wrong_ball").back();

        // Did not pot anything
        if (m_potted.empty())
          return m_parent->findState("after_shot/legal/pot_nothing").back();

        return nullptr;
      }

      return nullptr;
    }

    virtual void onEntry(IState *last)
    {
      (void)last;
      m_firstCueBallTouched = nullptr;
      m_potted.clear();
    }

    virtual void onOperate()
    {
      std::vector<Simulation::Physics::InterfaceDef> inters = m_simulation->physics.interfaces();
      Ball *cueBall = m_simulation->balls[0];

      for (auto it = inters.begin(); it != inters.end(); ++it)
      {
        // Record the first ball the cue ball touches
        if (m_firstCueBallTouched == nullptr && it->contains(cueBall))
          m_firstCueBallTouched = dynamic_cast<Ball *>(it->otherNot(cueBall));

        // Record potted balls
        Simulation::Physics::Entity *a = it->entityA();
        Simulation::Physics::Entity *b = it->entityB();

        Ball *potted = nullptr;
        if (dynamic_cast<Pocket *>(a))
          potted = dynamic_cast<Ball *>(b);
        else if (dynamic_cast<Pocket *>(b))
          potted = dynamic_cast<Ball *>(a);

        if (potted && (std::find(m_potted.begin(), m_potted.end(), potted) == m_potted.end()))
        {
          // Record his ball as being potted
          m_potted.push_back(potted);

          // Reset to default position and stop motion
          potted->reset(true);

          // Set no collide
          potted->setCollide(false);

          // Make invisivle
          potted->setActive(false);
        }
      }
    }

  private:
    SnookerSimulation *m_simulation;
    Ball *m_firstCueBallTouched;
    std::vector<Ball *> m_potted;
    int m_targetBallPoints;
  };

  class TakeShotState : public Simulation::AI::CompletableActionState
  {
  public:
    TakeShotState(Simulation::AI::IState *parent, Simulation::AI::StateMachine *machine, SnookerSimulation *simulation)
        : CompletableActionState("take_shot", parent, machine)
        , m_simulation(simulation)
    {
    }

    virtual ~TakeShotState()
    {
      resetMousePosition();
    }

  protected:
    virtual IState *testTransferFrom() const
    {
      if (m_completed)
        return m_parent->findState("wait_for_shot").back();
      else
        return nullptr;
    }

    virtual void onExit(IState *next)
    {
      (void)next;
      m_simulation->balls[0]->setAcceleration(Engine::Maths::Vector2());
    }

    virtual void onEntry(IState *last)
    {
      CompletableActionState::onEntry(last);
      resetMousePosition();

      WaitForShotState *shotState = dynamic_cast<WaitForShotState *>(m_parent->findState("wait_for_shot").back());
      if (shotState == nullptr)
        return;

      // If players last shot in turn was a red then now they hit any colour
      // TODO
      if (shotState->lastPotted() != nullptr && shotState->lastPotted()->points() == 1)
        shotState->setTargetBallPoints(0);

      // Players first shot in turn is either on red or the next colour in sequence if no reds are in play
      // i.e. whatever the lowest value ball in play is
      for (size_t i = 1; i < SnookerSimulation::NUM_BALLS; i++)
      {
        if (m_simulation->balls[i]->collides() && shotState)
        {
          shotState->setTargetBallPoints(m_simulation->balls[i]->points());
          return;
        }
      }
    }

    virtual void onOperate()
    {
      // Mouse clicks (to take shots)
      if (m_mouseStartPosition == nullptr)
      {
        if (m_simulation->controls->state(S_TAKE_SHOT))
        {
          // Record starting position of mouse
          m_mouseStartPosition = new Engine::Maths::Vector2(m_simulation->controls->analog(A_MOUSE_X),
                                                            m_simulation->controls->analog(A_MOUSE_Y));
          static_cast<Engine::Graphics::LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(Engine::Maths::Vector3());
          m_simulation->shotAimLine->setActive(true);
        }
        else
        {
          m_simulation->balls[0]->setAcceleration(Engine::Maths::Vector2());
        }
      }
      else
      {
        Engine::Maths::Vector2 newMousePosition = Engine::Maths::Vector2(m_simulation->controls->analog(A_MOUSE_X),
                                                                         m_simulation->controls->analog(A_MOUSE_Y));
        Engine::Maths::Vector2 deltaMouse = *m_mouseStartPosition - newMousePosition;

        // Clamp max acceleration to a sensible level
        float maxShotMagnitude = 0.5f;
        if (deltaMouse.length2() > (maxShotMagnitude * maxShotMagnitude))
          deltaMouse = Engine::Maths::VectorOperations::GetNormalised(deltaMouse) * maxShotMagnitude;

        if (!m_simulation->controls->state(S_TAKE_SHOT))
        {
          m_simulation->shotAimLine->setActive(false);
          m_simulation->balls[0]->setAcceleration(deltaMouse);
          resetMousePosition();
          m_completed = true;
        }
        else
        {
          static_cast<Engine::Graphics::LineMesh *>(m_simulation->shotAimLine->mesh())->setTo(deltaMouse * 1000.0f);
        }
      }
    }

  private:
    inline void resetMousePosition()
    {
      if (m_mouseStartPosition != nullptr)
        delete m_mouseStartPosition;
      m_mouseStartPosition = nullptr;
    }

  private:
    SnookerSimulation *m_simulation;
    Engine::Maths::Vector2 *m_mouseStartPosition;
  };
}
}

#endif