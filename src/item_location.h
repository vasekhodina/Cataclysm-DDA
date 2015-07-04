#ifndef ITEM_LOCATION_H
#define ITEM_LOCATION_H

#include <memory>

struct point;
struct tripoint;
class item;
class Character;
class vehicle;
class item_location;

class impl
{
protected:
    const item *what;
public:
    virtual ~impl() = default;
    /** Removes the selected item from the game */
    virtual void remove_item() = 0;
    /** Gets the selected item or nullptr */
    virtual item *get_item() = 0;
    /** Gets the position of item in character's inventory or INT_MIN */
    virtual int get_inventory_position()
    {
        return INT_MIN;
    }
};

/**
 * A class for easy removal of used items.
 * Ensures the item exists, but not that the character/vehicle does.
 * Should not be kept, but removed before the end of turn.
 */
class item_location
{
private:
    std::unique_ptr<impl> ptr;
    item_location( impl* );
public:
    item_location( item_location&& ) = default;
    /** Factory functions for readability */
    /*@{*/
    static item_location nowhere();
    static item_location on_map( const tripoint &p, const item *which );
    static item_location on_character( Character &ch, const item *which );
    static item_location on_vehicle( vehicle &v, const point &where, const item *which );
    /*@}*/

    /** Removes the selected item from the game */
    void remove_item();
    /** Gets the selected item or nullptr */
    item *get_item();
    /** Gets the position of item in character's inventory or INT_MIN */
    int get_inventory_position();
};

#endif
