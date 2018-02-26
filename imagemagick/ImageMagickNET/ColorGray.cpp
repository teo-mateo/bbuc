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

#include "stdafx.h"
#include "ColorGray.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorGray::ColorGray ( double shade_ )
	{
		color = new Magick::ColorGray(shade_);
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorGray::ColorGray ( void )
	{
		color = new Magick::ColorGray();
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorGray::ColorGray ( Color^ color_ )
	{
		color = new Magick::ColorGray(*(color_->color));
	}

	///-------------------------------------------------------------------
	/// Shade
	///-------------------------------------------------------------------
    void           ColorGray::Shade ( double shade_ )
	{
		((Magick::ColorGray*)color)->shade(shade_);
	}

	double         ColorGray::Shade ( void )
	{
		return ((Magick::ColorGray*)color)->shade();
	}

}