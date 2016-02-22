/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <SphericalEntity.h>

class Ball : public Simulation::Physics::SphericalEntity
{
public:
  Ball(const Engine::Maths::Vector2 &pos);
  virtual ~Ball();
};