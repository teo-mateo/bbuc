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

#include "Types.h"
#pragma once

#include "Image.h"

using namespace System;
using namespace System::Collections;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
	///-------------------------------------------------------------------
	/// ImageListIterator
	///-------------------------------------------------------------------
	public class ImageListIterator
	{
	public:
		std::list<Magick::Image>::iterator iterator;
		bool first;
		bool end;
		ImageListIterator(std::list<Magick::Image>::iterator &iterator_)
		{
			iterator = iterator_;
			first = true;
			end = false;
		}
	};


	///-------------------------------------------------------------------
	/// ImageListEnumerator
	///-------------------------------------------------------------------
	public ref class ImageListEnumerator : public IEnumerator
	{
	internal:
		std::list<Magick::Image> *imageList;
		ImageListIterator *imageListIterator;
	public:
		ImageListEnumerator(std::list<Magick::Image> *imageList_)
		{
			imageList = imageList_;
			imageListIterator = NULL;
			this->Reset();
		}

		// IEnumerator interface
		virtual void Reset() = IEnumerator::Reset;
		property virtual Object^ Current
		{
			virtual Object^ get() = IEnumerator::Current::get;
		}
		virtual bool MoveNext() = IEnumerator::MoveNext;

	};


	///-------------------------------------------------------------------
	/// ImageList
	///-------------------------------------------------------------------
	public ref class ImageList : public IEnumerable
	{
	internal:
		std::list<Magick::Image> *imageList;
		

	public:
		ImageList() { imageList = new std::list<Magick::Image>(); }
		~ImageList() { this->!ImageList(); }
		!ImageList() 
		{ 
			if( imageList!=NULL) 
			{ 
				delete imageList; 
				imageList = NULL; 
			} 
		}
	
		void ReadImages(System::String^ imageSpec);
		void WriteImages(System::String^ imageSpec, bool adjoin_);

		// IEnumerable interface
		virtual IEnumerator^ GetEnumerator() = IEnumerable::GetEnumerator;

		// IList interface
		
	};
}
