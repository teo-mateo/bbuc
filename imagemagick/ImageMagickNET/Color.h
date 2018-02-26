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

#pragma once

#include "Types.h"
#include "Color.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
	public ref class Color
	{
	internal:
		Magick::Color*  color;
	
	protected:
		~Color() { this->!Color(); }
		!Color() { if( color!=NULL ) { delete color; color = NULL; } }
	
	public:
		// constructors
		Color ( MagickCore::Quantum red_,
			MagickCore::Quantum green_,
			MagickCore::Quantum blue_ );
		Color ( MagickCore::Quantum red_,
			MagickCore::Quantum green_,
			MagickCore::Quantum blue_,
			MagickCore::Quantum alpha_ );
		Color ( System::String^ x11color_ );
		Color ( void );
		Color ( Color^ color_ );
	
    // Red color (range 0 to QuantumRange)
    void           RedQuantum ( MagickCore::Quantum red_ );
    MagickCore::Quantum        RedQuantum ( void );

    // Green color (range 0 to QuantumRange)
    void           GreenQuantum ( MagickCore::Quantum green_ );
    MagickCore::Quantum        GreenQuantum ( void );

    // Blue color (range 0 to QuantumRange)
    void           BlueQuantum ( MagickCore::Quantum blue_ );
    MagickCore::Quantum        BlueQuantum ( void );

    // Alpha level (range OpaqueOpacity=0 to TransparentOpacity=QuantumRange)
    void           AlphaQuantum ( MagickCore::Quantum alpha_ );
    MagickCore::Quantum        AlphaQuantum ( void );

    // Scaled (to 1.0) version of alpha for use in sub-classes
    // (range opaque=0 to transparent=1.0)
    void           Alpha ( double alpha_ );
    double         Alpha ( void );
        
    // Does object contain valid color?
    void           IsValid ( bool valid_ );
    bool           IsValid ( void );
    
    // Obtain pixel intensity as a double
    double Intensity ( void )
      {
        return color->intensity();;
      }

    // Scale a value expressed as a double (0-1) to Quantum range (0-QuantumRange)
	static MagickCore::Quantum ScaleDoubleToQuantum( double double_ )
      {
		  return Magick::Color::scaleDoubleToQuantum(double_);
      }

    // Scale a value expressed as a Quantum (0-QuantumRange) to double range (0-1)
    static double ScaleQuantumToDouble( MagickCore::Quantum quantum_ )
      {
		  return Magick::Color::scaleQuantumToDouble(quantum_);
      }
    static double ScaleQuantumToDouble( double quantum_ )
      {
		  return Magick::Color::scaleQuantumToDouble(quantum_);
      }

	};
}
