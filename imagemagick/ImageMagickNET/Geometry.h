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

#include "Types.h"
#pragma once


using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
	public ref class Geometry
	{
	internal:
		Magick::Geometry*  geometry;
	
	protected:
		~Geometry() { this->!Geometry(); }
		!Geometry() { if( geometry!=NULL ) { delete geometry; geometry = NULL; } }
	
	public:
		// constructors
		Geometry ( );
		Geometry ( 
			unsigned int width_,
			unsigned int height_,
			unsigned int xOff_,
			unsigned int yOff_,
			bool xNegative_,
			bool yNegative_ );
		Geometry ( System::String ^geometry_ );
		Geometry ( Geometry^ geometry_ );
	
		// Width
		void          Width ( unsigned int width_ );
		unsigned int  Width ( void );
	    
		// Height
		void          Height ( unsigned int height_ );
		unsigned int  Height ( void );
	    
		// X offset from origin
		void          XOff ( unsigned int xOff_ );
		unsigned int  XOff ( void );
	    
		// Y offset from origin
		void          YOff ( unsigned int yOff_ );
		unsigned int  YOff ( void );
	    
		// Sign of X offset negative? (X origin at right)
		void          XNegative ( bool xNegative_ );
		bool          XNegative ( void );
	    
		// Sign of Y offset negative? (Y origin at bottom)
		void          YNegative ( bool yNegative_ );
		bool          YNegative ( void );
	    
		// Width and height are expressed as percentages
		void          Percent ( bool percent_ );
		bool          Percent ( void );

		// Resize without preserving aspect ratio (!)
		void          Aspect ( bool aspect_ );
		bool          Aspect ( void );
	    
		// Resize if image is greater than size (>)
		void          Greater ( bool greater_ );
		bool          Greater ( void );
	    
		// Resize if image is less than size (<)
		void          Less ( bool less_ );
		bool          Less ( void );
	    
		// Does object contain valid geometry?
		void          IsValid ( bool isValid_ );
		bool          IsValid ( void );
	};
}
