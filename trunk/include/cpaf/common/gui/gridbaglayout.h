/*!
    \file include/cpaf/common/gui/gridbaglayout.h
    \brief Grid Bag Layout Manager implementation declarations
    \date Created: 2005-10-16
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

#include <cpaf/api/gui/layoutmanager.h>
#include <cpaf/gui/gridbaglayout.h>

#include <set>
#include <list>
#include <map>

namespace cpaf {
    namespace common {
        namespace gui { 

            /*!
                Namespace to tuck away the implementation details for the Grid Bag
                layout manager
            */
            namespace gblm {

enum GROUP {
    COLUMN,
    ROW,
};

const int DEFAULT_WEIGHT = 1;

class LayoutData
{
public:
    LayoutData();

    /*!
        Contains bit flags for expansion and alignment information
    */
    int flags;

    /*!
        Padding values
    */
    int pad_left, pad_top, pad_right, pad_bottom;

    /*!
        Placement information
    */
    unsigned int col, row, col_span, row_span;
};

struct ObjectInfo
{
    //! What widget is this information for
    boost::weak_ptr<cpaf::gui::Object> object;

    cpaf::Size m_min_size;
    cpaf::Size m_max_size;
    cpaf::Size m_natural_size;
    cpaf::Rect m_rect;

    //! The information for this widget
    LayoutData data;

    ObjectInfo(boost::weak_ptr<cpaf::gui::Object> o, const LayoutData &d) : object(o), data(d) { }

    bool operator < (const ObjectInfo &other) const
    {
        return object < other.object;
    }
};

typedef std::list<ObjectInfo> Objects;
typedef std::map<int, ObjectInfo *> GroupObjects;

/*!
    Stores information for each group for processing
*/
struct GroupData {
    GroupObjects m_objects;
    bool m_done;
    float m_weight;
    float m_min_size;
    cpaf::Rect m_rect;

    GroupData(float weight = DEFAULT_WEIGHT)
        : m_done(false),
        m_weight(weight),
        m_min_size(0)
    { }

    /*!
        \return True if this group is empty (it has no widgets)
    */
    bool empty() const { return m_objects.empty(); }
};

typedef std::map<int, GroupData> Groups;

            } // gblm

class GridBagLayout : public cpaf::api::gui::LayoutManager
{
public:
    GridBagLayout();

    // LayoutManager interface
    void assign(boost::weak_ptr<cpaf::gui::Panel> panel);
    void remove(boost::weak_ptr<cpaf::gui::Object> object);
    void invalidate();

    void add(boost::weak_ptr<cpaf::gui::Object> object, const cpaf::gui::GridBagLayoutInfo &info);
    void set_column_weight(int column, float weight);
    void set_row_weight(int row, float weight);
    void set_column_gap(float gap);
    void set_row_gap(float gap);
    void set_gap(float gap);
    void set_margins(float margin);
    void set_margins(float left, float top, float right, float bottom);
    void set_left_margin(float margin);
    void set_top_margin(float margin);
    void set_right_margin(float margin);
    void set_bottom_margin(float margin);

    // Object interface
    void set_size(const cpaf::Size&);
    void set_min_size(const cpaf::Size&);
    void set_max_size(const cpaf::Size&);
    void set_natural_size(const cpaf::Size&);
    void set_position(const cpaf::Point&);
    void set_rect(const cpaf::Rect&);
    cpaf::Size get_size() const;
    cpaf::Size get_min_size() const;
    cpaf::Size get_max_size() const;
    cpaf::Size get_natural_size() const;
    cpaf::Point get_position() const;
    cpaf::Rect get_rect() const;

private:
    typedef std::map<boost::weak_ptr<cpaf::gui::Object>, cpaf::Rect> ObjectRects;

    // the panel this gblm is managing
    boost::weak_ptr<cpaf::gui::Panel> m_panel;

    mutable cpaf::Rect m_rect;
    mutable cpaf::Size m_min_size, m_max_size, m_natural_size;

    /*!
        If this value is true, the values for m_min_size, m_max_size, and m_natural_size
        need to be recalculated.
    */
    mutable bool m_values_invalid;

    mutable gblm::Objects m_objects;
    mutable gblm::Groups m_rows, m_columns;
    mutable int m_non_empty_rows, m_non_empty_columns;

    float m_row_gap, m_column_gap;
    float m_margin_top, m_margin_left, m_margin_right, m_margin_bottom;

    /*!
        Update the positions and sizes of all widgets
    */
    void update_layout();

    /*!
        Updates the cache of Object sizes if necessary
    */
    void update_sizes() const;

    /*!
        Updates the cached min and max size values for each group
    */
    template<gblm::GROUP> void update_group_sizes() const;

    /*!
        \return a reference to the existing column with this index.
            If a column for this index doesn't exist, it will be created.
    */
    float &get_column_weight(int index);

    /*!
        \return a reference to the existing row with this index.
            If a row for this index doesn't exist, it will be created.
    */
    float &get_row_weight(int index);

    /*!
        Calculates the sizes of the widgets contained in this objects columns or rows
        based on the template parameter
    */
    template<gblm::GROUP> void calc_group_sizes();

    /*!
        \return The group info indexed by rows or columns based on the template parameter
    */
    template<gblm::GROUP> gblm::Groups &get_objects() const; 

    /*!
        \return The group data for a given row or column based on the template parameter
    */
    template<gblm::GROUP> gblm::GroupData &get_group_data(int index) const;

    /*!
        \return A reference to the height or width of the given size based on the template parameter
    */
    template<gblm::GROUP> float &get_size_value(cpaf::Size &size) const;

    /*!
        \return The height of width of the given size based on the template parameter.
    */
    template<gblm::GROUP> float get_size_value(const cpaf::Size &size) const;

    /*!
        \return A reference to the x or y value of the given position based on the template parameter
    */
    template<gblm::GROUP> float &get_pos_value(cpaf::Point &pos) const;

    /*!
        \return The x or y value of the given position based on the template parameter
    */
    template<gblm::GROUP> float get_pos_value(const cpaf::Point &pos) const;

    /*!
        Returns either the left and right or top and bottom padding values from the given data
            based on the template parameter through the pad1 and pad2 arguments.
    */
    template<gblm::GROUP> void get_pad_values(const gblm::LayoutData &data, float &pad1, float &pad2) const;

    /*!
        Returns either the left and right or top and bottom margin values
            based on the template parameter through the margin1 and margin2 arguments.
    */
    template<gblm::GROUP> void get_margin_values(float &margin1, float &margin2) const;

    /*!
        \return The gap between rows or columns based on the template parameter
    */
    template<gblm::GROUP> float get_gap() const;

    /*!
        \return The number of groups which contain objects that effect the layout
    */
    template<gblm::GROUP> int &get_non_empty_groups() const;

    /*!
        \return An objects group spanning value
    */
    template<gblm::GROUP> int get_group_span(const gblm::LayoutData &data) const;
};
        } // gui
    } // common
} // cpaf
