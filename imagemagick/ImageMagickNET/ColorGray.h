///=======================================================================
/// ImageMagick .NET Wrapper
///	is
/// Copyright (C) 20Price ApS 2007,  www.20prices.com
/// Free to use for non-commercial purposes
///
/// NOTICE:
/// ImageMagick, its logo and it source codes are
/// Copyright 1999-2007 ImageMagick Studio LLC
/// Please refer to http://www.imagemagick.org/script/license.php
/// for details.
/// 
/// ColorGray class
///=======================================================================

#pragma once

#include "Types.h"
#include "Color.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
  public ref class ColorGray : public Color
  {
  public:
    ColorGray ( double shade_ );
    ColorGray ( void );
    ColorGray ( Color^ color_ );

    void           Shade ( double shade_ );
    double         Shade ( void );
  };
}
