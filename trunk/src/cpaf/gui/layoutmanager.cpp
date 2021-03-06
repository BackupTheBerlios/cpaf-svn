/*!
    \file src/cpaf/gui/layoutmanager.cpp
    \brief Layout Manager implementation
    \date Created: 2005-08-24
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

#include <cpaf/gui/layoutmanager.h>
#include <cpaf/gui/widget.h>
#include <cpaf/api/gui/layoutmanager.h>

using namespace cpaf::gui;

LayoutManager::LayoutManager(api_type *impl)
    : Object(impl),
    m_impl(impl)
{

}

LayoutManager::~LayoutManager() { }

void LayoutManager::remove(boost::weak_ptr<Object> object)
{
    m_impl->remove(object);
}

void LayoutManager::invalidate()
{
    m_impl->invalidate();
}

void LayoutManager::assign(boost::weak_ptr<cpaf::gui::Panel> panel)
{
    m_impl->assign(panel);
}
