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
///=======================================================================

#include "Magick++.h"
#pragma once

namespace ImageMagickNET
{
	public enum class StorageType 
	{
		UndefinedPixel = MagickCore::UndefinedPixel,
		CharPixel = MagickCore::CharPixel,
		DoublePixel = MagickCore::DoublePixel,
		FloatPixel = MagickCore::FloatPixel,
		IntegerPixel = MagickCore::IntegerPixel,
		LongPixel = MagickCore::LongPixel,
		QuantumPixel = MagickCore::QuantumPixel,
		ShortPixel = MagickCore::ShortPixel
	};


	public enum class CompressionType
	{
		UndefinedCompression = MagickCore::UndefinedCompression,
		  NoCompression = MagickCore::NoCompression,
		  BZipCompression = MagickCore::BZipCompression,
		  FaxCompression = MagickCore::FaxCompression,
		  Group4Compression = MagickCore::Group4Compression,
		  JPEGCompression = MagickCore::JPEGCompression,
		  JPEG2000Compression = MagickCore::JPEG2000Compression,
		  LosslessJPEGCompression = MagickCore::LosslessJPEGCompression,
		  LZWCompression = MagickCore::LZWCompression,
		  RLECompression = MagickCore::RLECompression,
		  ZipCompression = MagickCore::ZipCompression
	};


	public enum class ChannelType
	{
		UndefinedChannel = Magick::UndefinedChannel,
		RedChannel = 0x0001,
		GrayChannel = 0x0001,
		CyanChannel = 0x0001,
		GreenChannel = 0x0002,
		MagentaChannel = 0x0002,
		BlueChannel = 0x0004,
		YellowChannel = 0x0004,
		AlphaChannel = 0x0008,
		OpacityChannel = 0x0008,
		MatteChannel = 0x0008,/* deprecated */
		BlackChannel = 0x0020,
		IndexChannel = 0x0020,
		AllChannels = 0xff,
		DefaultChannels = (AllChannels &~ OpacityChannel)
	} ;

	public enum class NoiseType
	{
		UndefinedNoise = MagickCore::UndefinedNoise,
		  UniformNoise = MagickCore::UniformNoise,
		  GaussianNoise = MagickCore::GaussianNoise,
		  MultiplicativeGaussianNoise = MagickCore::MultiplicativeGaussianNoise,
		  ImpulseNoise = MagickCore::ImpulseNoise,
		  LaplacianNoise = MagickCore::LaplacianNoise,
		  PoissonNoise = MagickCore::PoissonNoise
	};

	public enum class PaintMethod
	{
		UndefinedMethod = MagickCore::UndefinedMethod,
		PointMethod = MagickCore::PointMethod,
		ReplaceMethod = MagickCore::ReplaceMethod,
		FloodfillMethod = MagickCore::FloodfillMethod,
		FillToBorderMethod = MagickCore::FillToBorderMethod,
		ResetMethod = MagickCore::ResetMethod
	};


