/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3222 Project 1.
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

// Uncomment to run with correct layout when building in Debug mode
// #undef _DEBUG

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
    // Load shader for menu
    ShaderProgram *menuShader = new ShaderProgram();
    menuShader = new ShaderProgram();
    menuShader->addShader(new VertexShader("../resources/shader/vert_simple.glsl"));
    menuShader->addShader(new FragmentShader("../resources/shader/frag_tex.glsl"));
    menuShader->link();
    ShaderProgramLookup::Instance().add("menu_shader", menuShader);

    // Load font for text display
    m_fontLarge = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 45);
    m_fontMedium = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20);

    // Table
    m_table = new Table(physics.entities());
    m_table->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -3600.0)));

    initBalls();

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

    // Alignments
    Alignment_bitset centreRight;
    centreRight.set(Alignment::X_RIGHT);
    centreRight.set(Alignment::Y_CENTRE);

    Alignment_bitset centreLeft;
    centreLeft.set(Alignment::X_LEFT);
    centreLeft.set(Alignment::Y_CENTRE);

    // Status line
    statusLine = new TextPane("status_line", 0.06f, m_uiShader, m_fontLarge);
    statusLine->setModelMatrix(Matrix4::Translation(Vector3(-0.6f, -0.9f, 0.0f)));
    statusLine->setAlignment(centreLeft);
    statusLine->setText("Snooker Loopy!");
    m_ui->root()->addChild(statusLine);

    // Foul status line
    foulLine = new TextPane("status_line", 0.05f, m_uiShader, m_fontLarge);
    foulLine->setModelMatrix(Matrix4::Translation(Vector3(0.0f, -0.90f, 0.0f)));
    foulLine->setAlignment(centreLeft);
    foulLine->setActive(false);
    m_ui->root()->addChild(foulLine);

    // Scores
    scoreDisplay = new SceneObject("scores");
    scoreDisplay->setModelMatrix(Matrix4::Translation(Vector3(-0.75f, -0.9f, 0.0f)));
    m_ui->root()->addChild(scoreDisplay);

    // Player 1 score
    TextPane *player1Text = new TextPane("player_1", 0.06f, m_uiShader, m_fontMedium);
    player1Text->setModelMatrix(Matrix4::Translation(Vector3(0.0f, 0.03f, 0.0f)));
    player1Text->setAlignment(centreRight);
    player1Text->setText("Player 1:");
    scoreDisplay->addChild(player1Text);

    player1ScoreText = new TextPane("player_1_score", 0.06f, m_uiShader, m_fontMedium);
    player1ScoreText->setModelMatrix(Matrix4::Translation(Vector3(0.01f, 0.0f, 0.0f)));
    player1ScoreText->setAlignment(centreLeft);
    player1ScoreText->setText("0");
    player1Text->addChild(player1ScoreText);

    player1IndicatorText = new TextPane("player_1_indicator", 0.06f, m_uiShader, m_fontMedium);
    player1IndicatorText->setModelMatrix(Matrix4::Translation(Vector3(-0.18f, 0.0f, 0.0f)));
    player1IndicatorText->setAlignment(centreRight);
    player1IndicatorText->setText("=>");
    player1Text->addChild(player1IndicatorText);

    // Player 2 score
    TextPane *player2Text = new TextPane("player_2", 0.06f, m_uiShader, m_fontMedium);
    player2Text->setModelMatrix(Matrix4::Translation(Vector3(0.0f, -0.03f, 0.0f)));
    player2Text->setAlignment(centreRight);
    player2Text->setText("Player 2:");
    scoreDisplay->addChild(player2Text);

    player2ScoreText = new TextPane("player_1_score", 0.06f, m_uiShader, m_fontMedium);
    player2ScoreText->setModelMatrix(Matrix4::Translation(Vector3(0.01f, 0.0f, 0.0f)));
    player2ScoreText->setAlignment(centreLeft);
    player2ScoreText->setText("0");
    player2Text->addChild(player2ScoreText);

    player2IndicatorText = new TextPane("player_2_indicator", 0.06f, m_uiShader, m_fontMedium);
    player2IndicatorText->setModelMatrix(Matrix4::Translation(Vector3(-0.18f, 0.0f, 0.0f)));
    player2IndicatorText->setAlignment(centreRight);
    player2IndicatorText->setText("=>");
    player2Text->addChild(player2IndicatorText);

    scoreDisplay->setActive(false);

    // Shot aim line
    shotAimLine = new RenderableObject("aim_line", new LineMesh(Vector3(), Vector3()), m_uiShader);
    shotAimLine->setActive(false);
    balls[0]->addChild(shotAimLine);

    // Init state machine
    static_cast<SnookerStateMachine *>(fsm)->initStates();

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");
    m_physicsLoop = addTimedLoop(8.33f, "physics");
    m_controlLoop = addTimedLoop(25.0f, "control");
    m_profileLoop = addTimedLoop(1000.0f, "profile");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Menu
    menu = new OptionsMenu(this, m_fontMedium, 0.05f);
    menu->setMargin(Vector2(0.005f, 0.005f));
    menu->layout();
    menu->show();
    addEventHandler(menu);

    controls = new SnookerControls(this);

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
      menu->update(dtMilliSec, Subsystem::GRAPHICS);

      swapBuffers();
    }
    // Handle physics
    else if (id == m_physicsLoop)
    {
      physics.update(dtMilliSec);

      // Update state machine if on the wait_for_pocket or sandbox states
      const std::string &fsmLeaf = fsm->activeStateBranch().back()->name();
      if ((fsmLeaf == "wait_for_shot" || fsmLeaf == "sandbox") && fsm->update())
        // The manu text may need updated (since this happens after the physics
        // update it should not affect the simulation)
        menu->updateTextFromState();
    }
    // Handle control
    else if (id == m_controlLoop)
    {
      // Update state machine unless on the sandbox sttae (updating is done in
      // physics loop and must not be done simultaneously)
      if (fsm->activeStateBranch().back()->name() != "sandbox" && fsm->update())
        // The manu text may need updated
        menu->updateTextFromState();

      // Profile display
      m_profileText->setActive(controls->state(S_PROFILE_DISPLAY));

      // Pause
      physics.setRunning(!controls->state(S_PAUSE));
    }
    // Output profiling data
    else if (id == m_profileLoop)
    {
      m_profiler->computeStats(dtMilliSec);

      // If profile data is shown
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
    delete fsm;
    TTF_CloseFont(m_fontLarge);
    TTF_CloseFont(m_fontMedium);
  }

  /**
   * @brief Resets balls to their initial state.
   * @param b Balls to be reset
   *
   * When the _DEBUG macro is defined (default for a debug build in VS) only a
   * subset of balls will be enabled.
   */
  void SnookerSimulation::resetBalls(SnookerBalls b)
  {
    for (size_t i = 0; i < NUM_BALLS; i++)
    {
      // If ball is valid and is selected by the b parameter
      if (balls[i] != nullptr &&
          (b == SnookerBalls::ALL || balls[i]->points() == static_cast<std::underlying_type<SnookerBalls>::type>(b) ||
           (b == SnookerBalls::ALL_COLOURS && balls[i]->points() > 1)))
      {
        balls[i]->reset();
      }
    }
  }

  /**
   * @brief Creates balls and adds them to the simulation.
   */
  void SnookerSimulation::initBalls()
  {
    // Cue ball
    balls[0] = new Ball(Vector2(-1150.0f, 200.0f), -1);

#ifndef _DEBUG
    // Red
    balls[1] = new Ball(Vector2(957.85f, 0.0f), 1);
#else
    balls[1] = new Ball(Vector2(0.0f, -820.0f), 1);
#endif

#ifndef _DEBUG
    // Red
    balls[2] = new Ball(Vector2(1010.35f, 26.25f), 1);
#else
    balls[2] = new Ball(Vector2(-1740.0f, -840.0f), 1);
#endif

#ifndef _DEBUG
    // Reds
    balls[3] = new Ball(Vector2(1010.35f, -26.25f), 1);
    balls[4] = new Ball(Vector2(1062.85f, 52.5f), 1);
    balls[5] = new Ball(Vector2(1062.85f, 0.0f), 1);
    balls[6] = new Ball(Vector2(1062.85f, -52.5f), 1);
    balls[7] = new Ball(Vector2(1115.35f, 78.75f), 1);
    balls[8] = new Ball(Vector2(1115.35f, 26.25f), 1);
    balls[9] = new Ball(Vector2(1115.35f, -26.25f), 1);
    balls[10] = new Ball(Vector2(1115.35f, -78.75f), 1);
    balls[11] = new Ball(Vector2(1167.85f, 105.0f), 1);
    balls[12] = new Ball(Vector2(1167.85f, 52.5f), 1);
    balls[13] = new Ball(Vector2(1167.85f, 0.0f), 1);
    balls[14] = new Ball(Vector2(1167.85f, -52.5f), 1);
    balls[15] = new Ball(Vector2(1167.85f, -105.0f), 1);
#endif

#ifndef _DEBUG
    // Yellow
    balls[16] = new Ball(Vector2(-1047.75f, -291.1f), 2);
#else
    balls[16] = new Ball(Vector2(0.0f, 820.0f), 2);
#endif

#ifndef _DEBUG
    // Green
    balls[17] = new Ball(Vector2(-1047.75f, 291.1f), 3);

    // Brown
    balls[18] = new Ball(Vector2(-1047.75f, 0.0f), 4);

    // Blue
    balls[19] = new Ball(Vector2(0.0f, 0.0f), 5);
#endif

#ifndef _DEBUG
    // Pink
    balls[20] = new Ball(Vector2(895.35f, 0.0f), 6);
#else
    balls[20] = new Ball(Vector2(1704.0f, 840.0f), 6);
#endif

#ifndef _DEBUG
    // Black
    balls[21] = new Ball(Vector2(1466.85f, 0.0f), 7);
#else
    balls[21] = new Ball(Vector2(1740.0f, -840.0f), 7);
#endif

    // Set default states
    resetBalls();

    // Add valid balls to simulation
    for (size_t i = 0; i < NUM_BALLS; i++)
    {
      if (balls[i] != nullptr)
      {
        m_table->addChild(balls[i]);
        physics.addEntity(balls[i]);
      }
    }
  }
}
}