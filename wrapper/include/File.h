#pragma once

// File
// Date: 8/03
// Author: Dr. Holly

//-----
#ifdef NDEBUG
//-----

typedef FileBase File;

//-----
#else // compiling in debug mode
//-----

#include "FileChecking.hpp"

typedef FileChecking1<FileBase> File;

//-----
#endif	// NDEBUG
//-----
