/*!
    \file include/cpaf/flags.h
    \brief Defines all flags which are used throughout the library
    \date Crated: 2005-10-18
*/

/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CPAF_FLAGS_H
#define CPAF_FLAGS_H

namespace cpaf {
    namespace flags {

        /*!
            \brief Flags controlling the placement of the Object within the layout. These flags
            are used by GridBagLayoutInfo and GridBagLayout

            Mutually exclusive flags:
                {ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER_HORIZONTALORIZONTAL}
                {ALIGN_TOP, ALIGN_BOTTOM, ALIGN_CENTER_VERTICALERTICAL}
            Combinations of mutually exclusive flags will result in undefined behavior.

            If no flags are specified, the default combation of flags is ALIGN_LEFT | ALIGN_TOP.
            
            If a combination of EXPAND flags and ALIGN flags are made which both effect the same axis
            (horizontal or vertical), the EXPAND flag will have priority unless the maximal size
            of an Object is exceeded, in which case the EXPAND flag will be ignored and the
            ALIGN flag will be used instead.
            
            If an EXPAND flag was set but no ALIGN flag was set and an Objects maximal size is
            exceeded, the EXPAND flag will be ignored and ALIGN_LEFT | ALIGN_TOP is assumed.
        */
        enum LAYOUT_FLAGS {
            ALIGN_LEFT              = 0x01,
            ALIGN_RIGHT             = 0x02,
            ALIGN_CENTER_HORIZONTAL = 0x04,
            ALIGN_TOP               = 0x08,
            ALIGN_BOTTOM            = 0x10,
            ALIGN_CENTER_VERTICAL   = 0x20,
            ALIGN_CENTER            = ALIGN_CENTER_HORIZONTAL | ALIGN_CENTER_VERTICAL,
            EXPAND_HORIZONTAL       = 0x40,
            EXPAND_VERTICAL         = 0x80,
            EXPAND_BOTH             = EXPAND_HORIZONTAL | EXPAND_VERTICAL,
        };

    } // flags
} // cpaf

#endif // CPAF_FLAGS_H
