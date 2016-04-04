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

using namespace Engine::Common;
using namespace Engine::Graphics;
using namespace Engine::Maths;
using namespace Engine::Input;
using namespace Simulation::Physics;

namespace Simulation
{
namespace Snooker
{
  SnookerSimulation::SnookerSimulation()
      : Game("Snooker Loopy", std::make_pair(1024, 768))
      , m_mouseStartPosition(nullptr)
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
    // Load font for text display
    m_fontLarge = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 45);
    m_fontMedium = TTF_OpenFont("../resources/open-sans/OpenSans-Regular.ttf", 20);

    // Table
    m_table = new Table(m_entities);
    m_table->setModelMatrix(Matrix4::Translation(Vector3(0.0, 0.0, -3600.0)));

    // Balls
    m_balls[0] = new Ball(Vector2(-1150.0f, 200.0f), -1);   // Cue ball
    m_balls[1] = new Ball(Vector2(957.85f, 0.0f), 1);       // Red
    m_balls[2] = new Ball(Vector2(1010.35f, 26.25f), 1);    // Red
    m_balls[3] = new Ball(Vector2(1010.35f, -26.25f), 1);   // Red
    m_balls[4] = new Ball(Vector2(1062.85f, 52.5f), 1);     // Red
    m_balls[5] = new Ball(Vector2(1062.85f, 0.0f), 1);      // Red
    m_balls[6] = new Ball(Vector2(1062.85f, -52.5f), 1);    // Red
    m_balls[7] = new Ball(Vector2(1115.35f, 78.75f), 1);    // Red
    m_balls[8] = new Ball(Vector2(1115.35f, 26.25f), 1);    // Red
    m_balls[9] = new Ball(Vector2(1115.35f, -26.25f), 1);   // Red
    m_balls[10] = new Ball(Vector2(1115.35f, -78.75f), 1);  // Red
    m_balls[11] = new Ball(Vector2(1167.85f, 105.0f), 1);   // Red
    m_balls[12] = new Ball(Vector2(1167.85f, 52.5f), 1);    // Red
    m_balls[13] = new Ball(Vector2(1167.85f, 0.0f), 1);     // Red
    m_balls[14] = new Ball(Vector2(1167.85f, -52.5f), 1);   // Red
    m_balls[15] = new Ball(Vector2(1167.85f, -105.0f), 1);  // Red
    m_balls[16] = new Ball(Vector2(-1047.75f, -291.1f), 2); // Yellow
    m_balls[17] = new Ball(Vector2(-1047.75f, 291.1f), 3);  // Green
    m_balls[18] = new Ball(Vector2(-1047.75f, 0.0f), 4);    // Brown
    m_balls[19] = new Ball(Vector2(0.0f, 0.0f), 5);         // Blue
    m_balls[20] = new Ball(Vector2(895.35f, 0.0f), 6);      // Pink
    m_balls[21] = new Ball(Vector2(1466.85f, 0.0f), 7);     // Black

