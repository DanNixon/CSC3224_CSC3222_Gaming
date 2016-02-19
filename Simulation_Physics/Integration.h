/**
 * @file
 * @author Dan Nixon
 */

#pragma once

class Vector3;

/**
 * @class Integration
 * @brief Helper class for performing numerical integration.
 * @author Dan Nixon
 */
class Integration
{
public:
  static void Euler(Vector3 &out, const Vector3 &x, const Vector3 &y, float dT);
};
