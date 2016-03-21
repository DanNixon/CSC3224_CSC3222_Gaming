/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_GRAPHICS_BOUNDINGBOX_H_
#define _ENGINE_GRAPHICS_BOUNDINGBOX_H_

namespace Engine
{
  namespace Graphics
  {
    template <class T> class BoundingBox
    {
    public:
      BoundingBox(const T &lowerLeft, const T &upperRight)
        : m_lowerLeft(lowerLeft)
        , m_upperRight(upperRight)
      {
      }

      T lowerLeft() const
      {
        return m_lowerLeft;
      }

      T upperRight() const
      {
        return m_upperRight;
      }

      T size() const
      {
        return m_upperRight - m_lowerLeft;
      }

      bool pointInside(T point) const
      {
        return m_lowerLeft <= point && point <= m_upperRight;
      }

      BoundingBox &operator+=(const T &vector)
      {
        m_lowerLeft += vector;
        m_upperRight += vector;

        return *this;
      }

      BoundingBox &operator-=(const T &vector)
      {
        m_lowerLeft -= vector;
        m_upperRight -= vector;

        return *this;
      }

    private:
      T m_lowerLeft;
      T m_upperRight;
    };
  }
}

#endif