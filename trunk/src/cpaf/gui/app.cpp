/*!
    \file src/cpaf/gui/app.cpp
    \brief Implementation of cpaf::gui::App
    \date Created: 2005-04-07
*/

#include <cpaf/gui/app.h>
#include <cpaf/gui/toplevel.h>

namespace {
    cpaf::gui::TopLevelList top_level_widgets;
}

cpaf::gui::App::App()
{
    // implementation specific gui initialization
    gui_init();
}

void cpaf::gui::App::quit()
{
    //! \todo send APP_QUIT

    // close all top levels
    for( TopLevelList::const_iterator i = get_top_level_widgets().begin(), end = get_top_level_widgets().end(); i != end; )
    {
        TopLevel *t = *i;

        // increment the iterator before we close the TopLevel
        // the act of closing the TopLevel could invalidate the iterator if we didnt.
        ++i;

        //! \todo call close() instead of destroy()
        t->destroy();
    }

    // tell the implementation to terminate the application
    _quit();
}

const cpaf::gui::TopLevelList &cpaf::gui::App::get_top_level_widgets()
{
    return top_level_widgets;
}

void cpaf::gui::App::add_top_level(TopLevel *t)
{
    top_level_widgets.push_back(t);
}

template<class T> class equals
{
private:
    T _t;
public:
    equals(T t)
        : _t(t)
    { }

    bool operator() (T t)
    {
        return _t == t;
    }
};

void cpaf::gui::App::remove_top_level(TopLevel *t)
{
    top_level_widgets.remove_if(equals<TopLevel*>(t));
}
