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
     * @brief Gets the position of the lower left vertex.
     * @return Lower left vertex
     */
    T lowerLeft() const
    {
      return m_lowerLeft;
    }

    /**
     * @brief Gets the position of the upper right vertex.
     * @return Upper right vertex
     */
    T upperRight() const
    {
      return m_upperRight;
    }

    /**
     * @brief Gets the dimensions of the bounding box.
     * @return Box dimensions
     */
    T size() const
    {
      return m_upperRight - m_lowerLeft;
    }

    /**
     * @brief Tests if a point is inside the bounding box.
     * @param point Point to test
     * @return True if point is inside the box
     */
    bool pointInside(T point) const
    {
      return m_lowerLeft <= point && point <= m_upperRight;
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
}
}

#endif
