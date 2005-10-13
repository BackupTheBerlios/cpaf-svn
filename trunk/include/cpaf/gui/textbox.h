/*!
    \file include/cpaf/gui/textbox.h
    \brief cpaf::gui::TextBox declaration
    \date Created: 2005-07-07
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

#ifndef CPAF_GUI_TEXTBOX_H
#define CPAF_GUI_TEXTBOX_H

#include <cpaf/gui/textwidget.h>
#include <cpaf/gui/initializer/textbox.h>

namespace cpaf {
    namespace gui {

class CPAF_API TextBox : public TextWidget
{
public:
    typedef cpaf::api::gui::TextBox api_type;
    typedef TextBoxInitializer Initializer;

    static boost::shared_ptr<TextBox> create(const Initializer &initializer);

protected:
    TextBox();
    TextBox(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    boost::shared_ptr<TextBox> initialize(const Initializer &initializer);

private:
    api_type *m_impl;

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif
