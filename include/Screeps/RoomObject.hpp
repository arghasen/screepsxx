#ifndef SCREEPS_ROOM_OBJECT_HPP
#define SCREEPS_ROOM_OBJECT_HPP

#include "Object.hpp"

namespace Screeps {

class Effect;
class RoomPosition;
class Room;
/**
 * Any object with a position in a room. Almost all game objects prototypes are derived from RoomObject
 */
class RoomObject : public Object
{
public:
	explicit RoomObject(JS::Value value);

	virtual ~RoomObject();

	std::vector<Effect> effects() const;

	RoomPosition pos() const;

    /**
     * Gets the room the current structure/creep is in
     * @return The Room
     */
	Room room() const;
};

std::unique_ptr<RoomObject> createRoomObject(JS::Value object);

template <typename T>
bool is(const std::unique_ptr<RoomObject>& ptr)
{
	return dynamic_cast<T*>(ptr.get());
}

} // namespace Screeps

#endif // SCREEPS_ROOM_OBJECT_HPP
