/*!
    \file include/cpaf/gui/app.h
    \brief cpaf::gui::App declaration
    \date Created: 2005-04-07
*/

#ifndef CPAF_GUI_APP_H
#define CPAF_GUI_APP_H

#include <cpaf/app.h>

#include <list>

namespace cpaf {
    namespace gui {
        class TopLevel;

        typedef std::list<TopLevel*> TopLevelList;

class CPAF_API App : public cpaf::App
{
protected:
    App();

public:
    virtual bool init() = 0;

    /*
        This function must be implemented by an implementation (win32, gtk2, ...).
    */
    int run();

    /*!
        Quits the application.

        Firstly, this function sends the APP_QUITTING event. If this event is not vetoed,
        it will then iterate over all TopLevel widgets and close() them. If all windws are
        closed, the application will terminate.
    */
    void quit();

    /*!
        \return A list containing all TopLevel widgets in the application. Note
            that the returned list is const. If you need to remove a TopLevel widget,
            use destroy() or close(). You cannot remove it directly from this list.
    */
    static const TopLevelList &get_top_level_widgets();

private:
    /*!
        Called by the constructor, and implemented by an implementation for port specific initialization.

        If gui initialization fails for what ever reason (no X server for a *nix port), an exception will
        be thrown.
    */
    void gui_init();

    /*!
        Called by quit(). Must be implemented by an implementation. Its purpose is to
        notify an implementation that the application must terminate. It is called after
        all TopLevel widgets have been closed.

        The purpose of this function is to notify the implementation that it should allow
        cpaf::gui::App::run() to return, terminating the application.
    */
    void _quit();

    /*!
        Adds a TopLevel widget to the toplevel widget list
    */
    static void add_top_level(TopLevel *t);

    /*!
        Removes a TopLevel widget from the TopLevel widget list
    */
    static void remove_top_level(TopLevel *t);

    friend class TopLevel;
};

    } // gui
} // cpaf

#endif // CPAF_GUI_APP_H
