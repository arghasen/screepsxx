#ifndef SCREEPS_STRUCTURE_SPAWN_HPP
#define SCREEPS_STRUCTURE_SPAWN_HPP

#include "OwnedStructure.hpp"

#include <optional>

namespace Screeps {

class Creep;
class Store;

class StructureSpawn : public OwnedStructure
{
public:
	class Spawning;

	explicit StructureSpawn(JS::Value obj);

	JSON memory() const;
	void setMemory(const JSON&);

	std::string name() const;

	std::optional<Spawning> spawning() const;

	Store store() const;

    /**
     * Start the creep spawning process.
     * @param body A vector defining the body parts
     * @param name name of the creep
     * @return Return Code of the action as defined in constants.
     */
	int spawnCreep(const std::vector<std::string>& body, const std::string& name);

    /**
     * Start the creep spawning process.
     * @param body A vector defining the body parts
     * @param name name of the creep
     * @param options An object with additional options for the spawning process.
     * @return Return Code of the action as defined in constants.
     */
    int spawnCreep(const std::vector<std::string>& body, const std::string& name, const JSON& options);

    /**
     * Kill the creep and drop up to 100% of resources spent on its spawning and boosting depending on remaining life time. The target should be at adjacent square. Energy return is limited to 125 units per body part.
     * @param target Creep to recycle
     * @return Return Code of the action as defined in constants.
     */
	int recycleCreep(const Creep& target);

    /**
     * Increase the remaining time to live of the target creep.
     * @param target Creep to renew
     * @return Return Code of the action as defined in constants.
     */
	int renewCreep(const Creep& target);
};

class StructureSpawn::Spawning : public Object
{
public:
	explicit Spawning(JS::Value value);

	std::vector<int> directions() const;

	std::string name() const;

	int needTime() const;

	int remainingTime() const;

	StructureSpawn spawn();

	int cancel();

	int setDirections(const std::vector<int>& directions);
};

} // namespace Screeps

#endif // SCREEPS_STRUCTURE_SPAWN_HPP
