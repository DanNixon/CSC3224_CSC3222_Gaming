/**
 * @file
 * @author Dan Nixon
 */

#include "StringUtils.h"

#include <sstream>

namespace Engine
{
namespace Utility
{
  /**
   * @brief Trims specified characters from the start and end of a string.
   * @param str String to trim
   * @param trinChars String containing characters to trim
   * @return Trimmed string
   */
  std::string StringUtils::Trim(std::string str, const std::string &trimChars)
  {
    size_t pos;

    // Trim from end
    pos = str.find_last_not_of(trimChars);
    if (pos != std::string::npos)
      str = str.substr(0, pos + 1);

    // Trim from start
    pos = str.find_first_not_of(trimChars);
    if (pos != std::string::npos)
      str = str.substr(pos);

    return str;
  }

  /**
   * @brief Splits a string by a delimiter.
   * @param str String to split
   * @param delim Delimiter
   * @return Vector of substrings
   */
  std::vector<std::string> StringUtils::Split(const std::string &str, char delim)
  {
    std::vector<std::string> retVal;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
    {
      if (!item.empty())
        retVal.push_back(item);
    }

    return retVal;
  }

  /**
   * @brief Gets the directory given the path to a file.
   * @param path File path
   * @return Directory to file
   *
   * e.g. DirectoryFromPath("c:\stuff\thing.txt") = "c:\stuff"
   */
  std::string StringUtils::DirectoryFromPath(const std::string &path)
  {
    std::string retVal;
    size_t slashIdx = findSlash(path);

    if (slashIdx != std::string::npos)
      retVal = path.substr(0, slashIdx);

    return retVal;
  }

  /**
   * @brief Gets the name of a file given a path to it.
   * @param path File path
   * @return Filename
   *
   * e.g. FilenameFromPath("c:\stuff\thing.txt") = "thing.txt"
   */
  std::string StringUtils::FilenameFromPath(const std::string &path)
  {
    std::string retVal;
    size_t slashIdx = findSlash(path);

    if (slashIdx != std::string::npos)
      retVal = path.substr(slashIdx + 1);

    return retVal;
  }

  /**
   * @brief Gets the base name of a file given its filename.
   * @param filename Filename
   * @return Base name
   *
   * e.g. BasenameFromFilename("thing.txt") = "thing"
   */
  std::string StringUtils::BasenameFromFilename(const std::string &filename)
  {
    std::string retVal;
    size_t dotIdx = filename.rfind('.');

    if (dotIdx != std::string::npos)
      retVal = filename.substr(0, dotIdx);
    else
      retVal = filename;

    return retVal;
  }

  /**
   * @brief Gets the extension of a file given its filename.
   * @param filename Filename
   * @return Extension
   *
   * e.g. ExtFromFilename("thing.txt") = "txt"
   */
  std::string StringUtils::ExtFromFilename(const std::string &filename)
  {
    std::string retVal;
    size_t dotIdx = filename.rfind('.');

    if (dotIdx != std::string::npos)
      retVal = filename.substr(dotIdx + 1);

    return retVal;
  }

  /**
   * @brief Searches a string for a directory delimiting slash.
   * @param str String to search in
   * @return Index of slash
   *
   * First searches for Windows style slashes (\) then, if none are found, UNIX style (/).
   */
  size_t StringUtils::findSlash(const std::string &str)
  {
    // Look for Windows style slashes
    size_t slashIdx = str.rfind('\\');

    // If not found look for UNIX style
    if (slashIdx == std::string::npos)
      slashIdx = str.rfind('/');

    return slashIdx;
  }
}
}
