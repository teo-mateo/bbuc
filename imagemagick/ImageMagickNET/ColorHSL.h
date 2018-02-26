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
/// ColorHSL class
///=======================================================================

#pragma once

#include "Types.h"
#include "Color.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
  public ref class ColorHSL : public Color
  {
  public:
    ColorHSL ( double hue_, double saturation_, double luminosity_ );
    ColorHSL ( void );
    ColorHSL ( Color^ color_ );
    
    void           Hue ( double hue_ );
    double         Hue ( void );
    
    void           Saturation ( double saturation_ );
    double         Saturation ( void );
    
    void           Luminosity ( double luminosity_ );
    double         Luminosity ( void );

  };
}
