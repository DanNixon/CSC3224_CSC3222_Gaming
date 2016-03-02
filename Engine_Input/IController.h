/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include "IControlScheme.h"

namespace Engine
{
	namespace Input
	{
		class IController
		{
		public:
      IController(IControlScheme * parent)
        : m_controlScheme(parent)
      {
      }

      virtual ~IController()
      {
      }

    protected:
      IControlScheme * m_controlScheme;
		};
	}
}
