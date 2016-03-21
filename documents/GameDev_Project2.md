# Game Development Project (12 May)

RC flight simulator with parametric/randomly generated finite terrains.

## Features

Essential:

- [ ] Parametric terrain (height map) generator
- [ ] Controllable 3D helicopter
- [ ] Collision detection with terrain
- [ ] Basic wind
- [ ] Switchable between LOS and FPV views
- [ ] Both mouse + keyboard and joystick controls

Extra:

- [ ] Proper Doppler corrected audio
- [ ] Terrain object generation (trees, buildings, fences, runway, etc.)
- [ ] Weather
- [ ] Telemetry to TX
- [ ] Training modes (hover in box, linear flight, circle, etc.)
- [ ] 3rd person (behind aircraft) view
- [ ] Multirotors
- [ ] Fixed wings

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
- Simulation
  - Pause
  - Reset
  - Speed?
- Aircraft
  - (list all models in `models` directory)
- Terrain
  - (list all terrain generator presets)
- Help (show some help/control listing of some sort)

Config file:

- Terrain generator
  - (presets)
- Telemetry
  - Protocol
  - COM port
