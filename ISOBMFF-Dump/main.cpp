/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 DigiDNA - www.digidna.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        main.cpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#include <ISOBMFF.hpp>
#include "MadvMP4Boxes.h"
#include <iostream>
#include <fstream>
#include <cstring>

inline int32_t readLittleEndianInt32(const void* ptr) {
    const uint8_t* bytes = (const uint8_t*)ptr;
    int32_t ret = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
    return ret;
}

inline int32_t readBigEndianInt32(const void* ptr) {
    const uint8_t* bytes = (const uint8_t*)ptr;
    int32_t ret = bytes[3] | (bytes[2] << 8) | (bytes[1] << 16) | (bytes[0] << 24);
    return ret;
}

inline int16_t readLittleEndianInt16(const void* ptr) {
    const uint8_t* bytes = (const uint8_t*)ptr;
    int32_t ret = bytes[0] | (bytes[1] << 8);
    return (int16_t)ret;
}

inline int16_t readBigEndianInt16(const void* ptr) {
    const uint8_t* bytes = (const uint8_t*)ptr;
    int32_t ret = bytes[1] | (bytes[0] << 8);
    return (int16_t)ret;
}

void enumerateInBoxes(const void* data, int size, void(*callback)(void* context, uint32_t boxType, uint8_t* boxData, int boxSize, bool* stop), void* context);

void handleBox(void* context, uint32_t boxType, uint8_t* boxData, int boxSize, bool* stop);

void enumerateInBoxes(const void* data, int size, void(*callback)(void* context, uint32_t boxType, uint8_t* boxData, int boxSize, bool* stop), void* context) {
    bool stop = false;
    uint8_t* pRead = (uint8_t*)data;
    for (int iRead = 0; iRead < size;)
    {
        uint32_t* pReadInt = (uint32_t*)pRead;
        int boxSize = readBigEndianInt32(pReadInt++);
        uint32_t boxType = (uint32_t)readLittleEndianInt32(pReadInt++);
        
        if (NULL != callback)
        {
            callback(context, boxType, (uint8_t*)pReadInt, boxSize - 2 * (int)sizeof(uint32_t), &stop);
            if (stop)
                break;
        }
        
        pRead += boxSize;
        iRead += (2 * (int)sizeof(uint32_t) + boxSize);
    }
}

void handleBox(void* context, uint32_t boxType, uint8_t* boxData, int boxSize, bool* stop) {
    printf("boxType=0x%x, boxSize=%d, boxData=0x%lx, context=0x%lx\n", boxType, boxSize, (long)boxData, (long)context);
    *stop = false;
    switch (boxType)
    {
        case MADV_MP4_USERDATA_MADV:
            enumerateInBoxes(boxData, boxSize, handleBox, context);
            break;
        case MADV_MP4_USERDATA_TAG_TYPE:
            break;
        case MADV_MP4_USERDATA_BEAUTY_TYPE:
            break;
        case MADV_MP4_USERDATA_CAMERA_INFO_TYPE:
            break;
        case MADV_MP4_USERDATA_GPS_TYPE:
            break;
        case MADV_MP4_USERDATA_LUT_TYPE:
        {
            MADV_MP4_USERDATA_LUT_t* pLUTStruct = (MADV_MP4_USERDATA_LUT_t*)boxData;
            printf("LUT size = %d\n", pLUTStruct->size);
        }
            break;
        case MADV_MP4_USERDATA_GYRO_TYPE:
            break;
        default:
            break;
    }
}

using namespace ISOBMFF;

class CustomBox: public ISOBMFF::Box
{
public:
    
    CustomBox( void ): Box( "caif" )
    {}
    
    void ReadData( ISOBMFF::Parser & parser, ISOBMFF::BinaryStream & stream )
    {
        /* Read box data here... */
        std::cout << *(parser.GetFile()) << std::endl;
        stream.DeleteBytes(0);
    }
    
    std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const
    {
        /* Returns box properties, to support output... */
        return {};
    }
};

int main( int argc, const char * argv[] )
{
    ISOBMFF::Parser parser;
    std::string     path;
    int             i;
    std::ifstream   stream;
    
    if( argc < 2 )
    {
        std::cerr << "No input file provided" << std::endl;

        #if defined( _WIN32 ) && defined( _DEBUG )
        getchar();
        #endif
        
        return EXIT_FAILURE;
    }
    
    for( i = 1; i < argc; i++ )
    {
        path   = argv[ i ];
        stream = std::ifstream( path );
        
        if( path.length() == 0 || stream.good() == false )
        {
            std::cerr << "Input file does not exist: '" << path << "'" << std::endl;

            #if defined( _WIN32 ) && defined( _DEBUG )
            getchar();
            #endif
            
            return EXIT_FAILURE;
        }
        
        stream.close();
        
        try
        {
            parser.AddOption( ISOBMFF::Parser::Options::SkipMDATData );
            parser.RegisterBox( "caif", [ = ]( void ) -> std::shared_ptr< CustomBox > { return std::make_shared< CustomBox >(); } );
            parser.Parse( path );
        }
        catch( const std::runtime_error & e )
        {
            std::cerr << e.what() << std::endl;

            #if defined( _WIN32 ) && defined( _DEBUG )
            getchar();
            #endif
            
            return EXIT_FAILURE;
        }
        std::shared_ptr< ISOBMFF::File > file = parser.GetFile();
        std::vector<std::shared_ptr< ISOBMFF::Box > > boxes = file->GetBoxes();
        for (std::shared_ptr< ISOBMFF::Box > box : boxes)
        {
            std::cout << "Box '" << box->GetName().c_str() << "': " << *box << std::endl;
            if (0 == strcmp(box->GetName().c_str(), "moov"))
            {
                ISOBMFF::ContainerBox* containerBox = static_cast<ISOBMFF::ContainerBox*>(box.get());
                std::vector< std::shared_ptr< Box > > subBoxes = containerBox->GetBoxes();
                for (std::shared_ptr< ISOBMFF::Box > subBox : subBoxes)
                {
                    if (0 == strcmp(subBox->GetName().c_str(), "udta"))
                    {
                        std::vector<uint8_t> userData = subBox->GetData();
                        int boxBytesSize = (int)userData.size();
                        std::cout << "udta length = " << boxBytesSize << std::endl;
                        enumerateInBoxes(userData.data(), boxBytesSize, handleBox, NULL);
                        return EXIT_SUCCESS;
                    }
                }
            }
        }
//        std::cout << *file << std::endl << std::endl;
    }

//    #if defined( _WIN32 ) && defined( _DEBUG )
//    getchar();
//    #endif
    return EXIT_SUCCESS;
}
