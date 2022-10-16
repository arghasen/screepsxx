#ifndef SCREEPS_MEMORY_HPP
#define SCREEPS_MEMORY_HPP

#include "Object.hpp"

#include <string_view>

namespace Screeps {

class MemoryObject : public Object
{
public:
	MemoryObject();

    /**
     * Gets the JSON representation of the object in the Memory
     * NOTE: if the key doesnt exist the JSON parsing fails and throws.
     * @param key
     * @return JSON representation of the object
     */
	JSON operator[](const std::string_view& key);

    /**
     * stores the key and value in Memory
     * @param key  std::string_view as key
     * @param value JSON value to store
     */
	void set(const std::string_view& key, const JSON& value);

    /**
     * checks if the memory value is defined or not
     * @param key
     * @return true if defined, false otherwise
     */
    bool isUndefined(const std::string_view& key);
};

/**
 * Global Memory object that makes it convenient to handle memory operations
 */
extern MemoryObject Memory;

} // namespace Screeps

#endif // SCREEPS_MEMORY_HPP
