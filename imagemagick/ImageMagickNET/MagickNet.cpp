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
/// MagickNet class
///
/// Global class for accessing any global functions
///=======================================================================

#include "stdafx.h"
#include "MagickNet.h"

namespace ImageMagickNET 
{
	
	///-------------------------------------------------------------------
	/// Initializes the ImageMagick library.
	///-------------------------------------------------------------------
	void MagickNet::InitializeMagick(String^ path) 
	{
		IntPtr sTmp = Marshal::StringToHGlobalAnsi(path);
		Magick::InitializeMagick((char*)sTmp.ToPointer());
		Marshal::FreeHGlobal(sTmp);
	}

	void MagickNet::InitializeMagick() 
	{
	}
}
