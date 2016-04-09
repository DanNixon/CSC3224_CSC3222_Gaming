/**
 * @file
 * @author Dan Nixon
 */

#include "SnookerSimulation.h"

#include <sstream>

#include <SDL_ttf.h>

#include <Engine_Common/Profiler.h>
#include <Engine_Graphics/LineMesh.h>
#include <Engine_Graphics/Shaders.h>
#include <Engine_Maths/VectorOperations.h>

#include "SnookerControls.h"
#include "SnookerStateMachine.h"

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Input;
using namespace Simulation::Physics;
using namespace Simulation::AI;

namespace Simulation
{
namespace Snooker
{
  SnookerSimulation::SnookerSimulation()
      : Game("Snooker Loopy", std::make_pair(1024, 768))
      , fsm(new SnookerStateMachine(this))
  {
  }

  SnookerSimulation::~SnookerSimulation()
  {
  }

  /**
   * @copydoc Game::gameStartup
   */
  int SnookerSimulation::gameStartup()
  {
    // Init state machine
    static_cast<SnookerStateMachine *>(fsm)->initStates();

    // Load font for text display
    m_fontLarge = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 45);
    m_fontMedium = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20);

    // Table
    m_table = new Table(physics.entities());
    m_table->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -3600.0)));

    // Balls
    balls[0] = new Ball(Vector2(), -1); // Cue ball
    balls[1] = new Ball(Vector2(), 1);  // Red
    balls[2] = new Ball(Vector2(), 1);  // Red
    balls[3] = new Ball(Vector2(), 1);  // Red
    balls[4] = new Ball(Vector2(), 1);  // Red
    balls[5] = new Ball(Vector2(), 1);  // Red
    balls[6] = new Ball(Vector2(), 1);  // Red
    balls[7] = new Ball(Vector2(), 1);  // Red
    balls[8] = new Ball(Vector2(), 1);  // Red
    balls[9] = new Ball(Vector2(), 1);  // Red
    balls[10] = new Ball(Vector2(), 1); // Red
    balls[11] = new Ball(Vector2(), 1); // Red
    balls[12] = new Ball(Vector2(), 1); // Red
    balls[13] = new Ball(Vector2(), 1); // Red
    balls[14] = new Ball(Vector2(), 1); // Red
    balls[15] = new Ball(Vector2(), 1); // Red
    balls[16] = new Ball(Vector2(), 2); // Yellow
    balls[17] = new Ball(Vector2(), 3); // Green
    balls[18] = new Ball(Vector2(), 4); // Brown
    balls[19] = new Ball(Vector2(), 5); // Blue
    balls[20] = new Ball(Vector2(), 6); // Pink
    balls[21] = new Ball(Vector2(), 7); // Black

    placeBalls();

    for (size_t i = 0; i < NUM_BALLS; i++)
    {
      if (balls[i] != nullptr)
      {
        m_table->addChild(balls[i]);
        physics.addEntity(balls[i]);
      }
    }

    // Scene
    Matrix4 view = Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10));
    Matrix4 proj = Matrix4::Perspective(1, 100000, 1.33f, 45.0f);
    m_scene = new Scene(m_table, view, proj);

    // UI
    Matrix4 orth = Matrix4::Orthographic(0.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f);
    m_ui = new Scene(new SceneObject("root"), view, orth);

    m_uiShader = new ShaderProgram();
    m_uiShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    m_uiShader->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
    m_uiShader->link();

    m_profileText = new TextPane("profile_info", 0.05f, m_uiShader, m_fontMedium);
    m_profileText->setActive(false);
    m_profileText->setModelMatrix(Matrix4::Translation(Vector3(-0.5f, 0.8f, 0.0f)));
    m_profileText->setText("Graphics: -\nPhysics: -");
    m_ui->root()->addChild(m_profileText);

    shotAimLine = new RenderableObject("aim_line", new LineMesh(Vector3(), Vector3()), m_uiShader);
    shotAimLine->setActive(false);
    balls[0]->addChild(shotAimLine);

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");
    m_physicsLoop = addTimedLoop(8.33f, "physics");
    m_controlLoop = addTimedLoop(25.0f, "control");
    m_profileLoop = addTimedLoop(1000.0f, "profile");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    controls = new SnookerControls(this);

    // Menu
    m_menu = new OptionsMenu(this, m_fontMedium, 0.05f, this);
    m_menu->setMargin(Vector2(0.005f, 0.005f));
    m_menu->layout();
    m_menu->show();
    addEventHandler(m_menu);

    m_profiler = new Profiler(this);

    return 0;
  }

  /**
   * @copydoc Game::gameLoop
   */
  void SnookerSimulation::gameLoop(Uint8 id, float dtMilliSec)
  {
    // Handle graphics
    if (id == m_graphicsLoop)
    {
      m_scene->update(dtMilliSec, Subsystem::GRAPHICS);
      m_ui->update(dtMilliSec, Subsystem::GRAPHICS);
      m_menu->update(dtMilliSec, Subsystem::GRAPHICS);

      swapBuffers();
    }
    // Handle physics
    else if (id == m_physicsLoop)
    {
      physics.update(dtMilliSec);
    }
    // Handle control
    else if (id == m_controlLoop)
    {
      // Update state machine
      if (fsm->update())
      {
        m_menu->updateTextFromState();
        std::cout << "FSM state change: " << StateMachine::BranchToString(fsm->activeStateBranch()) << std::endl;
      }

      // Profile display
      m_profileText->setActive(controls->state(S_PROFILE_DISPLAY));

      // Pause
      physics.setRunning(!controls->state(S_PAUSE));
    }
    // Output profiling data
    else if (id == m_profileLoop)
    {
      m_profiler->computeStats(dtMilliSec);

      if (controls->state(S_PROFILE_DISPLAY))
      {
        std::stringstream profileStr;
        profileStr.precision(3);
        profileStr << "Graphics: " << m_profiler->frameRate(m_graphicsLoop) << " FPS"
                   << " (" << m_profiler->averageDuration(m_graphicsLoop) << "ms)" << '\n'
                   << "Physics: " << m_profiler->frameRate(m_physicsLoop) << " FPS"
                   << " (" << m_profiler->averageDuration(m_physicsLoop) << "ms)";

        m_profileText->setText(profileStr.str());
      }
    }
  }

  /**
   * @copydoc Game::gameShutdown
   */
  void SnookerSimulation::gameShutdown()
  {
  }

  /**
   * @brief Sets the intial position of the balls and resets velcoity and
   *        acceleration to zero.
   */
  void SnookerSimulation::placeBalls()
  {
    // Initial positions
    balls[0]->setPosition(Vector2(-1150.0f, 200.0f));    // Cue ball
    balls[1]->setPosition(Vector2(957.85f, 0.0f));       // Red
    balls[2]->setPosition(Vector2(1010.35f, 26.25f));    // Red
    balls[3]->setPosition(Vector2(1010.35f, -26.25f));   // Red
    balls[4]->setPosition(Vector2(1062.85f, 52.5f));     // Red
    balls[5]->setPosition(Vector2(1062.85f, 0.0f));      // Red
    balls[6]->setPosition(Vector2(1062.85f, -52.5f));    // Red
    balls[7]->setPosition(Vector2(1115.35f, 78.75f));    // Red
    balls[8]->setPosition(Vector2(1115.35f, 26.25f));    // Red
    balls[9]->setPosition(Vector2(1115.35f, -26.25f));   // Red
    balls[10]->setPosition(Vector2(1115.35f, -78.75f));  // Red
    balls[11]->setPosition(Vector2(1167.85f, 105.0f));   // Red
    balls[12]->setPosition(Vector2(1167.85f, 52.5f));    // Red
    balls[13]->setPosition(Vector2(1167.85f, 0.0f));     // Red
    balls[14]->setPosition(Vector2(1167.85f, -52.5f));   // Red
    balls[15]->setPosition(Vector2(1167.85f, -105.0f));  // Red
    balls[16]->setPosition(Vector2(-1047.75f, -291.1f)); // Yellow
    balls[17]->setPosition(Vector2(-1047.75f, 291.1f));  // Green
    balls[18]->setPosition(Vector2(-1047.75f, 0.0f));    // Brown
    balls[19]->setPosition(Vector2(0.0f, 0.0f));         // Blue
    balls[20]->setPosition(Vector2(895.35f, 0.0f));      // Pink
    balls[21]->setPosition(Vector2(1466.85f, 0.0f));     // Black

    // Reset acceleration and velocity to zero
    for (size_t i = 0; i < NUM_BALLS; i++)
    {
      balls[i]->setVelocity(Vector2());
      balls[i]->setAcceleration(Vector2());
    }
  }
}
}