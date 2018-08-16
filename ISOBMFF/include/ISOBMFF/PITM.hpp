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
 * @header      PITM.hpp
 * @copyright   (c) 2017, DigiDNA - www.digidna.net
 * @author      Jean-David Gadina - www.digidna.net
 */

#ifndef ISOBMFF_PITM_HPP
#define ISOBMFF_PITM_HPP

#include <ISOBMFF/Object.hpp>
#include <ISOBMFF/Macros.hpp>
#include <ISOBMFF/FullBox.hpp>
#include <cstdint>

namespace ISOBMFF
{
    class ISOBMFF_EXPORT PITM: public FullBox, public XS::PIMPL::Object< PITM >
    {
        public:
            
            using XS::PIMPL::Object< PITM >::impl;
            
            PITM( void );
            
            void                                                 ReadData( Parser & parser, BinaryStream & stream ) override;
            std::vector< std::pair< std::string, std::string > > GetDisplayableProperties( void ) const override;
            
            uint32_t GetItemID( void ) const;
            
            void SetItemID( uint32_t value );
    };
}

#endif /* ISOBMFF_PITM_HPP */
