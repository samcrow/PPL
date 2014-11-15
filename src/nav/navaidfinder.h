#ifndef NAVAIDFINDER_H
#define NAVAIDFINDER_H
#include "navaid.h"
#include "latlon.h"
#include <vector>
#include <memory>
#include <iterator>
#include <functional>

namespace PPLNAMESPACE {

/**
 * Searches for navaids.
 *
 * An instance of this class can be used to chain criteria.
 */
class NavaidFinder
{
public:

    typedef std::vector< std::shared_ptr< Navaid > > list_type;

    /**
     * Adds a criterion to include only navaids of the specified
     * type or types.
     *
     * @param types Type(s) to include. This can be a bitwise combination
     * of Types.
     * @return *this
     */
    NavaidFinder& type(Navaid::Type types);

    /**
     * Adds a criterion to only include navaids within a specified
     * distance of a center point
     * @param position The point to center on
     * @param maxDistance The maximum distance, in meters, from the center point
     * @return *this
     */
    NavaidFinder& proximity(LatLon position, double maxDistance);

    /**
     *
     * @return All navaids that meet the criteria set by calling other methods
     */
    list_type search();

    // Utility functions

    /**
     * Returns a list of all navaids in the database.
     *
     * Because there may be many navaids and each navaid
     * does at least one navigation database query when
     * it is created, this function may be very slow
     * and will use lots of memory.
     *
     * @return
     */
    static list_type findAllNavaids();

    /**
     * Returns a list of all navaids of the provided type(s) in the databse.
     *
     * Type values can be combined using bitwise operators.
     *
     * @param type
     * @return
     */
    static list_type findNavaidsWithType(Navaid::Type type);

private:

    /// A function object that takes an XPLMNavRef and returns
    /// true if the corresponding navaid should be included
    typedef std::function< bool ( XPLMNavRef ) > criterion;

    std::vector< criterion > criteria;

    /// Iterates over XPLMNavRefs.
    /// Meets the requirements of InputIterator.
    class NavRefIterator : public std::iterator< std::input_iterator_tag, XPLMNavRef, XPLMNavRef> {
    public:

        reference operator * () {
            return ref;
        }
        // Post-increment
        NavRefIterator operator ++ (int) {
            NavRefIterator original = *this;
            this->next();
            return original;
        }
        // Pre-increment
        // Returns the updated value
        NavRefIterator& operator ++ () {
            this->operator ++();
            return *this;
        }

        friend bool operator == (NavRefIterator left, NavRefIterator right) {
            return left.ref == right.ref;
        }
        friend bool operator != (NavRefIterator left, NavRefIterator right) {
            return !(left == right);
        }

        static NavRefIterator begin() {
            return NavRefIterator(XPLMGetFirstNavAid());
        }
        static NavRefIterator end() {
            return NavRefIterator(XPLM_NAV_NOT_FOUND);
        }

    private:
        NavRefIterator(XPLMNavRef ref) :
            ref(ref)
        {
        }

        void next() {
            ref = XPLMGetNextNavAid(ref);
        }

        XPLMNavRef ref;
    };



};

}
#endif // NAVAIDFINDER_H
