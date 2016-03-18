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

    // Look for Windows style slashes
    size_t slashIdx = path.rfind('\\');

    // If not found look for UNIX style
    if (slashIdx == std::string::npos)
      slashIdx = path.rfind('/');

    if (slashIdx != std::string::npos)
      retVal = path.substr(0, slashIdx);

    return retVal;
  }

  std::string StringUtils::FilenameFromPath(const std::string &path)
  {
    std::string retVal;

    // TODO

    return retVal;
  }
}
}
