/**
 * @file
 * @author Dan Nixon (120263697)
 *
 * For CSC3224 Project 1.
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

  /**
   * @brief Obtains a list of items in a directory.
   * @param path Path to directory to list
   * @param files If names of files should be returned
   * @param directories If names of directories should be returned
   * @param listAll If all (including hidden) items should be shown
   * @return List of item names
   *
   * Adapted from:
   * http://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c/1932861#1932861
   */
  std::vector<std::string> DiskUtils::ListDirectory(const std::string &path, bool files, bool directories, bool listAll)
  {
    std::vector<std::string> retVal;

    HANDLE dir;
    WIN32_FIND_DATA fileData;

    if ((dir = FindFirstFile((path + "/*").c_str(), &fileData)) != INVALID_HANDLE_VALUE)
    {
      do
      {
        const std::string filename = fileData.cFileName;
        const bool isDirectory = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        const bool hiddenMod = filename[0] != '.' || listAll;

        if (directories && isDirectory && hiddenMod)
          retVal.push_back(filename);
        else if (files && hiddenMod)
          retVal.push_back(filename);

      } while (FindNextFile(dir, &fileData));

      FindClose(dir);
    }

    return retVal;
  }
}
}