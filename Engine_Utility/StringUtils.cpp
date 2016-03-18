/**
 * @file
 * @author Dan Nixon
 */

#include "StringUtils.h"

namespace Engine
{
namespace Utility
{
  std::string StringUtils::DirectoryFromPath(const std::string &path)
  {
    std::string retVal;
    size_t slashIdx = findSlash(path);

    if (slashIdx != std::string::npos)
      retVal = path.substr(0, slashIdx);

    return retVal;
  }

  std::string StringUtils::FilenameFromPath(const std::string &path)
  {
    std::string retVal;
    size_t slashIdx = findSlash(path);
    
    if (slashIdx != std::string::npos)
      retVal = path.substr(slashIdx + 1);

    return retVal;
  }

  std::string StringUtils::BasenameFromFilename(const std::string &path)
  {
    std::string retVal;
    size_t dotIdx = path.rfind('.');

    if (dotIdx != std::string::npos)
      retVal = path.substr(0, dotIdx);

    return retVal;
  }

  std::string StringUtils::ExtFromFilename(const std::string &path)
  {
    std::string retVal;
    size_t dotIdx = path.rfind('.');

    if (dotIdx != std::string::npos)
      retVal = path.substr(dotIdx + 1);

    return retVal;
  }

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