    for (size_t i = 0; i < NUM_BALLS; i++)
    {
      if (m_balls[i] != nullptr)
      {
        m_table->addChild(m_balls[i]);
        m_entities.push_back(m_balls[i]);
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

    m_profileGraphics = new TextPane("graphics_profile", 0.05f, m_uiShader, m_fontMedium);
    m_profileGraphics->setActive(false);
    m_profileGraphics->setModelMatrix(Matrix4::Translation(Vector3(-0.5f, 0.8f, 0.0f)));
    m_profileGraphics->setText("Graphics: ");
    m_ui->root()->addChild(m_profileGraphics);

    m_profilePhysics = new TextPane("physics_profile", 0.05f, m_uiShader, m_fontMedium);
    m_profilePhysics->setActive(false);
    m_profilePhysics->setModelMatrix(Matrix4::Translation(Vector3(-0.5f, 0.75f, 0.0f)));
    m_profilePhysics->setText("Physics: ");
    m_ui->root()->addChild(m_profilePhysics);

    m_shotAimLine = new RenderableObject("aim_line", new LineMesh(Vector3(), Vector3()), m_uiShader);
    m_shotAimLine->setActive(false);
    m_balls[0]->addChild(m_shotAimLine);

    // Timed loops
    m_graphicsLoop = addTimedLoop(16.66f, "graphics");
    m_physicsLoop = addTimedLoop(8.33f, "physics");
    m_controlLoop = addTimedLoop(25.0f, "control");
    m_profileLoop = addTimedLoop(1000.0f, "profile");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    m_controls = new SnookerControls(this);

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

      swapBuffers();
    }
    // Handle physics
    else if (id == m_physicsLoop)
    {
      m_physics.update(m_entities, dtMilliSec);

      // Check for potted balls
      auto inters = m_physics.interfaces();
      for (auto it = inters.begin(); it != inters.end(); ++it)
      {
        Entity *a = it->entityA();
        Entity *b = it->entityB();

        if (dynamic_cast<Pocket *>(a))
          std::cout << dynamic_cast<Ball *>(b)->name() << " potted." << std::endl;
        if (dynamic_cast<Pocket *>(b))
          std::cout << dynamic_cast<Ball *>(a)->name() << " potted." << std::endl;
      }
    }
    // Handle control
    else if (id == m_controlLoop)
    {
      updateControl();
    }
    // Output profiling data
    else if (id == m_profileLoop)
    {
      m_profiler->computeStats(dtMilliSec);

      if (m_controls->state(S_PROFILE_DISPLAY))
      {
        std::stringstream graphStr;
        graphStr.precision(3);
        graphStr << "Graphics: " << m_profiler->frameRate(m_graphicsLoop) << " FPS"
                 << " (" << m_profiler->averageDuration(m_graphicsLoop) << "ms)";
        m_profileGraphics->setText(graphStr.str());

        std::stringstream physStr;
        physStr.precision(3);
        physStr << "Physics: " << m_profiler->frameRate(m_physicsLoop) << " FPS"
                << " (" << m_profiler->averageDuration(m_physicsLoop) << "ms)";
        m_profilePhysics->setText(physStr.str());
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
   * @brief Update the controls.
   */
  void SnookerSimulation::updateControl()
  {
    m_profileGraphics->setActive(m_controls->state(S_PROFILE_DISPLAY));
    m_profilePhysics->setActive(m_controls->state(S_PROFILE_DISPLAY));

    if (m_mouseStartPosition == nullptr)
    {
      if (m_controls->state(S_TAKE_SHOT))
      {
        // Record starting position of mouse
        m_mouseStartPosition = new Vector2(m_controls->analog(A_MOUSE_X), m_controls->analog(A_MOUSE_Y));

        // TODO
        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        m_scene->viewMatrix().toGLdoubleMtx(modelview);
        m_scene->projectionMatrix().toGLdoubleMtx(projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        winX = m_mouseStartPosition->x();
        winY = viewport[3] - m_mouseStartPosition->y();
        glReadPixels(int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        Vector3 pos(posX, posY, posZ);

        std::cout << "MOUSE DOWN" << std::endl
                  << "screen: " << *m_mouseStartPosition << std::endl
                  << "world: " << pos << "   " << winZ << std::endl
                  << std::endl;

        static_cast<LineMesh *>(m_shotAimLine->mesh())->setTo(Vector3());
        m_shotAimLine->setActive(true);
      }
      else
      {
        m_balls[0]->setAcceleration(Vector2());
      }
    }
    else
    {
      Vector2 newMousePosition = Vector2(m_controls->analog(A_MOUSE_X), m_controls->analog(A_MOUSE_Y));
      Vector2 deltaMouse = *m_mouseStartPosition - newMousePosition;

      // Clamp max acceleration to a sensible level
      float maxShotMagnitude = 0.5f;
      if (deltaMouse.length2() > (maxShotMagnitude * maxShotMagnitude))
        deltaMouse = VectorOperations::GetNormalised(deltaMouse) * maxShotMagnitude;

      if (!m_controls->state(S_TAKE_SHOT))
      {
        m_shotAimLine->setActive(false);

        std::cout << "MOUSE UP" << std::endl << "delta mouse: " << deltaMouse << std::endl << std::endl;

        m_balls[0]->setAcceleration(deltaMouse);

        delete m_mouseStartPosition;
        m_mouseStartPosition = nullptr;
      }
      else
      {
        static_cast<LineMesh *>(m_shotAimLine->mesh())->setTo(deltaMouse * 1000.0f);
      }
    }
  }
}
}