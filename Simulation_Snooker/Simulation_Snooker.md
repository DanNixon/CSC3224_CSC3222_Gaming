Snooker Simulation
==================

For CSC3222 project 1.

The simulator has two modes: sandbox and game.

In sandbox mode the simulation runs and allows shots on the cue ball to be
taken by clicking and dragging, the acceleration vector that will be applied
to the cue ball is shows as a black line with one end at the centre of the cue
ball.

When balls collide with pockets they are thereafter ignored by the simulation
until it is reset (key R or via menu).

Game mode is turn by turn game of snooker between two human players.

When built in Release mode all balls are present in the standard snooker
layout. When built in Debug more only a small subset of balls are present,
this is to allow easier testing of the state machine that runs the game mode.