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

#include "stdafx.h"
#include "Image.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace ImageMagickNET 
{
	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Image::Image(Magick::Image* image_)
	{ 
		isReferenceOnly = true; // set this so that the image reference is not destroyed.
		image = image_; 
	}


	///-------------------------------------------------------------------
	/// Constructor
	///-------------------------------------------------------------------
	Image::Image()
	{
		isReferenceOnly = false;
		image = new Magick::Image();
	}

	///-------------------------------------------------------------------
	/// Copy constructor
	///-------------------------------------------------------------------
	Image::Image(Image^ imageSource)
	{
		isReferenceOnly = false;
		image = new Magick::Image(*(imageSource->image));
	}


	///-------------------------------------------------------------------
	/// Constructor
	/// Loads the file from the specified file path.
	///-------------------------------------------------------------------
	Image::Image(System::String^ imageSpec)
	{
		isReferenceOnly = false;
		image = new Magick::Image(Marshaller::SystemStringToStdString(imageSpec));
	}

	///===================================================================
	/// methods
	///===================================================================

	///-------------------------------------------------------------------
	// Local adaptive threshold image
	// http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm
	// Width x height define the size of the pixel neighborhood
	// offset = constant to subtract from pixel neighborhood mean
	///-------------------------------------------------------------------
	void            Image::AdaptiveThreshold ( unsigned int width,
										unsigned int height,
										unsigned offset )
	{
		image->adaptiveThreshold( width, height, offset );
	}

	///-------------------------------------------------------------------
	// Add noise to image with specified noise type
	///-------------------------------------------------------------------
	void            Image::AddNoise ( NoiseType noiseType_ )
	{
		image->addNoise( (Magick::NoiseType) noiseType_ );
	}

	///-------------------------------------------------------------------
	// Annotate using specified text, and placement location
	///-------------------------------------------------------------------
	void            Image::Annotate ( System::String^ text_,
								Geometry^ location_ )
	{
		image->annotate( Marshaller::SystemStringToStdString(text_), *(location_->geometry));
	}

	///-------------------------------------------------------------------
	// Annotate using specified text, bounding area, and placement
	// gravity
	///-------------------------------------------------------------------
	void            Image::Annotate ( System::String^ text_,
								Geometry^ boundingArea_,
								GravityType gravity_ )
	{
		image->annotate( Marshaller::SystemStringToStdString(text_), 
			(MagickCore::GravityType)gravity_ );
	}

	///-------------------------------------------------------------------
	// Annotate with text using specified text, bounding area,
	// placement gravity, and rotation.
	///-------------------------------------------------------------------
	void            Image::Annotate ( System::String^ text_,
								 Geometry^ boundingArea_,
								 GravityType gravity_,
								 double degrees_ )
	{
		image->annotate( Marshaller::SystemStringToStdString(text_), 
			*(boundingArea_->geometry), (MagickCore::GravityType)gravity_, degrees_ );
	}

	///-------------------------------------------------------------------
	// Annotate with text (bounding area is entire image) and placement
	// gravity.
	///-------------------------------------------------------------------
	void            Image::Annotate ( System::String^ text_,
								GravityType gravity_ )
	{
		image->annotate( Marshaller::SystemStringToStdString(text_), 
			(MagickCore::GravityType)gravity_ );
	}

	///-------------------------------------------------------------------
	// Blur image with specified blur factor
	// The radius_ parameter specifies the radius of the Gaussian, in
	// pixels, not counting the center pixel.  The sigma_ parameter
	// specifies the standard deviation of the Laplacian, in pixels.
	///-------------------------------------------------------------------
	void            Image::Blur ( double radius_, double sigma_ )
	{
		image->blur( radius_, sigma_ );
	}
    
	///-------------------------------------------------------------------
	// Border image (add border to image)
	///-------------------------------------------------------------------
	void            Image::Border ( Geometry^ geometry_ )
	{
		image->border( *(geometry_->geometry) );
	}

	///-------------------------------------------------------------------
	// Extract channel from image
	///-------------------------------------------------------------------
	void            Image::Channel ( ChannelType channel_ )
	{
		image->channel( (Magick::ChannelType) channel_ );
	}

	///-------------------------------------------------------------------
	// Set or obtain modulus channel depth
	///-------------------------------------------------------------------
	void            Image::ChannelDepth ( ChannelType channel_,
								   unsigned int depth_ )
	{
		image->channelDepth( (Magick::ChannelType) channel_, depth_ );
	}
	unsigned int    Image::ChannelDepth ( ChannelType channel_ )
	{
		return image->channelDepth( (Magick::ChannelType) channel_ );
	}

	///-------------------------------------------------------------------
	// Charcoal effect image (looks like charcoal sketch)
	// The radius_ parameter specifies the radius of the Gaussian, in
	// pixels, not counting the center pixel.  The sigma_ parameter
	// specifies the standard deviation of the Laplacian, in pixels.
	///-------------------------------------------------------------------
	void            Image::Charcoal ( double radius_, double sigma_ )
	{
		image->charcoal( radius_, sigma_ );
	}

	///-------------------------------------------------------------------
	// Chop image (remove vertical or horizontal subregion of image)
	// FIXME: describe how geometry argument is used to select either
	// horizontal or vertical subregion of image.
	///-------------------------------------------------------------------
	void            Image::Chop ( Geometry^ geometry_ )
	{
		image->chop( *(geometry_->geometry) );
	}

	///-------------------------------------------------------------------
    // Colorize image with pen color, using specified percent opacity
    // for red, green, and blue quantums
	///-------------------------------------------------------------------
    void            Image::Colorize ( unsigned int opacityRed_,
                               unsigned int opacityGreen_,
                               unsigned int opacityBlue_,
								Color^ penColor_ )
	{
		image->colorize(opacityRed_, opacityGreen_, opacityBlue_, *(penColor_->color));
	}

	///-------------------------------------------------------------------
    // Colorize image with pen color, using specified percent opacity.
	///-------------------------------------------------------------------
    void            Image::Colorize ( unsigned int opacity_,
								Color^ penColor_ )
	{
		image->colorize(opacity_, *(penColor_->color));
	}
    
	///-------------------------------------------------------------------
	// Comment image (add comment string to image)
	///-------------------------------------------------------------------
	void            Image::Comment ( System::String^ comment_ )
	{
		image->comment(Marshaller::SystemStringToStdString(comment_));
	}

	///-------------------------------------------------------------------
	// Composition operator to be used when composition is implicitly
	// used (such as for image flattening).
	///-------------------------------------------------------------------
	void            Image::Compose (CompositeOperator compose_)
	{
		image->compose((Magick::CompositeOperator)compose_);
	}
	CompositeOperator Image::Compose ( void )
	{
		return (CompositeOperator)image->compose();
	}

	///-------------------------------------------------------------------
	// Compare current image with another image
	// Sets meanErrorPerPixel, normalizedMaxError, and normalizedMeanError
	// in the current image. False is returned if the images are identical.
	///-------------------------------------------------------------------
	bool            Image::Compare (Image^ reference_ )
	{
		return image->compare(*(reference_->image));
	}

	///-------------------------------------------------------------------
	// Compose an image onto another at specified offset and using
	// specified algorithm
	///-------------------------------------------------------------------
	void            Image::Composite ( Image^ compositeImage_,
								int xOffset_,
								int yOffset_,
								CompositeOperator compose_ )
	{
		image->composite(*(compositeImage_->image), xOffset_, yOffset_, (Magick::CompositeOperator)compose_);
	}
	void            Image::Composite ( Image^ compositeImage_,
								Geometry^ offset_,
								CompositeOperator compose_ )
	{
		image->composite(*(compositeImage_->image), *(offset_->geometry), (Magick::CompositeOperator)compose_);
	}
	void            Image::Composite ( Image^ compositeImage_,
								GravityType gravity_,
								CompositeOperator compose_ )
	{
		image->composite(*(compositeImage_->image), (Magick::GravityType)gravity_, (Magick::CompositeOperator)compose_);
	}
		
	///-------------------------------------------------------------------
    // Contrast image (enhance intensity differences in image)
	///-------------------------------------------------------------------
    void            Image::Contrast ( const unsigned int sharpen_ )
	{
		image->contrast(sharpen_);
	}

	///-------------------------------------------------------------------
    // Convolve image.  Applies a user-specified convolution to the image.
    //  order_ represents the number of columns and rows in the filter kernel.
    //  kernel_ is an array of doubles representing the convolution kernel.
	///-------------------------------------------------------------------
    void            Image::Convolve ( unsigned int order_,
                               double *kernel_ )
	{
		image->convolve(order_, kernel_);
	}

	///-------------------------------------------------------------------
    // Crop image (subregion of original image)
	///-------------------------------------------------------------------
    void            Image::Crop ( Geometry^ geometry_ )
	{
		image->crop(*(geometry_->geometry));
	}
    
	///-------------------------------------------------------------------
    // Cycle image colormap
	///-------------------------------------------------------------------
    void            Image::CycleColormap ( int amount_ )
	{
		image->cycleColormap(amount_);
	}
    
	///-------------------------------------------------------------------
    // Despeckle image (reduce speckle noise)
	///-------------------------------------------------------------------
    void            Image::Despeckle ( void )
	{
		image->despeckle();
	}
    
	///-------------------------------------------------------------------
	// Edge image (hilight edges in image)
	///-------------------------------------------------------------------
	void            Image::Edge ( double radius_ )
	{
		image->edge( radius_ );
	}
   
	///-------------------------------------------------------------------
	// Emboss image (hilight edges with 3D effect)
	// The radius_ parameter specifies the radius of the Gaussian, in
	// pixels, not counting the center pixel.  The sigma_ parameter
	// specifies the standard deviation of the Laplacian, in pixels.
	///-------------------------------------------------------------------
	void            Image::Emboss ( double radius_, double sigma_ )
	{
		image->emboss( radius_, sigma_ );
	}


	///-------------------------------------------------------------------
	// Enhance image (minimize noise)
	///-------------------------------------------------------------------
	void            Image::Enhance ( void )
	{
		image->enhance();
	}
    
	///-------------------------------------------------------------------
	// Equalize image (histogram equalization)
	///-------------------------------------------------------------------
	void            Image::Equalize ( void )
	{
		image->equalize();
	}

	///-------------------------------------------------------------------
	// Erase image to current "background color"
	///-------------------------------------------------------------------
	void            Image::Erase ( void )
	{
		image->erase();
	}
    
	///-------------------------------------------------------------------
	// Extend the image as defined by the geometry.
	///-------------------------------------------------------------------
	void            Image::Extent ( Geometry^ geometry_ )
	{
		image->extent(*(geometry_->geometry));
	}

	///-------------------------------------------------------------------
	// Flip image (reflect each scanline in the vertical direction)
	///-------------------------------------------------------------------
	void            Image::Flip ( void )
	{
		image->flip();
	}

	///-------------------------------------------------------------------
	// Flood-fill color across pixels that match the color of the
	// target pixel and are neighbors of the target pixel.
	// Uses current fuzz setting when determining color match.
	///-------------------------------------------------------------------
	void            Image::FloodFillColor( unsigned int x_,
									unsigned int y_,
									Color^ fillColor_ )
	{
		image->floodFillColor( x_, y_, *(fillColor_->color) );
	}
	void            Image::FloodFillColor( Geometry^ point_,
									Color^ fillColor_ )
	{
		image->floodFillColor( *(point_->geometry), *(fillColor_->color) );
	}

	///-------------------------------------------------------------------
	// Flood-fill color across pixels starting at target-pixel and
	// stopping at pixels matching specified border color.
	// Uses current fuzz setting when determining color match.
	///-------------------------------------------------------------------
	void            Image::FloodFillColor( unsigned int x_,
									unsigned int y_,
									Color^ fillColor_,
									Color^ borderColor_ )
	{
		image->floodFillColor( x_, y_, *(fillColor_->color), *(borderColor_->color) );
	}
	void            Image::FloodFillColor( Geometry^ point_,
									Color^ fillColor_,
									Color^ borderColor_ )
	{
		image->floodFillColor( *(point_->geometry), 
			*(fillColor_->color), *(borderColor_->color) );
	}

	///-------------------------------------------------------------------
	// Floodfill pixels matching color (within fuzz factor) of target
	// pixel(x,y) with replacement opacity value using method.
	///-------------------------------------------------------------------
	void            Image::FloodFillOpacity ( unsigned int x_,
									   unsigned int y_,
									   unsigned int opacity_,
									   PaintMethod method_ )
	{
		image->floodFillOpacity( x_, y_, opacity_, (MagickCore::PaintMethod)method_ );
	}

	///-------------------------------------------------------------------
	// Flood-fill texture across pixels that match the color of the
	// target pixel and are neighbors of the target pixel.
	// Uses current fuzz setting when determining color match.
	///-------------------------------------------------------------------
	void            Image::FloodFillTexture( unsigned int x_,
									  unsigned int y_,
										Image^ texture_ )
	{
		image->floodFillTexture( x_, y_, *(texture_->image) );
	}
	void            Image::FloodFillTexture( Geometry^ point_,
										Image^ texture_ )
	{
		image->floodFillTexture( *(point_->geometry), *(texture_->image) );
	}

	///-------------------------------------------------------------------
	// Flood-fill texture across pixels starting at target-pixel and
	// stopping at pixels matching specified border color.
	// Uses current fuzz setting when determining color match.
	///-------------------------------------------------------------------
	void            Image::FloodFillTexture( unsigned int x_,
									  unsigned int y_,
										Image^ texture_,
										Color^ borderColor_ )
	{
		image->floodFillTexture( x_, y_, *(texture_->image), *(borderColor_->color) );
	}

	void            Image::FloodFillTexture( Geometry^ point_,
										Image^ texture_,
										Color^ borderColor_ )
	{
		image->floodFillTexture( *(point_->geometry), *(texture_->image), 
			*(borderColor_->color) );
	}
    
	///-------------------------------------------------------------------
	// Flop image (reflect each scanline in the horizontal direction)
	///-------------------------------------------------------------------
	void            Image::Flop ( void )
	{
		image->flop();
	}
    

	///-------------------------------------------------------------------
	// Frame image
	///-------------------------------------------------------------------
	void            Image::Frame ( Geometry^ geometry_ )
	{
		image->frame( *(geometry_->geometry) );
	}
	void            Image::Frame ( unsigned int width_,
							unsigned int height_,
							int innerBevel_,
							int outerBevel_ )
	{
		image->frame( width_, height_, innerBevel_, outerBevel_ );
	}
    
	///-------------------------------------------------------------------
	// Gamma correct image
	///-------------------------------------------------------------------
	void            Image::Gamma ( double gamma_ )
	{
		image->gamma( gamma_ );
	}
	void            Image::Gamma ( double gammaRed_,
							double gammaGreen_,
							double gammaBlue_ )
	{
		image->gamma( gammaRed_, gammaGreen_, gammaBlue_ );
	}

	///-------------------------------------------------------------------
	// Gaussian blur image
	// The number of neighbor pixels to be included in the convolution
	// mask is specified by 'width_'. The standard deviation of the
	// gaussian bell curve is specified by 'sigma_'.
	///-------------------------------------------------------------------
	void            Image::GaussianBlur ( double width_, double sigma_ )
	{
		image->gaussianBlur( width_, sigma_ );
	}
    
	///-------------------------------------------------------------------
	// Implode image (special effect)
	///-------------------------------------------------------------------
	void            Image::Implode ( double factor_ )
	{
		image->implode( factor_ );
	}
    
	///-------------------------------------------------------------------
	// Label image
	///-------------------------------------------------------------------
	void            Image::Label ( System::String^ label_ )
	{
		image->label( Marshaller::SystemStringToStdString(label_));
	}

	///-------------------------------------------------------------------
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
	///-------------------------------------------------------------------
	void            Image::Level ( double black_point,
							double white_point,
							double mid_point )
	{
		image->level( black_point, white_point, mid_point );
	}

	///-------------------------------------------------------------------
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
	///-------------------------------------------------------------------
	void            Image::LevelChannel ( ChannelType channel,
								   double black_point,
								   double white_point,
								   double mid_point )
	{
		image->levelChannel( (MagickCore::ChannelType)channel, 
			black_point, white_point, mid_point );
	}

	///-------------------------------------------------------------------
	// Magnify image by integral size
	///-------------------------------------------------------------------
	void            Image::Magnify ( void )
	{
		image->magnify();
	}
    
	///-------------------------------------------------------------------
	// Remap image colors with closest color from reference image
	///-------------------------------------------------------------------
	void            Image::Map ( Image^ mapImage_ ,
						  bool dither_ )
	{
		image->map( *(mapImage_->image), dither_ );
	}
    

	///-------------------------------------------------------------------
	// Floodfill designated area with replacement opacity value
	///-------------------------------------------------------------------
	void            Image::MatteFloodfill ( Color^ target_ ,
			 unsigned int opacity_,
			 int x_, const int y_,
			 PaintMethod method_ )

	{
		image->matteFloodfill( *(target_->color), opacity_, x_, y_, (MagickCore::PaintMethod) method_ );
	}

	///-------------------------------------------------------------------
	// Filter image by replacing each pixel component with the median
	// color in a circular neighborhood
	///-------------------------------------------------------------------
	void            Image::MedianFilter ( double radius_ )
	{
		image->medianFilter( radius_);
	}
    
	///-------------------------------------------------------------------
	// Reduce image by integral size
	///-------------------------------------------------------------------
	void            Image::Minify ( void )
	{
		image->minify();
	}
    
	///-------------------------------------------------------------------
	// Modulate percent hue, saturation, and brightness of an image
	///-------------------------------------------------------------------
	void            Image::Modulate ( double brightness_,
			 double saturation_,
			 double hue_ )
	{
		image->modulate( brightness_, saturation_, hue_ );
	}
    
	///-------------------------------------------------------------------
	// Negate colors in image.  Set grayscale to only negate grayscale
	// values in image.
	///-------------------------------------------------------------------
	void            Image::Negate ( bool grayscale_ )
	{
		image->negate( grayscale_ );
	}
    
	///-------------------------------------------------------------------
	// Normalize image (increase contrast by normalizing the pixel
	// values to span the full range of color values)
	///-------------------------------------------------------------------
	void            Image::Normalize ( void )
	{
		image->normalize();
	}
    
	///-------------------------------------------------------------------
	// Oilpaint image (image looks like oil painting)
	///-------------------------------------------------------------------
	void            Image::OilPaint ( double radius_ )
	{
		image->oilPaint(radius_);
	}

	///-------------------------------------------------------------------
	// Set or attenuate the opacity channel in the image. If the image
	// pixels are opaque then they are set to the specified opacity
	// value, otherwise they are blended with the supplied opacity
	// value.  The value of opacity_ ranges from 0 (completely opaque)
	// to QuantumRange. The defines OpaqueOpacity and TransparentOpacity are
	// available to specify completely opaque or completely
	// transparent, respectively.
	///-------------------------------------------------------------------
	void            Image::Opacity ( unsigned int opacity_ )
	{
		image->opacity(opacity_);
	}

	///-------------------------------------------------------------------
	// Change color of opaque pixel to specified pen color.
	///-------------------------------------------------------------------
	void            Image::Opaque ( Color^ opaqueColor_,
		   Color^ penColor_ )
	{
		image->opaque( *(opaqueColor_->color), *(penColor_->color) );
	}



	///-------------------------------------------------------------------
	// Quantize image (reduce number of colors)
	///-------------------------------------------------------------------
	void            Image::Quantize ( bool measureError_ )
	{
		image->quantize(measureError_);
	}

	void            Image::QuantumOperator ( ChannelType channel_,
									  MagickEvaluateOperator operator_,
									  MagickCore::Quantum rvalue_)
	{
		image->quantumOperator( (MagickCore::ChannelType)channel_,
			(MagickCore::MagickEvaluateOperator)operator_,
			rvalue_);
	}

	void            Image::QuantumOperator ( int x_,int y_,
									  unsigned int columns_,
									  unsigned int rows_,
									  ChannelType channel_,
									  MagickEvaluateOperator operator_,
									  MagickCore::Quantum rvalue_)
	{
		image->quantumOperator( x_, y_, columns_, rows_,
			(MagickCore::ChannelType)channel_,
			(MagickCore::MagickEvaluateOperator)operator_,
			rvalue_);
	}

	///-------------------------------------------------------------------
	// Raise image (lighten or darken the edges of an image to give a
	// 3-D raised or lowered effect)
	///-------------------------------------------------------------------
	void            Image::Raise ( Geometry^ geometry_,
							bool raisedFlag_ )
	{
		image->raise( *(geometry_->geometry), raisedFlag_);
	}
    

	///-------------------------------------------------------------------
	// Reduce noise in image using a noise peak elimination filter
	///-------------------------------------------------------------------
	void            Image::ReduceNoise ( void )
	{
		image->reduceNoise();
	}
	void            Image::ReduceNoise ( double order_ )
	{
		image->reduceNoise(order_);
	}
    
	///-------------------------------------------------------------------
	// Resize image to specified size.
	///-------------------------------------------------------------------
	void            Image::Resize ( Geometry ^geometry_ )
	{
		image->resize( *(geometry_->geometry) );
	}

	///-------------------------------------------------------------------
	// Roll image (rolls image vertically and horizontally) by specified
	// number of columnms and rows)
	///-------------------------------------------------------------------
	void            Image::Roll ( Geometry ^roll_ )
	{
		image->roll( *(roll_->geometry) );
	}
	void            Image::Roll ( unsigned int columns_,
		 unsigned int rows_ )
	{
		image->roll( columns_, rows_ );
	}
    
	///-------------------------------------------------------------------
	// Rotate image counter-clockwise by specified number of degrees.
	///-------------------------------------------------------------------
	void            Image::Rotate ( double degrees_ )
	{
		image->rotate( degrees_ );
	}
    
	///-------------------------------------------------------------------
	// Resize image by using pixel sampling algorithm
	///-------------------------------------------------------------------
	void            Image::Sample ( Geometry ^geometry_ )
	{
		image->sample( *(geometry_->geometry) );
	}
    
	///-------------------------------------------------------------------
	// Resize image by using simple ratio algorithm
	///-------------------------------------------------------------------
	void            Image::Scale ( Geometry ^geometry_ )
	{
		image->scale( *(geometry_->geometry) );
	}
    
	///-------------------------------------------------------------------
	// Segment (coalesce similar image components) by analyzing the
	// histograms of the color components and identifying units that
	// are homogeneous with the fuzzy c-means technique.  Also uses
	// QuantizeColorSpace and Verbose image attributes
	///-------------------------------------------------------------------
	void            Image::Segment ( double clusterThreshold_ , 
			double smoothingThreshold_ )
	{
		image->segment( clusterThreshold_, smoothingThreshold_ );
	}
    
	///-------------------------------------------------------------------
	// Shade image using distant light source
	///-------------------------------------------------------------------
	void            Image::Shade ( double azimuth_ ,
		  double elevation_,
		  bool   colorShading_ )
	{
		image->shade( azimuth_, elevation_, colorShading_ );
	}
    
	///-------------------------------------------------------------------
	// Sharpen pixels in image
	// The radius_ parameter specifies the radius of the Gaussian, in
	// pixels, not counting the center pixel.  The sigma_ parameter
	// specifies the standard deviation of the Laplacian, in pixels.
	///-------------------------------------------------------------------
	void            Image::Sharpen ( double radius_,
							  double sigma_ )
	{
		image->sharpen( radius_, sigma_ );
	}

	///-------------------------------------------------------------------
	// Shave pixels from image edges.
	///-------------------------------------------------------------------
	void            Image::Shave ( Geometry ^geometry_ )
	{
		image->shave( *(geometry_->geometry) );
	}
    
	///-------------------------------------------------------------------
	// Shear image (create parallelogram by sliding image by X or Y axis)
	///-------------------------------------------------------------------
	void            Image::Shear ( double xShearAngle_,
		  double yShearAngle_ )
	{
		image->shear( xShearAngle_, yShearAngle_ );
	}
    
	///-------------------------------------------------------------------
	// adjust the image contrast with a non-linear sigmoidal contrast algorithm
	///-------------------------------------------------------------------
	void            Image::SigmoidalContrast ( unsigned int sharpen_, double contrast, double midpoint )
	{
		image->sigmoidalContrast( sharpen_, contrast, midpoint );
	}


	///-------------------------------------------------------------------
	// Solarize image (similar to effect seen when exposing a
	// photographic film to light during the development process)
	///-------------------------------------------------------------------
	void            Image::Solarize ( double factor_ )
	{
		image->solarize( factor_ );
	}
    
	///-------------------------------------------------------------------
	// Spread pixels randomly within image by specified ammount
	///-------------------------------------------------------------------
	void            Image::Spread ( unsigned int amount_ )
	{
		image->spread( amount_ );
	}
    
	///-------------------------------------------------------------------
	// Add a digital watermark to the image (based on second image)
	///-------------------------------------------------------------------
	void            Image::Stegano ( Image ^watermark_ )
	{
		image->stegano( *(watermark_->image) );
	}
    
	///-------------------------------------------------------------------
	// Create an image which appears in stereo when viewed with
	// red-blue glasses (Red image on left, blue on right)
	///-------------------------------------------------------------------
	void            Image::Stereo ( Image^ rightImage_ )
	{
		image->stereo( *(rightImage_->image)) ;
	}
    
	///-------------------------------------------------------------------
	// Swirl image (image pixels are rotated by degrees)
	///-------------------------------------------------------------------
	void            Image::Swirl ( double degrees_ )
	{
		image->swirl( degrees_ );
	}
    
	///-------------------------------------------------------------------
	// Channel a texture on image background
	///-------------------------------------------------------------------
	void            Image::Texture ( Image^ texture_ )
	{
		image->texture( *(texture_->image));
	}
    
	///-------------------------------------------------------------------
	// Threshold image
	///-------------------------------------------------------------------
	void            Image::Threshold ( double threshold_ )
	{
		image->threshold(threshold_);
	}
    
	///-------------------------------------------------------------------
	// Transform image based on image and crop geometries
	// Crop geometry is optional
	///-------------------------------------------------------------------
	void            Image::Transform ( Geometry ^imageGeometry_ )
	{
		image->transform( *(imageGeometry_->geometry) );
	}
	void            Image::Transform ( Geometry ^imageGeometry_,
		Geometry ^cropGeometry_  )
	{
		image->transform( *(imageGeometry_->geometry), *(cropGeometry_->geometry) );
	}

	///-------------------------------------------------------------------
	// Add matte image to image, setting pixels matching color to
	// transparent
	///-------------------------------------------------------------------
	void            Image::Transparent ( Color ^color_ )
	{
		image->transparent( *(color_->color) );
	}
    
	///-------------------------------------------------------------------
	// Trim edges that are the background color from the image
	///-------------------------------------------------------------------
	void            Image::Trim ( void )
	{
		image->trim();
	}


	///-------------------------------------------------------------------
	// Image representation type (also see type attribute)
	//   Available types:
	//    Bilevel        Grayscale       GrayscaleMatte
	//    Palette        PaletteMatte    TrueColor
	//    TrueColorMatte ColorSeparation ColorSeparationMatte
	///-------------------------------------------------------------------
	void            Image::Type ( ImageType type_ )
	{
		image->type( (MagickCore::ImageType)type_ );
	}

	///-------------------------------------------------------------------
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
	///-------------------------------------------------------------------
	void            Image::Unsharpmask ( double radius_,
								  double sigma_,
								  double amount_,
								  double threshold_ )
	{
		image->unsharpmask( radius_, sigma_, amount_, threshold_ );
	}

	///-------------------------------------------------------------------
	// Map image pixels to a sine wave
	///-------------------------------------------------------------------
	void            Image::Wave ( double amplitude_ ,
						   double wavelength_ )
	{
		image->wave( amplitude_, wavelength_ );
	}


	///===================================================================
	/// properties
	///===================================================================


	///-------------------------------------------------------------------
	// Image width
	///-------------------------------------------------------------------
	unsigned int    Image::Columns::get ( void )
	{
		return image->columns();
	}

	///-------------------------------------------------------------------
	/// Sets the compression type.
	///-------------------------------------------------------------------
	void Image::CompressType::set( ImageMagickNET::CompressionType compressType )
	{
		image->compressType( (Magick::CompressionType)compressType );
	}


	///-------------------------------------------------------------------
	/// Gets the compression type
	///-------------------------------------------------------------------
	ImageMagickNET::CompressionType Image::CompressType::get()
	{
		return (ImageMagickNET::CompressionType) image->compressType();
	}

	///-------------------------------------------------------------------
	/// Sets the compression quality.
	///-------------------------------------------------------------------
	void			Image::Quality::set( unsigned int quality )
	{
		image->quality(quality);
	}


	///-------------------------------------------------------------------
	/// Gets the compression quality.
	///-------------------------------------------------------------------
	unsigned int    Image::Quality::get()
	{
		return image->quality();
	}


	///-------------------------------------------------------------------
	// The number of pixel rows in the image
	///-------------------------------------------------------------------
	unsigned int    Image::Rows::get ( void )
	{
		return image->rows();
	}

	///-------------------------------------------------------------------
	/// Sets the image format.
	///-------------------------------------------------------------------
	void			Image::Format::set( String^ format )
	{
		image->magick(Marshaller::SystemStringToStdString(format));
	}


	///-------------------------------------------------------------------
	/// Gets the image format.
	///-------------------------------------------------------------------
	String^    Image::Format::get()
	{
		return Marshaller::StdStringToSystemString(image->magick());
	}


	///===================================================================
	/// IO
	///===================================================================

	///-------------------------------------------------------------------
	/// Load an image from the specified file path.
	///-------------------------------------------------------------------
	void Image::Read(System::String^ imageSpec)
	{
		image->read(Marshaller::SystemStringToStdString(imageSpec));
	}


	///-------------------------------------------------------------------
	// Read single image frame of specified size into current object
	///-------------------------------------------------------------------
	void            Image::Read ( Geometry^ size_,
							System::String^ imageSpec_ )
	{
		image->read( *(size_->geometry), Marshaller::SystemStringToStdString(imageSpec_));
	}


	///-------------------------------------------------------------------
	/// Save an image to the specified file path.
	///-------------------------------------------------------------------
	void Image::Write(System::String^ imageSpec)
	{
		image->write(Marshaller::SystemStringToStdString(imageSpec));
	}


	///-------------------------------------------------------------------
	// convert to bitmap
	///-------------------------------------------------------------------
	System::Drawing::Bitmap^ Image::ToBitmap()
	{
		System::Drawing::Bitmap^ bitmap = 
			gcnew System::Drawing::Bitmap(image->columns(), image->rows(), 
			System::Drawing::Imaging::PixelFormat::Format24bppRgb);

		System::Drawing::Imaging::BitmapData^ bitmapData = bitmap->LockBits( 
			System::Drawing::Rectangle(0,0,image->columns(), image->rows()), 
			System::Drawing::Imaging::ImageLockMode::ReadWrite,
			System::Drawing::Imaging::PixelFormat::Format24bppRgb);

		unsigned char *ptr = (unsigned char *) bitmapData->Scan0.ToPointer();
		std::string map = "BGR";
		for( int i=0; i<image->rows(); i++ )
		{
			image->write(
				0, i, image->columns(), 1, map,
				MagickCore::CharPixel, (void *)ptr);
			ptr += bitmapData->Stride;
		}

		bitmap->UnlockBits(bitmapData);
		return bitmap;
	}

}

