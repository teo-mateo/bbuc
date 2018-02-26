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
/// Color class
///=======================================================================

#include "stdafx.h"
#include "Color.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Color::Color ( MagickCore::Quantum red_,
		MagickCore::Quantum green_,
		MagickCore::Quantum blue_ )
	{
		color = new Magick::Color(red_, green_, blue_);
	}


	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Color::Color ( MagickCore::Quantum red_,
		MagickCore::Quantum green_,
		MagickCore::Quantum blue_,
		MagickCore::Quantum alpha_ )
	{
		color = new Magick::Color(red_, green_, blue_, alpha_);
	}


	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Color::Color ( System::String^ x11color_ )
	{
		std::string x11colorStr;
		color = new Magick::Color(Marshaller::SystemStringToStdString(x11color_, x11colorStr));
	}


	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Color::Color ( void )
	{
		color = new Magick::Color();
	}


	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Color::Color ( Color^ color_ )
	{
		color = new Magick::Color( *(color_->color) );
	}


	///-------------------------------------------------------------------
    // Red color (range 0 to QuantumRange)
	///-------------------------------------------------------------------
	void           Color::RedQuantum ( MagickCore::Quantum red_ )
	{
		color->redQuantum(red_);
	}
    MagickCore::Quantum        Color::RedQuantum ( void )
	{
		return color->redQuantum();
	}

	///-------------------------------------------------------------------
    // Green color (range 0 to QuantumRange)
	///-------------------------------------------------------------------
    void           Color::GreenQuantum ( MagickCore::Quantum green_ )
	{
		color->greenQuantum();
	}
    MagickCore::Quantum        Color::GreenQuantum ( void )
	{
		return color->greenQuantum();
	}


	///-------------------------------------------------------------------
    // Blue color (range 0 to QuantumRange)
	///-------------------------------------------------------------------
    void           Color::BlueQuantum ( MagickCore::Quantum blue_ )
	{
		color->blueQuantum();
	}
    MagickCore::Quantum        Color::BlueQuantum ( void )
	{
		return color->blueQuantum();
	}

	///-------------------------------------------------------------------
    // Alpha level (range OpaqueOpacity=0 to TransparentOpacity=QuantumRange)
	///-------------------------------------------------------------------
    void           Color::AlphaQuantum ( MagickCore::Quantum alpha_ )
	{
		color->alphaQuantum(alpha_);
	}
    MagickCore::Quantum        Color::AlphaQuantum ( void )
	{
		return color->alphaQuantum();
	}

	///-------------------------------------------------------------------
    // Scaled (to 1.0) version of alpha for use in sub-classes
    // (range opaque=0 to transparent=1.0)
	///-------------------------------------------------------------------
    void           Color::Alpha ( double alpha_ )
	{
		color->alpha(alpha_);
	}
    double         Color::Alpha ( void ) 
	{
		return color->alpha();
	}
        
	///-------------------------------------------------------------------
    // Does object contain valid color?
	///-------------------------------------------------------------------
    void           Color::IsValid ( bool valid_ )
	{
		color->isValid(valid_);
	}
    bool           Color::IsValid ( void ) 
	{
		return color->isValid();
	}
    

}

