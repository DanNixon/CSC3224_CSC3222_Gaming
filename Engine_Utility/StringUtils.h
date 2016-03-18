/**
 * @file
 * @author Dan Nixon
 */

#ifndef _ENGINE_UTILITY_STRINGUTILS_H_
#define _ENGINE_UTILITY_STRINGUTILS_H_

#include <string>

namespace Engine
{
namespace Utility
{
  /**
   * @class StringUtils
   * @brief Utility class for strng manipulation.
   * @author Dan Nixon
   */
  class StringUtils
  {
  public:
    static std::string DirectoryFromPath(const std::string &path);
    static std::string FilenameFromPath(const std::string &path);
  };
}
}

#endif