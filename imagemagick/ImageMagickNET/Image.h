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
/// Image class
///=======================================================================

#include "Types.h"
#pragma once

#include "Color.h"
#include "Geometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{ 
	public ref class Image
	{
		bool isReferenceOnly;
		Magick::Image*  image;

	internal:
		Image(Magick::Image *image_);

	protected:
		~Image() { this->!Image(); }
		!Image() 
		{ 
			if( image!=NULL && !isReferenceOnly ) 
			{ 
				delete image; 
				image = NULL; 
			} 
		}
	
	public:
		Image();
		Image(Image^ image);
		Image(System::String^ imageSpec);


		//----------------------------------------------------------------
		// methods
		//----------------------------------------------------------------

		// Local adaptive threshold image
		// http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm
		// Width x height define the size of the pixel neighborhood
		// offset = constant to subtract from pixel neighborhood mean
		void            AdaptiveThreshold ( unsigned int width,
											unsigned int height,
											unsigned offset );

		// Add noise to image with specified noise type
		void            AddNoise ( NoiseType noiseType_ );

		// Annotate using specified text, and placement location
		void            Annotate ( System::String^ text_,
									Geometry^ location_ );
		// Annotate using specified text, bounding area, and placement
		// gravity
		void            Annotate ( System::String^ text_,
									Geometry^ boundingArea_,
									GravityType gravity_ );
		// Annotate with text using specified text, bounding area,
		// placement gravity, and rotation.
		void            Annotate ( System::String^ text_,
									 Geometry^ boundingArea_,
									 GravityType gravity_,
									 double degrees_ );
		// Annotate with text (bounding area is entire image) and placement
		// gravity.
		void            Annotate ( System::String^ text_,
									GravityType gravity_ );
    
		// Blur image with specified blur factor
		// The radius_ parameter specifies the radius of the Gaussian, in
		// pixels, not counting the center pixel.  The sigma_ parameter
		// specifies the standard deviation of the Laplacian, in pixels.
		void            Blur ( double radius_, double sigma_ );
	    
		// Border image (add border to image)
		void            Border ( Geometry^ geometry_ );

		// Extract channel from image
		void            Channel ( ChannelType channel_ );

		// Set or obtain modulus channel depth
		void            ChannelDepth ( ChannelType channel_,
									   unsigned int depth_ );
		unsigned int    ChannelDepth ( ChannelType channel_ );

		// Charcoal effect image (looks like charcoal sketch)
		// The radius_ parameter specifies the radius of the Gaussian, in
		// pixels, not counting the center pixel.  The sigma_ parameter
		// specifies the standard deviation of the Laplacian, in pixels.
		void            Charcoal ( double radius_, double sigma_ );

		// Chop image (remove vertical or horizontal subregion of image)
		// FIXME: describe how geometry argument is used to select either
		// horizontal or vertical subregion of image.
		void            Chop ( Geometry^ geometry_ );
	    
		// Colorize image with pen color, using specified percent opacity
		// for red, green, and blue quantums
		void            Colorize ( unsigned int opacityRed_,
								   unsigned int opacityGreen_,
								   unsigned int opacityBlue_,
									Color^ penColor_ );
		// Colorize image with pen color, using specified percent opacity.
		void            Colorize ( unsigned int opacity_,
									Color^ penColor_ );
    
		// Comment image (add comment string to image)
		void            Comment ( System::String^ comment_ );

		// Composition operator to be used when composition is implicitly
		// used (such as for image flattening).
		void            Compose (CompositeOperator compose_);
		CompositeOperator Compose ( void );

		// Compare current image with another image
		// Sets meanErrorPerPixel, normalizedMaxError, and normalizedMeanError
		// in the current image. False is returned if the images are identical.
		bool            Compare (Image^ reference_ );

		// Compose an image onto another at specified offset and using
		// specified algorithm
		void            Composite ( Image^ compositeImage_,
									int xOffset_,
									int yOffset_,
									CompositeOperator compose_ );
		void            Composite ( Image^ compositeImage_,
									Geometry^ offset_,
									CompositeOperator compose_ );
		void            Composite ( Image^ compositeImage_,
									GravityType gravity_,
									CompositeOperator compose_ );
	    
		// Contrast image (enhance intensity differences in image)
		void            Contrast ( unsigned int sharpen_ );

		// Convolve image.  Applies a user-specified convolution to the image.
		//  order_ represents the number of columns and rows in the filter kernel.
		//  kernel_ is an array of doubles representing the convolution kernel.
		void            Convolve ( unsigned int order_,
								   double *kernel_ );

		// Crop image (subregion of original image)
		void            Crop ( Geometry^ geometry_ );
	    
		// Cycle image colormap
		void            CycleColormap ( int amount_ );
	    
		// Despeckle image (reduce speckle noise)
		void            Despeckle ( void );
	    
		// Edge image (hilight edges in image)
		void            Edge ( double radius_ );
	   
		// Emboss image (hilight edges with 3D effect)
		// The radius_ parameter specifies the radius of the Gaussian, in
		// pixels, not counting the center pixel.  The sigma_ parameter
		// specifies the standard deviation of the Laplacian, in pixels.
		void            Emboss ( double radius_, double sigma_ );

		// Enhance image (minimize noise)
		void            Enhance ( void );
	    
		// Equalize image (histogram equalization)
		void            Equalize ( void );

		// Erase image to current "background color"
		void            Erase ( void );
	    
		// Extend the image as defined by the geometry.
		void            Extent ( Geometry^ geometry_ );
		// Flip image (reflect each scanline in the vertical direction)
		void            Flip ( void );

		// Flood-fill color across pixels that match the color of the
		// target pixel and are neighbors of the target pixel.
		// Uses current fuzz setting when determining color match.
		void            FloodFillColor( unsigned int x_,
										unsigned int y_,
										Color^ fillColor_ );
		void            FloodFillColor( Geometry^ point_,
										Color^ fillColor_ );

		// Flood-fill color across pixels starting at target-pixel and
		// stopping at pixels matching specified border color.
		// Uses current fuzz setting when determining color match.
		void            FloodFillColor( unsigned int x_,
										unsigned int y_,
										Color^ fillColor_,
										Color^ borderColor_ );
		void            FloodFillColor( Geometry^ point_,
										Color^ fillColor_,
										Color^ borderColor_ );

		// Floodfill pixels matching color (within fuzz factor) of target
		// pixel(x,y) with replacement opacity value using method.
		void            FloodFillOpacity ( unsigned int x_,
										   unsigned int y_,
										   unsigned int opacity_,
										   PaintMethod method_ );

		// Flood-fill texture across pixels that match the color of the
		// target pixel and are neighbors of the target pixel.
		// Uses current fuzz setting when determining color match.
		void            FloodFillTexture( unsigned int x_,
										  unsigned int y_,
											Image^ texture_ );
		void            FloodFillTexture( Geometry^ point_,
											Image^ texture_ );

		// Flood-fill texture across pixels starting at target-pixel and
		// stopping at pixels matching specified border color.
		// Uses current fuzz setting when determining color match.
		void            FloodFillTexture( unsigned int x_,
										  unsigned int y_,
											Image^ texture_,
											Color^ borderColor_ );
		void            FloodFillTexture( Geometry^ point_,
											Image^ texture_,
											Color^ borderColor_ );
	    
		// Flop image (reflect each scanline in the horizontal direction)
		void            Flop ( void );
	    
		// Frame image
		void            Frame ( Geometry^ geometry_ );
		void            Frame ( unsigned int width_,
								unsigned int height_,
								int innerBevel_,
								int outerBevel_ );
	    
		// Gamma correct image
		void            Gamma ( double gamma_ );
		void            Gamma ( double gammaRed_,
								double gammaGreen_,
								double gammaBlue_ );

		// Gaussian blur image
		// The number of neighbor pixels to be included in the convolution
		// mask is specified by 'width_'. The standard deviation of the
		// gaussian bell curve is specified by 'sigma_'.
		void            GaussianBlur ( double width_, double sigma_ );
	    
		// Implode image (special effect)
		void            Implode ( double factor_ );
	    
		// Label image
		void            Label ( System::String^ label_ );

		// Level image. Adjust the levels of the image by scaling the
		// colors falling between specified white and black points to the
		// full available quantum range. The parameters provided represent
		// the black, mid (gamma), and white points.  The black point
		// specifies the darkest color in the image. Colors darker than
		// the black point are set to zero. Mid point (gamma) specifies a
		// gamma correction to apply to the image. White point specifies
		// the lightest color in the image.  Colors brighter than the
		// white point are set to the maximum quantum value. The black and
		// white point have the valid range 0 to QuantumRange while mid (gamma)
		// has a useful range of 0 to ten.
		void            Level ( double black_point,
								double white_point,
								double mid_point );

		// Level image channel. Adjust the levels of the image channel by
		// scaling the values falling between specified white and black
		// points to the full available quantum range. The parameters
		// provided represent the black, mid (gamma), and white points.
		// The black point specifies the darkest color in the
		// image. Colors darker than the black point are set to zero. Mid
		// point (gamma) specifies a gamma correction to apply to the
		// image. White point specifies the lightest color in the image.
		// Colors brighter than the white point are set to the maximum
		// quantum value. The black and white point have the valid range 0
		// to QuantumRange while mid (gamma) has a useful range of 0 to ten.
		void            LevelChannel ( ChannelType channel,
									   double black_point,
									   double white_point,
									   double mid_point );

		// Magnify image by integral size
		void            Magnify ( void );
	    
		// Remap image colors with closest color from reference image
		void            Map ( Image^ mapImage_ ,
							  bool dither_ );
	    
		// Floodfill designated area with replacement opacity value
		void            MatteFloodfill ( Color^ target_ ,
				 unsigned int opacity_,
				 int x_, int y_,
				 PaintMethod method_ );

		// Filter image by replacing each pixel component with the median
		// color in a circular neighborhood
		void            MedianFilter ( double radius_ );
	    
		// Reduce image by integral size
		void            Minify ( void );
	    
		// Modulate percent hue, saturation, and brightness of an image
		void            Modulate ( double brightness_,
				 double saturation_,
				 double hue_ );
	    
		// Negate colors in image.  Set grayscale to only negate grayscale
		// values in image.
		void            Negate ( bool grayscale_ );
	    
		// Normalize image (increase contrast by normalizing the pixel
		// values to span the full range of color values)
		void            Normalize ( void );
	    
		// Oilpaint image (image looks like oil painting)
		void            OilPaint ( double radius_ );

		// Set or attenuate the opacity channel in the image. If the image
		// pixels are opaque then they are set to the specified opacity
		// value, otherwise they are blended with the supplied opacity
		// value.  The value of opacity_ ranges from 0 (completely opaque)
		// to QuantumRange. The defines OpaqueOpacity and TransparentOpacity are
		// available to specify completely opaque or completely
		// transparent, respectively.
		void            Opacity ( unsigned int opacity_ );

		// Change color of opaque pixel to specified pen color.
		void            Opaque ( Color^ opaqueColor_,
			   Color^ penColor_ );


		// Quantize image (reduce number of colors)
		void            Quantize ( bool measureError_ );

		void            QuantumOperator ( ChannelType channel_,
										  MagickEvaluateOperator operator_,
										  MagickCore::Quantum rvalue_);

		void            QuantumOperator ( int x_,int y_,
										  unsigned int columns_,
										  unsigned int rows_,
										  ChannelType channel_,
										  MagickEvaluateOperator operator_,
										  MagickCore::Quantum rvalue_);

		// Raise image (lighten or darken the edges of an image to give a
		// 3-D raised or lowered effect)
		void            Raise ( Geometry^ geometry_,
								bool raisedFlag_ );
	    

		// Reduce noise in image using a noise peak elimination filter
		void            ReduceNoise ( void );
		void            ReduceNoise ( double order_ );
	    
		// Resize image to specified size.
		void            Resize ( Geometry ^geometry_ );

		// Roll image (rolls image vertically and horizontally) by specified
		// number of columnms and rows)
		void            Roll ( Geometry ^roll_ );
		void            Roll ( unsigned int columns_,
			 unsigned int rows_ );
	    
		// Rotate image counter-clockwise by specified number of degrees.
		void            Rotate ( double degrees_ );
	    
		// Resize image by using pixel sampling algorithm
		void            Sample ( Geometry ^geometry_ );
	    
		// Resize image by using simple ratio algorithm
		void            Scale ( Geometry ^geometry_ );
	    
		// Segment (coalesce similar image components) by analyzing the
		// histograms of the color components and identifying units that
		// are homogeneous with the fuzzy c-means technique.  Also uses
		// QuantizeColorSpace and Verbose image attributes
		void            Segment ( double clusterThreshold_ , 
				double smoothingThreshold_ );
	    
		// Shade image using distant light source
		void            Shade ( double azimuth_ ,
			  double elevation_,
			  bool   colorShading_ );
	    
		// Sharpen pixels in image
		// The radius_ parameter specifies the radius of the Gaussian, in
		// pixels, not counting the center pixel.  The sigma_ parameter
		// specifies the standard deviation of the Laplacian, in pixels.
		void            Sharpen ( double radius_,
								  double sigma_ );

		// Shave pixels from image edges.
		void            Shave ( Geometry ^geometry_ );
	    
		// Shear image (create parallelogram by sliding image by X or Y axis)
		void            Shear ( double xShearAngle_,
			  double yShearAngle_ );
	    
		// adjust the image contrast with a non-linear sigmoidal contrast algorithm
		void            SigmoidalContrast ( unsigned int sharpen_, double contrast, double midpoint );

		// Solarize image (similar to effect seen when exposing a
		// photographic film to light during the development process)
		void            Solarize ( double factor_ );
	    
		// Spread pixels randomly within image by specified ammount
		void            Spread ( unsigned int amount_ );
	    
		// Add a digital watermark to the image (based on second image)
		void            Stegano ( Image ^watermark_ );
	    
		// Create an image which appears in stereo when viewed with
		// red-blue glasses (Red image on left, blue on right)
		void            Stereo ( Image ^rightImage_ );
	    
		// Swirl image (image pixels are rotated by degrees)
		void            Swirl ( double degrees_ );
	    
		// Channel a texture on image background
		void            Texture ( Image ^texture_ );
	    
		// Threshold image
		void            Threshold ( double threshold_ );
	    
		// Transform image based on image and crop geometries
		// Crop geometry is optional
		void            Transform ( Geometry ^imageGeometry_ );
		void            Transform ( Geometry ^imageGeometry_,
			Geometry ^cropGeometry_  );

		// Add matte image to image, setting pixels matching color to
		// transparent
		void            Transparent ( Color ^color_ );
	    
		// Trim edges that are the background color from the image
		void            Trim ( void );

		// Image representation type (also see type attribute)
		//   Available types:
		//    Bilevel        Grayscale       GrayscaleMatte
		//    Palette        PaletteMatte    TrueColor
		//    TrueColorMatte ColorSeparation ColorSeparationMatte
		void            Type ( ImageType type_ );

		// Replace image with a sharpened version of the original image
		// using the unsharp mask algorithm.
		//  radius_
		//    the radius of the Gaussian, in pixels, not counting the
		//    center pixel.
		//  sigma_
		//    the standard deviation of the Gaussian, in pixels.
		//  amount_
		//    the percentage of the difference between the original and
		//    the blur image that is added back into the original.
		// threshold_
		//   the threshold in pixels needed to apply the diffence amount.
		void            Unsharpmask ( double radius_,
									  double sigma_,
									  double amount_,
									  double threshold_ );

		// Map image pixels to a sine wave
		void            Wave ( double amplitude_ ,
							   double wavelength_ );
	    

		//----------------------------------------------------------------
		// properties
		//----------------------------------------------------------------

		// Image width
		property unsigned int    Columns
		{
			unsigned int get();
		}
		property unsigned int    Width
		{
			unsigned int get()
			{
				return Columns;
			}
		}
    
		// Compression type
		property CompressionType	CompressType
		{
			CompressionType get();
			void set ( CompressionType compressType );
		}

		// JPEG/MIFF/PNG compression level (default 75).
		property unsigned int	Quality
		{
			unsigned int get();
			void set(unsigned int);
		}

		// JPEG/MIFF/PNG/GIF etc.
		property String^	Format
		{
			String^ get();
			void set(String^);
		}

		// The number of pixel rows in the image
		property unsigned int    Rows
		{
			unsigned int get();
		}
		property unsigned int    Height
		{
			unsigned int get()
			{
				return Rows;
			}
		}


		//----------------------------------------------------------------
		// IO
		//----------------------------------------------------------------

		// read
		void			Read(String^ imageSpec_);

		// Read single image frame of specified size into current object
		void            Read ( Geometry^ size_,
								System::String^ imageSpec_ );

		// write
		void Write(String^ filename);


		// convert to bitmap
		System::Drawing::Bitmap^ ToBitmap();

	};
}
