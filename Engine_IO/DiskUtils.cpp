/**
 * @file
 * @author Dan Nixon
 */

#include "DiskUtils.h"

#define NOMINMAX

#include <Windows.h>

namespace Engine
{
namespace IO
{
  bool DiskUtils::Exists(const std::string &path)
  {
    DWORD type = GetFileAttributesA(path.c_str());
    return (type != INVALID_FILE_ATTRIBUTES);
  }

  bool DiskUtils::MakeDirectories(const std::string &path)
  {
    return CreateDirectory(path.c_str(), NULL);
  }

  bool DiskUtils::IsFile(const std::string &path)
  {
    // TODO
    return false;
  }

  bool DiskUtils::IsDirectory(const std::string &path)
  {
    // TODO
    return false;
  }
}
}