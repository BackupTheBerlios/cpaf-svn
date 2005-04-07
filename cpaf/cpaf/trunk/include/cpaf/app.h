/*
cpaf::App base application class
*/

#ifndef CPAF_APP_H
#define CPAF_APP_H

#include <cpaf/dllimpexp.h>

namespace cpaf {

class CPAF_EXP App
{
public:
    //! \todo Should I make this not an inilined dtor?
    virtual ~App() { }

    virtual bool init() = 0;
    virtual int run() = 0;
};

} // cpaf

#endif // CPAF_APP_H
