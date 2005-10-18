
/*!
    \file include/cpaf/gridbaglayout.h
    \brief Grid Bag Layout Manager declaration
    \date Created: 2005-08-31
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

#ifndef CPAF_GUI_GRIDBAG_H
#define CPAF_GUI_GRIDBAG_H

#include <cpaf/gui/layoutmanager.h>

namespace cpaf {
    namespace common {
        namespace gui {
            class GridBagLayout;
            namespace gblm { class LayoutData; }
        } // gui
    } // common

    namespace gui {

/*!
    Layout flags for the grid bag layout manager. The default flags
    specify that the widget will be centered both vertically and horizontally
    within its alloted space and will not be expanded in either direction.
*/
class CPAF_API GridBagLayoutInfo
{
public:
    /*!
        Flags controlling the placement of the Object within the layout.

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
        ALIGN_LEFT              = 1,
        ALIGN_RIGHT             = 2,
        ALIGN_CENTER_HORIZONTAL = 3,
        ALIGN_TOP               = 1 << 2,
        ALIGN_BOTTOM            = 2 << 2,
        ALIGN_CENTER_VERTICAL   = 3 << 2,
        ALIGN_CENTER            = ALIGN_CENTER_HORIZONTAL | ALIGN_CENTER_VERTICAL,
        EXPAND_HORIZONTAL       = 1 << 4,
        EXPAND_VERTICAL         = 2 << 4,
        EXPAND_BOTH             = 3 << 4,
    };

    GridBagLayoutInfo();

    /*!
        \brief Specify flags controlling the placement of objects within the layout.
        You can specify both alignment and ex

        \param flags A combination of LAYOUT_FLAGS
    */
    GridBagLayoutInfo &flags(int flags);

    /*!
        \return The current combination of layout flags
    */
    int get_flags() const;

    GridBagLayoutInfo &position(unsigned int col, unsigned int row);
    GridBagLayoutInfo &column(unsigned int col);
    GridBagLayoutInfo &row(unsigned int row);

    /*!
        \brief Specifies the group spanning values for this object. A value of
        1 means that the object only spans one group, which is the default value.
    */
    GridBagLayoutInfo &span(unsigned int col, unsigned int row);
    GridBagLayoutInfo &col_span(unsigned int span);
    GridBagLayoutInfo &row_span(unsigned int span);

    GridBagLayoutInfo &padding(int pad);
    GridBagLayoutInfo &padding(int left, int top, int right, int bottom);
    GridBagLayoutInfo &padding_left(int pad);
    GridBagLayoutInfo &padding_right(int pad);
    GridBagLayoutInfo &padding_top(int pad);
    GridBagLayoutInfo &padding_bottom(int pad);

    const cpaf::common::gui::gblm::LayoutData &get_data() const;

private:
    boost::shared_ptr<cpaf::common::gui::gblm::LayoutData> m_data;
};

/*!
    A grid bag layout manager
*/
class CPAF_API GridBagLayout : public LayoutManager
{
public:
    typedef cpaf::common::gui::GridBagLayout api_type;

    GridBagLayout();

    /*!
        Adds a widget to this layout manager with the given layout info.
    */
    void add(boost::weak_ptr<Object> object, const GridBagLayoutInfo &info);

    /*!
        Sets the weight value for a given column
    */
    GridBagLayout &set_column_weight(int column, float weight);

    /*!
        Sets the weight value for a given row
    */
    GridBagLayout &set_row_weight(int row, float weight);

    /*!
        Specifies the amount of gap inbetween columns
    */
    GridBagLayout &set_column_gap(float gap);

    /*!
        Specifies the amount of gap inbetween rows
    */
    GridBagLayout &set_row_gap(float gap);

    /*!
        Specifies the amount of gap inbetween rows and columns
    */
    GridBagLayout &set_gap(float gap);

    /*!
        Sets the margins for all sides
    */
    GridBagLayout &set_margins(float margin);

    /*!
        Sets the margins for all sides
    */
    GridBagLayout &set_margins(float left, float top, float right, float bottom);

    /*!
        Sets the left margin
    */
    GridBagLayout &set_left_margin(float margin);

    /*!
        Sets the top margin
    */
    GridBagLayout &set_top_margin(float margin);

    /*!
        Sets the right margin
    */
    GridBagLayout &set_right_margin(float margin);

    /*!
        Sets the bottom margin
    */
    GridBagLayout &set_bottom_margin(float margin);

private:
    api_type *m_impl;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_GRIDBAG_H
