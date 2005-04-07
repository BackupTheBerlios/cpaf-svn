/*
cpaf::App implementation
*/

#include <cpaf/app.h>

const cpaf::App::cmd_line &cpaf::App::get_cmd_line()
{
    return m_cmd;
}

void cpaf::App::set_cmd_line(const cmd_line &cmd)
{
    m_cmd = cmd;
}
