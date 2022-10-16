#ifndef JS_HPP
#define JS_HPP

#include <emscripten/val.h>
#include <nlohmann/json_fwd.hpp>

#include <map>
#include <string>
#include <vector>

using JSON = nlohmann::json;

namespace JS {

using Value = emscripten::val;

// Global JS scope
const static Value gGlobal = Value::global();

// Global JS Object
const static Value gObject = Value::global("Object");

Value getGlobal(char const* name);
Value getGlobal(const std::string& name);
Value getConstant(const std::string& name);

bool isInstanceOf(const Value& val, const char* name);

/**
 * Converts a JS array to a std::vector of JS Value
 * @tparam T Type to the value(default JS::Value)
 * @param object the object to convert
 * @return A std::vector of the array values
 */

template <typename T = Value>
std::vector<T> jsArrayToVector(const Value& array)
{
	std::vector<T> result;
	int size = array["length"].as<int>();
	result.reserve(size);
	for (int i = 0; i < size; ++i)
		result.emplace_back(array[i].as<T>());
	return result;
}

/**
 * Converts a JS object to a std::map of string and JS Value
 * @tparam T Type to the value(default JS::Value)
 * @param object the object to convert
 * @return A std::map of the object keys to values
 */

template <typename T = Value>
std::map<std::string, T> jsObjectToMap(const Value& object)
{
	std::map<std::string, T> result;
	Value keys = gObject.call<Value>("keys", object);
	int size = keys["length"].as<int>();
	for (int i = 0; i < size; ++i)
	{
		auto key = keys[i].as<std::string>();
		result.emplace_hint(result.end(), key, object[key].as<T>());
	}
	return result;
}

/**
 * Converts a vector to JS Array
 * @param vector a std::vector
 * @return JS Value
 */
template <typename T>
Value vectorToJSArray(const std::vector<T>& vector)
{
	Value array = Value::array();
	for (std::size_t i = 0; i < vector.size(); i++)
		array.set(i, static_cast<JS::Value>(vector[i]));
	return array;
}

/**
 * Converts C++ map to JS object
 * @tparam K Key
 * @tparam T Value
 * @param map A map of type key and value
 * @return JS Object from the given map
 */

template <typename K, typename T>
Value mapToJSObject(const std::map<K, T>& map)
{
	Value object = Value::object();
	for (const auto& pair : map)
		object.set(pair.first, pair.second);
	return object;
}

/**
 * Convenience function for converting JSON to JS Value.
 * @param json
 * @return JS::Value parsed from the JSON
 */

Value fromJSON(const JSON& json);

/**
 * Convenience function to convert a JS value to JSON
 * @param value Any JS::Value
 * @return JSON representation of this value.
 */

JSON toJSON(const Value& value);

/**
 * class Console provides a convenient way to access the JS console. Pass it Embindable values or JSON
 */

class Console
{
public:
	Console();

    /**
     * A wrapper for console.log
     */

	template <typename... Args>
	void log(Args&&... args)
	{
		object_.call<void>("log", std::forward<Args>(args)...);
	}

private:
	Value object_;
};
/**
 * A global variable for easy access to JS console.
 */
extern Console console;

} // namespace JS

#endif // JS_HPP
