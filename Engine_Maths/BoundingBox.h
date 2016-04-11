/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_MATHS_BOUNDINGBOX_H_
#define _ENGINE_MATHS_BOUNDINGBOX_H_

#include <algorithm>

#include "Vector2.h"
#include "Vector3.h"

namespace Engine
{
namespace Maths
{
  /**
   * @class BoundingBox
   * @brief Represents an axis aligned bounding box for any number of
   *        dimensions.
   * @author Dan Nixon
   */
  template <class T> class BoundingBox
  {
  public:
    /**
     * @brief Creates a new box with largest possible dimensions.
     * @see BoundingBox::resizeByPoint
     *
     * Intended to be constrained using calls to BoundingBox::resizeByPoint
     */
    BoundingBox()
    {
      reset();
    }

    /**
     * @brief Creates a new box.
     * @param lowerLeft Lower left vertex position
     * @param upperRight Upper right vertex position
     */
    BoundingBox(const T &lowerLeft, const T &upperRight)
        : m_lowerLeft(lowerLeft)
        , m_upperRight(upperRight)
    {
    }

    /**
     * @brief Resets the box to the largest possible dimensions.
     * @see BoundingBox::resizeByPoint
     * @see BoundingBox::resizeByBoundingBox
     *
     * Intended to be constrained using calls to BoundingBox::resizeByPoint
     * or BoundingBox::resizeByBoundingBox
     */
    void reset()
    {
      const float maxFloat = std::numeric_limits<float>::max();
      const float minFloat = std::numeric_limits<float>::lowest();

      for (size_t i = 0; i < T::Dimensions(); i++)
      {
        m_lowerLeft[i] = maxFloat;
        m_upperRight[i] = minFloat;
      }
    }

    /**
     * @brief Resets the box to cover the entire world.
     */
    void world()
    {
      const float maxFloat = std::numeric_limits<float>::max();
      const float minFloat = std::numeric_limits<float>::lowest();

      for (size_t i = 0; i < T::Dimensions(); i++)
      {
        m_lowerLeft[i] = minFloat;
        m_upperRight[i] = maxFloat;
      }
    }

    /**
     * @brief Gets the position of the lower left vertex.
     * @return Lower left vertex
     */
    inline T lowerLeft() const
    {
      return m_lowerLeft;
    }

    /**
     * @brief Gets the position of the upper right vertex.
     * @return Upper right vertex
     */
    inline T upperRight() const
    {
      return m_upperRight;
    }

    /**
     * @brief Gets a vector containing the largest distance from the centre of
     *        the box to its boundary in each axis.
     * @return Largest centre-bounday distance
     */
    T longestBoundDistance() const
    {
      T retVal;

      for (size_t i = 0; i < T::Dimensions(); i++)
      {
        float val = std::max(std::abs(m_lowerLeft[i]), std::abs(m_upperRight[i]));

        if (val > retVal[i])
          retVal[i] = val;
      }

      return retVal;
    }

    /**
     * @brief Gets the dimensions of the bounding box.
     * @return Box dimensions
     */
    inline T size() const
    {
      return m_upperRight - m_lowerLeft;
    }

    /**
     * @brief Tests if a point is inside the bounding box.
     * @param point Point to test
     * @return True if point is inside the box
     */
    inline bool pointInside(const T &point) const
    {
      return m_lowerLeft <= point && point <= m_upperRight;
    }

    /**
     * @brief Constrains the size of the box by a point.
     * @param point Point to resize by
     * @see BoundingBox::reset
     * @see BoundingBox::resizeByBoundingBox
     */
    inline void resizeByPoint(const T &point)
    {
      for (size_t i = 0; i < T::Dimensions(); i++)
      {
        if (point[i] < m_lowerLeft[i])
          m_lowerLeft[i] = point[i];

        else if (point[i] > m_upperRight[i])
          m_upperRight[i] = point[i];
      }
    }

    /**
     * @brief Constrains the size of the box by another bounding box.
     * @param box Box to resize by
     * @see BoundingBox::reset
     * @see BoundingBox::resizeByPoint
     */
    inline void resizeByBoundingBox(const BoundingBox &box)
    {
      for (size_t i = 0; i < T::Dimensions(); i++)
      {
        if (box.m_lowerLeft[i] < m_lowerLeft[i])
          m_lowerLeft[i] = box.m_lowerLeft[i];

        if (box.m_upperRight[i] > m_upperRight[i])
          m_upperRight[i] = box.m_upperRight[i];
      }
    }

    /**
     * @brief Positively offsets the position of the bounding box.
     * @param vector Positional offset
     * @return Moved bounding box
     */
    BoundingBox &operator+=(const T &vector)
    {
      m_lowerLeft += vector;
      m_upperRight += vector;

      return *this;
    }

    /**
     * @brief Negatively offsets the position of the bounding box.
     * @param vector Positional offset
     * @return Moved bounding box
     */
    BoundingBox &operator-=(const T &vector)
    {
      m_lowerLeft -= vector;
      m_upperRight -= vector;

      return *this;
    }

    /**
     * @brief Scales this box by multiplying the position of both vertices by a
     *        common factor.
     * @param f Factor to multiply by
     * @return Scaled box
     */
    BoundingBox &operator*=(float f)
    {
      m_lowerLeft *= f;
      m_upperRight *= f;

      return *this;
    }

  private:
    T m_lowerLeft;  //!< Position of the lower left vertex
    T m_upperRight; //!< Position of the upper right vertex
  };

  /**
   * @typedef BoundingBox2
   * @brief Two dimensional BoundingBox.
   */
  typedef BoundingBox<Vector2> BoundingBox2;

  /**
   * @typedef BoundingBox3
   * @brief Three dimensional BoundingBox.
   */
  typedef BoundingBox<Vector3> BoundingBox3;
}
}

#endif
