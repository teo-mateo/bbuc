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

#include "Types.h"
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{
	public ref class Marshaller 
	{
	private:
		
	protected:
		
	public:
		static System::String^ StdStringToSystemString(const std::string& s);
		static std::string& SystemStringToStdString(System::String^ s, std::string& s2);
		static std::string& SystemStringToStdString(System::String^ s);
	};
}
