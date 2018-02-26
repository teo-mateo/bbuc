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
/// Geometry class
///=======================================================================

#include "stdafx.h"
#include "Geometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Geometry::Geometry ( )
	{
		geometry = new Magick::Geometry();
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Geometry::Geometry ( 
		unsigned int width,
		unsigned int height,
		unsigned int xOff,
		unsigned int yOff,
		bool xNegative,
		bool yNegative )
	{
		geometry = new Magick::Geometry(width, height, xOff, yOff, xNegative, yNegative);
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Geometry::Geometry ( System::String^ pGeometry )
	{
		std::string geometryStr;
		geometry = new Magick::Geometry(
			Marshaller::SystemStringToStdString(pGeometry, geometryStr));
	}

	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Geometry::Geometry ( Geometry^ pGeometry )
	{
		geometry = new Magick::Geometry(*(pGeometry->geometry));
	}


	///-------------------------------------------------------------------
	// Width
	///-------------------------------------------------------------------
	void          Geometry::Width ( unsigned int width_ )
	{
		geometry->width( width_ );
	}

	unsigned int  Geometry::Width ( void )
	{
		return geometry->width();
	}
    
	///-------------------------------------------------------------------
	// Height
	///-------------------------------------------------------------------
	void          Geometry::Height ( unsigned int height_ )
	{
		geometry->height( height_ );
	}

	unsigned int  Geometry::Height ( void )
	{
		return geometry->height();
	}
    
	///-------------------------------------------------------------------
	// X offset from origin
	///-------------------------------------------------------------------
	void          Geometry::XOff ( unsigned int xOff_ )
	{
		geometry->xOff( xOff_ );
	}

	unsigned int  Geometry::XOff ( void )
	{
		return geometry->xOff();
	}
    
	///-------------------------------------------------------------------
	// Y offset from origin
	///-------------------------------------------------------------------
	void          Geometry::YOff ( unsigned int yOff_ )
	{
		geometry->yOff( yOff_ );
	}

	unsigned int  Geometry::YOff ( void )
	{
		return geometry->yOff();
	}
    
	///-------------------------------------------------------------------
	// Sign of X offset negative? (X origin at right)
	///-------------------------------------------------------------------
	void          Geometry::XNegative ( bool xNegative_ )
	{
		geometry->xNegative( xNegative_ );
	}

	bool          Geometry::XNegative ( void )
	{
		return geometry->xNegative();
	}

    
	///-------------------------------------------------------------------
	// Sign of Y offset negative? (Y origin at bottom)
	///-------------------------------------------------------------------
	void          Geometry::YNegative ( bool yNegative_ )
	{
		geometry->yNegative( yNegative_ );
	}

	bool          Geometry::YNegative ( void )
	{
		return geometry->yNegative();
	}
    
	///-------------------------------------------------------------------
	// Width and height are expressed as percentages
	///-------------------------------------------------------------------
	void          Geometry::Percent ( bool percent_ )
	{
		geometry->percent( percent_ );
	}

	bool          Geometry::Percent ( void )
	{
		return geometry->percent();
	}


	///-------------------------------------------------------------------
	// Resize without preserving aspect ratio (!)
	///-------------------------------------------------------------------
	void          Geometry::Aspect ( bool aspect_ )
	{
		geometry->aspect( aspect_ );
	}

	bool          Geometry::Aspect ( void )
	{
		return geometry->aspect();
	}
    
	///-------------------------------------------------------------------
	// Resize if image is greater than size (>)
	///-------------------------------------------------------------------
	void          Geometry::Greater ( bool greater_ )
	{
		geometry->greater( greater_ );
	}
	bool          Geometry::Greater ( void )
	{
		return geometry->greater();
	}
    
	///-------------------------------------------------------------------
	// Resize if image is less than size (<)
	///-------------------------------------------------------------------
	void          Geometry::Less ( bool less_ )
	{
		geometry->less( less_ );
	}

	bool          Geometry::Less ( void )
	{
		return geometry->less();
	}
    
	///-------------------------------------------------------------------
	// Does object contain valid geometry?
	///-------------------------------------------------------------------
	void          Geometry::IsValid ( bool isValid_ )
	{
		geometry->isValid( isValid_ );
	}
	bool          Geometry::IsValid ( void )
	{
		return geometry->isValid();
	}

}