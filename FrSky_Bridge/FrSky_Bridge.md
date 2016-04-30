FrSky Bridge
============

Code to use a Teensy as a bridge between the flight simulator and a FrSky
X8R/X6R to control the simulator via a Taranis.

Supports decoding SBUS and outputting values as an emulated joystick.

Supports updating telemetry values over serial (9600 baud).

Serial protocol is: `A3,A4,I,V,Alt,VSpd;`
