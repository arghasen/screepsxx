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

/**
 * Checks if the RoomObject is an instance of the given type
 * @tparam T A type to check for
 * @param ptr RoomObject unique ptr
 * @return true if the RoomObject is type of the given type
 */
template <typename T>
bool is(const std::unique_ptr<RoomObject>& ptr)
{
	return dynamic_cast<T*>(ptr.get());
}

/**
 * Converts the RoomObject to a pointer of the given type
 * @tparam T A type to check for
 * @param ptr RoomObject unique ptr
 * @return  Pointer to the converted type, or nullptr if type doesnt match
 */
template <typename T>
T* asPtr_safe(const std::unique_ptr<RoomObject>& ptr)
{
    return dynamic_cast<T*>(ptr.get());
}

/**
 * Converts the RoomObject to a pointer of the given type(Undefined behaviour if the type is definitely correct)
 * Faster than the corresponding asPtr_safe function
 * @tparam T A type to check for
 * @param ptr RoomObject unique ptr
 * @return  Pointer to the converted type, or nullptr if type doesnt match
 */
template <typename T>
T* asPtr(const std::unique_ptr<RoomObject>& ptr)
{
    return static_cast<T*>(ptr.get());
}

/**
 * Converts the RoomObject to an instance of the given type
 * @tparam T A type to check for
 * @param ptr RoomObject unique ptr
 * @return  Object of the converted type
 */
template <typename T>
T as_safe(const std::unique_ptr<RoomObject>& ptr)
{
    return *dynamic_cast<T*>(ptr.get());
}

/**
 * Converts the RoomObject to an instance of the given type(Undefined behaviour if the type is definitely correct)
 * Faster than the corresponding as_safe function
 * @tparam T A type to check for
 * @param ptr RoomObject unique ptr
 * @return  Object of the converted type
 */
template <typename T>
T as(const std::unique_ptr<RoomObject>& ptr)
{
    return *static_cast<T*>(ptr.get());
}
} // namespace Screeps

#endif // SCREEPS_ROOM_OBJECT_HPP
