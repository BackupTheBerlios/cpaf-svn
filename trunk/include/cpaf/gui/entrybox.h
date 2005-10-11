/*!
    \file include/cpaf/gui/entrybox.h
    \brief cpaf::gui::EntryBox declaration
    \date Created: 2005-07-14
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

#ifndef CPAF_GUI_ENTRYBOX_H
#define CPAF_GUI_ENTRYBOX_H

#include <cpaf/gui/textwidget.h>
#include <cpaf/gui/initializer/entrybox.h>

namespace cpaf {
    namespace gui {

class CPAF_API EntryBox : public TextWidget
{
public:
    typedef cpaf::api::gui::EntryBox api_type;
    typedef EntryBoxInitializer Initializer;

    static boost::shared_ptr<EntryBox> create(const Initializer &initializer);

    void set_password_mode(bool mode);
    bool get_password_mode() const;

protected:
    EntryBox();
    EntryBox(api_type *impl);

    /*!
        \brief Constructs the native widget using the given initializer
    */
    boost::shared_ptr<EntryBox> initialize(const Initializer &initializer);

private:
    api_type *m_impl;

public:
    api_type *get_impl() const;
};

    } // gui
} // cpaf

#endif
