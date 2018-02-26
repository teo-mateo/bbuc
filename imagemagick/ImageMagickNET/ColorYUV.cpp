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
#include "ColorYUV.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	ColorYUV::ColorYUV ( double y_, double u_, double v_ )
	{
		color = new Magick::ColorYUV( y_, u_, v_);
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
    ColorYUV::ColorYUV ( void )
	{
		color = new Magick::ColorYUV();
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
    ColorYUV::ColorYUV ( Color^ color_ )
	{
		color = new Magick::ColorYUV(*(color_->color));
	}
    
	///-------------------------------------------------------------------
	/// U
	///-------------------------------------------------------------------
    void           ColorYUV::U ( double u_ )
	{
		((Magick::ColorYUV*)color)->u(u_);
	}
    double         ColorYUV::U ( void )
	{
		return ((Magick::ColorYUV*)color)->u();
	}
    
	///-------------------------------------------------------------------
	/// V
	///-------------------------------------------------------------------
    void           ColorYUV::V ( double v_ )
	{
		((Magick::ColorYUV*)color)->v(v_);
	}
    double         ColorYUV::V ( void )
	{
		return ((Magick::ColorYUV*)color)->v();
	}

    
	///-------------------------------------------------------------------
	/// Y
	///-------------------------------------------------------------------
    void           ColorYUV::Y ( double y_ )
	{
		((Magick::ColorYUV*)color)->y(y_);
	}
    double         ColorYUV::Y ( void )
	{
		return ((Magick::ColorYUV*)color)->y();
	}
}