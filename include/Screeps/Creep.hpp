#ifndef SCREEPS_CREEP_H
#define SCREEPS_CREEP_H

#include "JSON.hpp"
#include "RoomObject.hpp"

#include <optional>

namespace Screeps {

class ConstructionSite;
class Resource;
class Source;
class Store;
class Structure;
class StructureController;

/**
 * Creeps are your units. Creeps can move, harvest energy, construct structures, attack another creeps, and perform other actions. Each creep consists of up to 50 body parts
 */
class Creep : public RoomObject
{
public:
	struct Body
	{
		std::optional<std::string> boost;
		std::string type;
		int hits;
	};

	explicit Creep(JS::Value);

    /**
     * An array describing the creep’s body
     * @return A std::vector with the body parts
     */
	[[nodiscard]] std::vector<Body> body() const;

    /**
     * The movement fatigue indicator. If it is greater than zero, the creep cannot move.
     * @return the fatigue value
     */
    [[nodiscard]] int fatigue() const;

    /**
     * The current amount of hit points of the creep.
     * @return hit points
     */
    [[nodiscard]] int hits() const;

    /**
     * The maximum amount of hit points of the creep.
     * @return max hit points
     */
    [[nodiscard]] int hitsMax() const;

    /**
     * A unique object identificator.
     * @return the id
     */
    [[nodiscard]] std::string id() const;

    /**
     * Memory of the creep
     * @return JSON representation of the memory
     */
    [[nodiscard]] JSON memory() const;

    /**
     * Set the memory of the creep (overwrites)
     * @param memory JSON representation of memory to overwrite
     */
	void setMemory(const JSON& memory);

    [[nodiscard]] bool my() const;

    [[nodiscard]] std::string name() const;

    [[nodiscard]] std::string owner() const;

    [[nodiscard]] std::string saying() const;

    [[nodiscard]] bool spawning() const;

    [[nodiscard]] Store store() const;

    [[nodiscard]] int ticksToLive() const;

	int attack(const RoomObject& target);

	int attackController(const StructureController& target);

	int build(const ConstructionSite& target);

	int cancelOrder(const std::string& methodName);

	int claimController(const StructureController& target);

	int dismantle(const Structure& target);

	int drop(const std::string& resourceType, std::optional<int> amount);

	int generateSafeMode(const StructureController& target);

	int getActiveBodyParts(const std::string& type);

	int harvest(const Source& target);

	int heal(const Creep& target);

	int move(const Creep& direction);
	int move(int direction);

	// int moveByPath(...);
    /**
     *
     * @param x X position of the target in the same room.
     * @param y Y position of the target in the same room.
     * @param options Additional options for moving.
     * @return A status code indicating OK or ERR codes.
     */
	int moveTo(int x, int y, const std::optional<JSON>& options = std::nullopt);
    /**
     * Find the optimal path to the target within the same room and move to it.
     * @param target A RoomPosition object. The position doesn't have to be in the same room with the creep.
     * @param options Additional options for moving.
     * @return A status code indicating OK or ERR codes.
     */
	int moveTo(const RoomPosition& target, const std::optional<JSON>& options = std::nullopt);

    /**
     * Find the optimal path to the target within the same room and move to it.
     * @param target Any object containing RoomPosition. The position doesn't have to be in the same room with the creep.
     * @param options Addional options for moving.
     * @return A status code indicating OK or ERR codes.
     */
	int moveTo(const RoomObject& target, const std::optional<JSON>& options = std::nullopt);

	int notifyWhenAttacked(bool enabled);

	int pickup(const Resource& target);

	int pull(const Creep& target);

	int rangedAttack(const Creep& target);
	int rangedAttack(const Structure& target);

	int rangedHeal(const Creep& target);

	int rangedMassAttack();

	int repair(const Structure& target);

	int reserveController(const StructureController& target);

    /**
     * Display a visual speech balloon above the creep with the specified message. The message will be available for one tick.
     * @param message The message to be displayed. Maximum length is 10 characters.
     * @param visibleToAll Set to true to allow other players to see this message. Default is false.
     * @return One of the following codes OK, ERR_NOT_OWNER or ERR_busy
     */
	int say(const std::string& message, bool visibleToAll = false);

	int signController(const StructureController& target, const std::string& text);

	int suicide();

	int transfer(const Creep& target,
	             const std::string& resourceType,
	             const std::optional<int>& amount = std::nullopt);
	int transfer(const Structure& target,
	             const std::string& resourceType,
	             const std::optional<int>& amount = std::nullopt);

    /**
     * Upgrade your controller to the next level using carried energy.
     * @param target The target controller object to be upgraded.
     * @return A status code indicating OK or ERR codes.
     */
	int upgradeController(const StructureController& target);

	int withdraw(const RoomObject& target,
	             const std::string& resourceType,
	             const std::optional<int>& amount = std::nullopt);
};

} // namespace Screeps

#endif // SCREEPS_CREEP_H
