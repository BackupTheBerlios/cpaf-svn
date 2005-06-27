/*!
    \file include/cpaf/gui/factory.h
    \brief cpaf::gui::factory::create_widget template
    \date Created: 2005-06-27
*/

#ifndef CPAF_GUI_FACTORY_H
#define CPAF_GUI_FACTORY_H

namespace cpaf {
    namespace gui {
        namespace factory {

/*!
    \brief Factory function to create cpaf::gui objects.
*/
template<typename Widget> Widget *create_widget(typename Widget::Initializer const &initializer)
{
    Widget *wrapper = new Widget;

    // create the native widget passing it a copy of the data contained in the initializer
    wrapper->create(initializer);

    return wrapper;
}

        } // factory
    } // gui
} // cpaf

#endif // CPAF_GUI_FACTORY_H
