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
/// ImageList class
///=======================================================================

#include "stdafx.h"
#include "ImageList.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{
	///-------------------------------------------------------------------
	/// Read images into the ImageList container.
	///-------------------------------------------------------------------
	void ImageList::ReadImages(System::String^ imageSpec)
	{
		Magick::readImages( imageList, Marshaller::SystemStringToStdString(imageSpec) ); 
	}


	///-------------------------------------------------------------------
	/// Write images from the ImageList container.
	///-------------------------------------------------------------------
	void ImageList::WriteImages(System::String^ imageSpec, bool adjoin_)
	{
		Magick::writeImages( imageList->begin(), imageList->end(), Marshaller::SystemStringToStdString(imageSpec), adjoin_ ); 
	}

	///-------------------------------------------------------------------
	/// IEnumerable interface
	///-------------------------------------------------------------------
	IEnumerator^ ImageList::GetEnumerator()
	{
		return gcnew ImageListEnumerator(this->imageList);
	}

	///-------------------------------------------------------------------
	/// IEnumerator interface
	///-------------------------------------------------------------------
	void ImageListEnumerator::Reset()
	{
		imageListIterator = new ImageListIterator(imageList->begin());
	}
	
	Object^ ImageListEnumerator::Current::get()
	{
		return gcnew Image(&(*(imageListIterator->iterator)));
	}
	
	bool ImageListEnumerator::MoveNext()
	{
		if( imageListIterator->first )
		{
			imageListIterator->first = false;
			return !imageList->empty();
		}

		imageListIterator->iterator++;
		
		if( (imageListIterator->iterator)==imageList->end() )
		{
			delete imageListIterator;
			System::Console::WriteLine(imageList->size());
			return false;
		}
		
		return true;
	}
}
