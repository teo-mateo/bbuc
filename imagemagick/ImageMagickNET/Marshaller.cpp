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
/// Marshaller class mainly for marshaling of strings
///=======================================================================

#include "stdafx.h"
#include "Marshaller.h"

namespace ImageMagickNET
{
	int stringPoolCounter = 0;
	std::string strings[8]; 

	///-------------------------------------------------------------------
	/// Converts a STL string to a CLR string.
	///
	/// When the conversion is complete, returns the CLR string to the
	/// caller.
	///-------------------------------------------------------------------
	System::String^ Marshaller::StdStringToSystemString(const std::string& s)
	{
		return gcnew System::String(s.c_str());
	}

	///-------------------------------------------------------------------
	/// Converts a CLR string to a STL string.
	///
	/// When the conversion completes, returns the STL string through the
	/// referenced parameter s2.
	///-------------------------------------------------------------------
	std::string& Marshaller::SystemStringToStdString(System::String^ s, std::string &s2)
	{
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		s2 = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
		return s2;
	}


	///-------------------------------------------------------------------
	/// Converts a CLR string to a STL string, using a pool of internally
	/// declared strings (up to 8 of them)
	///-------------------------------------------------------------------
	std::string& Marshaller::SystemStringToStdString(System::String^ s)
	{
		int c = stringPoolCounter;
		stringPoolCounter = (stringPoolCounter+1) % 8;
		return Marshaller::SystemStringToStdString(s, strings[c]);

		
	}
}
