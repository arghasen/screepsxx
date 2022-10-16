#ifndef SCREEPS_GAME_HPP
#define SCREEPS_GAME_HPP

#include "Object.hpp"

#include <memory>

namespace Screeps {

class ConstructionSite;
class Creep;
class Flag;
class GameMap;
class GameMarket;
class PowerCreep;
class Room;
class RoomObject;
class StructureSpawn;
class Structure;

class GameObject : public Object
{
public:
	struct GCL
	{
		int level;
		int progress;
		int progressTotal;
	};
	using GPL = GCL;

	struct Shard
	{
		std::string name;
		std::string type;
		bool ptr;
	};

	GameObject();

    /**
     * A hash containing all your construction sites with their id as hash keys.
     * @return A map of ids to the construction sites
     */
	std::map<std::string, ConstructionSite> constructionSites() const;

    /**
     * An object containing information about your CPU usage
     * @return The object is returned as JSON with all the CPU properties
     */
	JSON cpu() const;

    /**
     *
     * @return
     */
	std::map<std::string, Creep> creeps() const;

	std::map<std::string, Flag> flags() const;

	GCL gcl() const;

	GPL gpl() const;

	GameMap map() const;

	GameMarket market() const;

	std::map<std::string, PowerCreep> powerCreeps() const;

	std::map<std::string, int> resources() const;

	std::map<std::string, Room> rooms() const;

	Shard shard() const;

	std::map<std::string, StructureSpawn> spawns() const;

	std::map<std::string, Structure> structures() const;

    /**
     * System game tick counter. It is automatically incremented on every tick
     * @return the tick value
     */
	int time() const;

	JSON cpuGetHeapStatistics();

	double cpuGetUsed();

	void cpuHalt();

	int cpuSetShardLimits(const std::map<std::string, int>& limits);

	int cpuUnlock();

	int cpuGeneratePixel();

	std::unique_ptr<RoomObject> getObjectById(const std::string& id);

	void notify(const std::string& message, int groupInterval = 0);
};

extern GameObject Game;

} // namespace Screeps

#endif // SCREEPS_GAME_HPP