	public enum class CompositeOperator
	{
		UndefinedCompositeOp = MagickCore::UndefinedCompositeOp,
		NoCompositeOp = MagickCore::NoCompositeOp,
	  AddCompositeOp = MagickCore::AddCompositeOp,
	  AtopCompositeOp = MagickCore::AtopCompositeOp,
	  BlendCompositeOp = MagickCore::BlendCompositeOp,
	  BumpmapCompositeOp = MagickCore::BumpmapCompositeOp,
	  ClearCompositeOp = MagickCore::ClearCompositeOp,
	  ColorBurnCompositeOp = MagickCore::ColorBurnCompositeOp,
	  ColorDodgeCompositeOp = MagickCore::ColorDodgeCompositeOp,
	  ColorizeCompositeOp = MagickCore::ColorizeCompositeOp,
	  CopyBlackCompositeOp = MagickCore::CopyBlackCompositeOp,
	  CopyBlueCompositeOp = MagickCore::CopyBlueCompositeOp,
	  CopyCompositeOp = MagickCore::CopyCompositeOp,
	  CopyCyanCompositeOp = MagickCore::CopyCyanCompositeOp,
	  CopyGreenCompositeOp = MagickCore::CopyGreenCompositeOp,
	  CopyMagentaCompositeOp = MagickCore::CopyMagentaCompositeOp,
	  CopyOpacityCompositeOp = MagickCore::CopyOpacityCompositeOp,
	  CopyRedCompositeOp = MagickCore::CopyRedCompositeOp,
	  CopyYellowCompositeOp = MagickCore::CopyYellowCompositeOp,
	  DarkenCompositeOp = MagickCore::DarkenCompositeOp,
	  DstAtopCompositeOp = MagickCore::DstAtopCompositeOp,
	  DstCompositeOp = MagickCore::DstCompositeOp,
	  DstInCompositeOp = MagickCore::DstInCompositeOp,
	  DstOutCompositeOp = MagickCore::DstOutCompositeOp,
	  DstOverCompositeOp = MagickCore::DstOverCompositeOp,
	  DifferenceCompositeOp = MagickCore::DifferenceCompositeOp,
	  DisplaceCompositeOp = MagickCore::DisplaceCompositeOp,
	  DissolveCompositeOp = MagickCore::DissolveCompositeOp,
	  ExclusionCompositeOp = MagickCore::ExclusionCompositeOp,
	  HardLightCompositeOp = MagickCore::HardLightCompositeOp,
	  HueCompositeOp = MagickCore::HueCompositeOp,
	  InCompositeOp = MagickCore::InCompositeOp,
	  LightenCompositeOp = MagickCore::LightenCompositeOp,
	  LuminizeCompositeOp = MagickCore::LuminizeCompositeOp,
	  MinusCompositeOp = MagickCore::MinusCompositeOp,
	  ModulateCompositeOp = MagickCore::ModulateCompositeOp,
	  MultiplyCompositeOp = MagickCore::MultiplyCompositeOp,
	  OutCompositeOp = MagickCore::OutCompositeOp,
	  OverCompositeOp = MagickCore::OverCompositeOp,
	  OverlayCompositeOp = MagickCore::OverlayCompositeOp,
	  PlusCompositeOp = MagickCore::PlusCompositeOp,
	  ReplaceCompositeOp = MagickCore::ReplaceCompositeOp,
	  SaturateCompositeOp = MagickCore::SaturateCompositeOp,
	  ScreenCompositeOp = MagickCore::ScreenCompositeOp,
	  SoftLightCompositeOp = MagickCore::SoftLightCompositeOp,
	  SrcAtopCompositeOp = MagickCore::SrcAtopCompositeOp,
	  SrcCompositeOp = MagickCore::SrcCompositeOp,
	  SrcInCompositeOp = MagickCore::SrcInCompositeOp,
	  SrcOutCompositeOp = MagickCore::SrcOutCompositeOp,
	  SrcOverCompositeOp = MagickCore::SrcOverCompositeOp,
	  SubtractCompositeOp = MagickCore::SubtractCompositeOp,
	  ThresholdCompositeOp = MagickCore::ThresholdCompositeOp,
	  XorCompositeOp = MagickCore::XorCompositeOp
	};


	public enum class GravityType
	{
		UndefinedGravity = MagickCore::UndefinedGravity,
		  ForgetGravity = 0,
		  NorthWestGravity = 1,
		  NorthGravity = 2,
		  NorthEastGravity = 3,
		  WestGravity = 4,
		  CenterGravity = 5,
		  EastGravity = 6,
		  SouthWestGravity = 7,
		  SouthGravity = 8,
		  SouthEastGravity = 9,
		  StaticGravity = 10
	} ;


	public enum class MagickEvaluateOperator
	{
		UndefinedEvaluateOperator = MagickCore::UndefinedEvaluateOperator,
	  AddEvaluateOperator = MagickCore::AddEvaluateOperator,
	  AndEvaluateOperator = MagickCore::AndEvaluateOperator,
	  DivideEvaluateOperator = MagickCore::DivideEvaluateOperator,
	  LeftShiftEvaluateOperator = MagickCore::LeftShiftEvaluateOperator,
	  MaxEvaluateOperator = MagickCore::MaxEvaluateOperator,
	  MinEvaluateOperator = MagickCore::MinEvaluateOperator,
	  MultiplyEvaluateOperator = MagickCore::MultiplyEvaluateOperator,
	  OrEvaluateOperator = MagickCore::OrEvaluateOperator,
	  RightShiftEvaluateOperator = MagickCore::RightShiftEvaluateOperator,
	  SetEvaluateOperator = MagickCore::SetEvaluateOperator,
	  SubtractEvaluateOperator = MagickCore::SubtractEvaluateOperator,
	  XorEvaluateOperator = MagickCore::XorEvaluateOperator
	} ;


	public enum class ImageType
	{
		UndefinedType = MagickCore::UndefinedType,
	  BilevelType = MagickCore::BilevelType,
	  GrayscaleType = MagickCore::GrayscaleType,
	  GrayscaleMatteType = MagickCore::GrayscaleMatteType,
	  PaletteType = MagickCore::PaletteType,
	  PaletteMatteType = MagickCore::PaletteMatteType,
	  TrueColorType = MagickCore::TrueColorType,
	  TrueColorMatteType = MagickCore::TrueColorMatteType,
	  ColorSeparationType = MagickCore::ColorSeparationType,
	  ColorSeparationMatteType = MagickCore::ColorSeparationMatteType,
	  OptimizeType = MagickCore::OptimizeType,
	  PaletteBilevelMatteType = MagickCore::PaletteBilevelMatteType
	} ;


}