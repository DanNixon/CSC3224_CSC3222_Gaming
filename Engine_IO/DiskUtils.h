/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
 */

#ifndef _ENGINE_IO_DISKUTILS_H_
#define _ENGINE_IO_DISKUTILS_H_

#include <string>
#include <vector>

namespace Engine
{
namespace IO
{
  /**
   * @class DiskUtils
   * @brief Contains utility functions for performing filesystem operations.
   * @author Dan Nixon
   */
  class DiskUtils
  {
  public:
    static bool Exists(const std::string &path);
    static bool MakeDirectories(const std::string &path);
    static std::vector<std::string> ListDirectory(const std::string &path, bool files = true, bool directories = true,
                                                  bool listAll = false);
  };
}
}

#endif
