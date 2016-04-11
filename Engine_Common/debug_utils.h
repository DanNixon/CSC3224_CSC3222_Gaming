/**
 * @file
 * @author Dan Nixon (120263697)
 * @brief Adds the C runtime library for memory leak detection.
 * @see https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx
 *
 * For CSC3224 Project 1.
 */

#ifdef _DEBUG

#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdlib.h>

#endif