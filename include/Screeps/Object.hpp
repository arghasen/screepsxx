#ifndef SCREEPS_OBJECT_HPP
#define SCREEPS_OBJECT_HPP

#include "JS.hpp"

namespace Screeps {
    /**
     * class Object describes a JS object and as such is the main way to interact with JS data
     */
class Object
{
public:
	using Error = int;

    /**
     * get the underlying JS value (non const version)
     * @return JS value
     */
	JS::Value& value();
    /**
     * get the underlying JS value(const version)
     * @return JS value
     */
	const JS::Value& value() const;
    /**
     * Set the JS Value(as defined by emscripten Val)
     * @param value the value to set
     */
	void setValue(JS::Value value);

    /**
    * get the underlying JS value (non const version, operator based)
    * @return JS value
    */
	operator JS::Value&();

    /**
    * get the underlying JS value (const version, operator based)
    * @return JS value
    */
	operator const JS::Value&() const;

protected:
	Object();
	explicit Object(JS::Value value);
	~Object();

private:
	JS::Value value_;
};

} // namespace Screeps

#endif // SCREEPS_OBJECT_HPP
