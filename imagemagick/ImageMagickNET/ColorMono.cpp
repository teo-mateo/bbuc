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

#include "stdafx.h"
#include "ColorMono.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorMono::ColorMono ( bool mono_ )
	{
		color = new Magick::ColorMono(mono_);
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
    ColorMono::ColorMono ( void )
	{
		color = new Magick::ColorMono();
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
    ColorMono::ColorMono ( Color^ color_ )
	{
		color = new Magick::ColorMono(*(color_->color));
	}
    
	///-------------------------------------------------------------------
	/// Mono
	///-------------------------------------------------------------------
    void           ColorMono::Mono ( bool mono_ )
	{
		((Magick::ColorMono*)color)->mono(mono_);
	}

    bool           ColorMono::Mono ( void ) 
	{
		return ((Magick::ColorMono*)color)->mono();
	}
}