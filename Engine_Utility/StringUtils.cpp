/**
 * @file
 * @author Dan Nixon
 */

#include "StringUtils.h"

namespace Engine
{
namespace Utility
{
  /**
   * @breif Gets the directory given the path to a file.
   * @param File path
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
   * @breif Gets the name of a file given a path to it.
   * @param File path
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
   * @breif Gets the base name of a file given its filename.
   * @param Filename
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
   * @breif Gets the extension of a file given its filename.
   * @param Filename
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
   * @breif Searches a string for a directory delimiting slash.
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
