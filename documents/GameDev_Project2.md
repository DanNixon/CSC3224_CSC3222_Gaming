# Game Development Project (12 May)

RC flight simulator with parametric/randomly generated finite terrains.

## Features

Essential:

- [ ] Parametric terrain (height map) generator
- [x] Controllable 3D helicopter
- [ ] Collision detection with terrain
- [ ] Switchable between LOS and FPV views
- [x] Both mouse + keyboard and joystick controls

Extra:

- [ ] Terrain object generation (trees, buildings, fences, runway, etc.)
- [ ] Weather (wind)
- [ ] Telemetry to TX
- [ ] 3rd person (behind aircraft) view

## Terrain generator

Parameters:

- Size
- Altitude constraint
- Steepness constraint
- Object types
- Object density
- Object placement constraints (fixed per object)

Objects:

- Tree

## Options

Menu:

- Exit
- Pause
- Reset
- Camera
  - Line of Sight
  - First Person View
- UI
  - Show/Hide Telemetry
  - Show/Hide Sticks
- Aircraft
  - (list all models in `models` directory)
- Terrain
  - (list all terrain generator presets)
- Help (show some help/control listing of some sort)
