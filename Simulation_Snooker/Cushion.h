/**
* @file
* @author Dan Nixon
*/

#pragma once

#include <PlanarEntity.h>

class Cushion : public Simulation::Physics::PlanarEntity
{
public:
  Cushion(const Engine::Maths::Vector2 &pos);
  virtual ~Cushion();
};