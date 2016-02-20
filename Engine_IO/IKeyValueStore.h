/**
 * @file
 * @author Dan Nixon
 */

#pragma once

#include <string>
#include <istream>
#include <ostream>

#include "KVNode.h"

/**
 * @class IKeyValueStore
 * @brief Represents a tree of KVNode each containing a set of key-value pairs.
 * @author Dan Nixon
 */
class IKeyValueStore
{
public:
  /**
   * @brief Create a new data store with an empty root node.
   */
  IKeyValueStore()
  {
  }

  virtual ~IKeyValueStore()
  {
  }

  /**
   * @brief Gets the root node of the data store.
   * @return Root node
   */
  KVNode &root()
  {
    return m_root;
  }

  /**
   * @brief Load the contents of the data store from a stream.
   * @param stream Stream to load from
   * @return True if load was successful
   */
  virtual bool load(std::istream &stream) = 0;

  /**
   * @brief Saves the contents of the data store to a stream.
   * @param stream Stream to output to
   * @return True if save was successful
   */
  virtual bool save(std::ostream &stream) = 0;

protected:
  KVNode m_root; //!< Root node
};
