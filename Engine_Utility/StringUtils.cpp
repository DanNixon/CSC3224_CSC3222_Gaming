/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#include "StringUtils.h"

#include <algorithm>
#include <sstream>

namespace Engine
{
namespace Utility
{
  /**
   * @brief Trims specified characters from the start and end of a string.
   * @param str String to trim
   * @param trimChars String containing characters to trim
   * @return Trimmed string
   */
  std::string StringUtils::Trim(std::string str, const std::string &trimChars)
  {
    size_t posStart, posEnd;

    // Trim from end
    posEnd = str.find_last_not_of(trimChars);
    if (posEnd != std::string::npos)
      str = str.substr(0, posEnd + 1);

    // Trim from start
    posStart = str.find_first_not_of(trimChars);
    if (posStart != std::string::npos)
      str = str.substr(posStart);

    if (posStart != std::string::npos && posEnd != std::string::npos)
      return str;
    else
      return std::string();
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
   * @brief Converts a string into a string that can be a filename/path by
   *        removing whitespace and punctuation.
   * @param str String to sanitize
   * @return Sanitized string
   *
   * e.g. SanitizeFilename("Snooker Loopy!") = "SnookerLoopy"
   */
  std::string StringUtils::SanitizeFilename(std::string str)
  {
    str.erase(std::remove_if(str.begin(), str.end(), [](const char &c) { return ispunct(c) || isspace(c); }),
              str.end());
    return str;
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
    size_t slashIdx = FindSlash(path);

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
    size_t slashIdx = FindSlash(path);

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
   * @brief Coverts a string value to a boolean.
   * @param str String value
   * @param defaultVal If string could not be parsed this value is returned
   * @return Parsed value, defaultValue if value could not be determined
   */
  bool StringUtils::ToBool(std::string str, bool defaultVal)
  {
    bool retVal = defaultVal;

    // Make string lowercase
    std::transform(str.begin(), str.end(), str.begin(), tolower);

    // List of words that correspond to true or false
    static const std::vector<std::string> trueStrs = {"1", "true", "yes", "on", "enable"};
    static const std::vector<std::string> falseStrs = {"0", "false", "no", "off", "disable"};

    // Test for a true value
    if (std::find(trueStrs.begin(), trueStrs.end(), str) != trueStrs.end())
      retVal = true;
    // Test for a false value
    else if (std::find(falseStrs.begin(), falseStrs.end(), str) != falseStrs.end())
      retVal = false;

    return retVal;
  }

  /**
   * @brief Searches a string for a directory delimiting slash.
   * @param str String to search in
   * @return Index of slash
   *
   * First searches for Windows style slashes (\) then, if none are found, UNIX style (/).
   */
  size_t StringUtils::FindSlash(const std::string &str)
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
