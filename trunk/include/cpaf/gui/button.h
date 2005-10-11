/*!
    \file include/cpaf/gui/button.h
    \brief cpaf::gui::Button declaration
    \date Created: 2005-04-05
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

#ifndef CPAF_GUI_BUTTON_H
#define CPAF_GUI_BUTTON_H

#include <cpaf/gui/widget.h>
#include <cpaf/gui/initializer/button.h>

namespace cpaf {
    namespace gui {

class CPAF_API Button : public Widget
{
public:
    typedef cpaf::api::gui::Button api_type;
    typedef ButtonInitializer Initializer;

    static boost::shared_ptr<Button> create(const Initializer &initializer);

    /*!
        \brief Sets the label of the button

        \todo Move this to the common base
    */
    void set_label(const std::string &label);

    /*!
        \return The button label

        \todo Move this to the common base
    */
    std::string get_label() const;

private:
    api_type *m_impl;

protected:
    Button();
    Button(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initialization data
    */
    boost::shared_ptr<Button> initialize(const Initializer &initializer);

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_BUTTON_H
