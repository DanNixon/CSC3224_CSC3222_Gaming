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
  /**
   * @brief Tests if the item at a path exists (can be file, directory or link).
   * @param path Path to item
   * @return Ture if path exists
   */
  bool DiskUtils::Exists(const std::string &path)
  {
    DWORD type = GetFileAttributesA(path.c_str());
    return (type != INVALID_FILE_ATTRIBUTES);
  }

  /**
   * @brief Creates a new diretcory tree.
   * @param path Path to create
   * @return True if path was created
   */
  bool DiskUtils::MakeDirectories(const std::string &path)
  {
    return CreateDirectory(path.c_str(), NULL) == TRUE;
  }
}
}