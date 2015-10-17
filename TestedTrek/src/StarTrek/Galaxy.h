#include <string>

namespace Untouchables {
    class WebGadget;
}

/**
 * A simple Proxy/wrapper class for Untouchables.WebGadget,
 * allowing us to create, modify, and subclass (or mock) Galaxy.
 * Note that this object currently has no tests, because it does nothing but delegate,
 * and the delegation is not unit-testable.
 * Note also that it is production code.
 */

using namespace std;

namespace StarTrek {

class Galaxy {
private:
    // we had to change this to a reference so we can supply NULL in the ctor,
    // since our link-time mock won't be using it at all
    Untouchables::WebGadget* webContext_;

public:
    Galaxy(Untouchables::WebGadget* webContext); 

    string parameter(string parameterName);

    void* variable(string variableName);

    void writeLine(string message);
};
}
