/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <inttypes.h>
#include <map>

namespace Engine
{
	namespace Input
	{
		class IController
		{
		public:
			IController();
			virtual ~IController();

      uint64_t state() const;
      bool state(uint64_t s) const;
      
      bool hasAnalog(uint64_t a) const;
      float analog(uint64_t a) const ;

    protected:
      void setState(uint64_t s, bool active);

      std::map<uint64_t, float> m_analogs;

    private:
      uint64_t m_state;
		};
	}
}
