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
/// ColorYUV class
///=======================================================================

#pragma once

#include "Types.h"
#include "Color.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
  public ref class ColorYUV : public Color
  {
  public:
    ColorYUV ( double y_, double u_, double v_ );
    ColorYUV ( void );
    ColorYUV ( Color^ color_ );
    
    void           U ( double u_ );
    double         U ( void ) ;
    
    void           V ( double v_ );
    double         V ( void ) ;
    
    void           Y ( double y_ );
    double         Y ( void ) ;

  };
}
