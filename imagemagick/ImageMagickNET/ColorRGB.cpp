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
/// ColorRGB class
///=======================================================================

#include "stdafx.h"
#include "ColorRGB.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorRGB::ColorRGB ( double red_, double green_, double blue_ )
	{
		color = new Magick::ColorRGB(red_, green_, blue_);
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
    ColorRGB::ColorRGB ( void )
	{
		color = new Magick::ColorRGB();
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
    ColorRGB::ColorRGB ( Color^ color_ )
	{
		color = new Magick::ColorRGB(*(color_->color));
	}
    
	///-------------------------------------------------------------------
	/// Red
	///-------------------------------------------------------------------
    void           ColorRGB::Red ( double red_ )
	{
		((Magick::ColorRGB*)color)->red(red_);
	}

    double         ColorRGB::Red ( void ) 
	{
		return ((Magick::ColorRGB*)color)->red();
	}
    
	///-------------------------------------------------------------------
	/// Green
	///-------------------------------------------------------------------
    void           ColorRGB::Green ( double green_ )
	{
		((Magick::ColorRGB*)color)->green(green_);
	}
    double         ColorRGB::Green ( void ) 
	{
		return ((Magick::ColorRGB*)color)->green();
	}
    
	///-------------------------------------------------------------------
	/// Blue
	///-------------------------------------------------------------------
    void           ColorRGB::Blue ( double blue_ )
	{
		((Magick::ColorRGB*)color)->blue(blue_);
	}
    double         ColorRGB::Blue ( void ) 
	{
		return ((Magick::ColorRGB*)color)->blue();
	}

}