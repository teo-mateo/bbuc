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
/// ColorMono class
///=======================================================================

#pragma once

#include "Types.h"
#include "Color.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
  public ref class ColorMono : public Color
  {
  public:
    ColorMono ( bool mono_ );
    ColorMono ( void );
    ColorMono ( Color^ color_ );
    
    void           Mono ( bool mono_ );
    bool           Mono ( void ) ;

  };
}
