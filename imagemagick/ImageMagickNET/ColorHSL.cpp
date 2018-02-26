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

#include "stdafx.h"
#include "ColorHSL.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorHSL::ColorHSL ( double hue_, double saturation_, double luminosity_ )
	{
		color = new Magick::ColorHSL(hue_, saturation_, luminosity_);
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorHSL::ColorHSL ( void )
	{
		color = new Magick::ColorHSL();
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorHSL::ColorHSL ( Color^ color_ )
	{
		color = new Magick::ColorHSL(*(color_->color));
	}
    

	///-------------------------------------------------------------------
	/// Hue
	///-------------------------------------------------------------------
	void           ColorHSL::Hue ( double hue_ )
	{
		((Magick::ColorHSL*)color)->hue(hue_);
	}
    double         ColorHSL::Hue ( void )
	{
		return ((Magick::ColorHSL*)color)->hue();
	}
    
	///-------------------------------------------------------------------
	/// Saturation
	///-------------------------------------------------------------------
    void           ColorHSL::Saturation ( double saturation_ )
	{
		((Magick::ColorHSL*)color)->saturation(saturation_);
	}
    double         ColorHSL::Saturation ( void )
	{
		return ((Magick::ColorHSL*)color)->saturation();
	}
    
	///-------------------------------------------------------------------
	/// Luminosity
	///-------------------------------------------------------------------
    void           ColorHSL::Luminosity ( double luminosity_ )
	{
		((Magick::ColorHSL*)color)->luminosity(luminosity_);
	}
    double         ColorHSL::Luminosity ( void )
	{
		return ((Magick::ColorHSL*)color)->luminosity();
	}

}