//
//  ISOBMFF.h
//  ISOBMFF
//
//  Created by QiuDong on 2018/8/16.
//  Copyright © 2018年 XS-Labs. All rights reserved.
//

#import <Cocoa/Cocoa.h>

//! Project version number for ISOBMFF.
FOUNDATION_EXPORT double ISOBMFFVersionNumber;

//! Project version string for ISOBMFF.
FOUNDATION_EXPORT const unsigned char ISOBMFFVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <ISOBMFF_macOS/PublicHeader.h>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/Utils.hpp>
#include <ISOBMFF/Parser.hpp>
#include <ISOBMFF/BinaryStream.hpp>
#include <ISOBMFF/DisplayableObject.hpp>
#include <ISOBMFF/DisplayableObjectContainer.hpp>
#include <ISOBMFF/Box.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <ISOBMFF/Container.hpp>
#include <ISOBMFF/ContainerBox.hpp>
#include <ISOBMFF/File.hpp>
#include <ISOBMFF/Matrix.hpp>
#include <ISOBMFF/FTYP.hpp>
#include <ISOBMFF/MVHD.hpp>
#include <ISOBMFF/TKHD.hpp>
#include <ISOBMFF/META.hpp>
#include <ISOBMFF/HDLR.hpp>
#include <ISOBMFF/PITM.hpp>
#include <ISOBMFF/IINF.hpp>
#include <ISOBMFF/DREF.hpp>
#include <ISOBMFF/URL.hpp>
#include <ISOBMFF/URN.hpp>
#include <ISOBMFF/ILOC.hpp>
#include <ISOBMFF/IREF.hpp>
#include <ISOBMFF/INFE.hpp>
#include <ISOBMFF/IROT.hpp>
#include <ISOBMFF/HVCC.hpp>
#include <ISOBMFF/SingleItemTypeReferenceBox.hpp>
#include <ISOBMFF/DIMG.hpp>
#include <ISOBMFF/THMB.hpp>
#include <ISOBMFF/CDSC.hpp>
#include <ISOBMFF/COLR.hpp>
#include <ISOBMFF/ISPE.hpp>
#include <ISOBMFF/IPMA.hpp>
#include <ISOBMFF/PIXI.hpp>
#include <ISOBMFF/IPCO.hpp>
#include <ISOBMFF/ImageGrid.hpp>
#include <ISOBMFF/STSD.hpp>
#include <ISOBMFF/FRMA.hpp>
#include <ISOBMFF/SCHM.hpp>

#ifdef _WIN32
#include <ISOBMFF/WIN32.hpp>
#endif

