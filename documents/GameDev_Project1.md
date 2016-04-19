# Game Development Project 1 (20 Apr)

## To Do

- [x] Engine structure outline
- [x] `Engine_Audio`
  - [x] Context
  - [x] Listener
  - [x] Source
  - [x] Switch to OpenAL Soft
- [x] `Engine_Common`
  - [x] Move setup code into engine
  - [x] Loop timing
  - [x] Clean startup routine
  - [x] Profiling
  - [x] Make `SceneObject::update()` generic for different types of updates
  - [x] Game that holds a configuration
- [x] `Engine_Graphics`
  - [x] Asset import
  - [x] Texture encapsulation
  - [x] Text rendering
  - [x] Render alpha meshes in correct order
  - [x] Load textures in asset loading
  - [x] Multi line text
  - [ ] Light abstraction
- [x] `Engine_Input`
  - [x] Keyboard
  - [x] Mouse
  - [x] Joystick
  - [x] Mapping control structure
- [x] `Engine_IO`
  - [x] INI
- [x] `Engine_Logging`
- [ ] `Engine_Physics`
  - [x] World/simulation representation
  - [x] Body representation
  - [x] Aircraft motion
  - [x] Convex hull collision shape
  - [x] Bounding box collision shape
  - [ ] Heightmap terrain abstraction
- [x] `Engine_ResourceManagment`
  - [x] Managed memory cleanup
- [x] `Engine_UIMenu`
  - [x] Menu structure definition
  - [x] Top bar menu
  - [x] Mouse interaction
  - [x] Simple programatic menu generation
- [x] `Engine_Utility`
  - [x] More random distributions
  - [x] Filesystem string utilities
  - [x] General string utilities

## Physics Notes

- World is scaled by 100
- Lenght in cm
- Time in seconds
- Force in Newtons
- Mass in kg
