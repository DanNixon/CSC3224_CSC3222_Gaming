/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_UTILITY_STRINGUTILS_H_
#define _ENGINE_UTILITY_STRINGUTILS_H_

#include <string>
#include <vector>

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
    static std::string Trim(std::string str, const std::string &trimChars = " \t");
    static std::vector<std::string> Split(const std::string &str, char delim);

    static std::string SanitizeFilename(std::string str);

    static std::string DirectoryFromPath(const std::string &path);
    static std::string FilenameFromPath(const std::string &path);

    static std::string BasenameFromFilename(const std::string &filename);
    static std::string ExtFromFilename(const std::string &filename);

    static bool ToBool(std::string str, bool defaultVal = false);

  private:
    static size_t FindSlash(const std::string &str);
  };
}
}

#endif