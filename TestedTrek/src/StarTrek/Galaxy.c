#include "Galaxy.h"

#include <string>
#include "../Untouchables/WebGadget.h"


/**
 * A simple Proxy/wrapper class for Untouchables.WebGadget,
 * allowing us to create, modify, and subclass (or mock) Galaxy.
 * Note that this object currently has no tests, because it does nothing but delegate,
 * which is not likely to break, and the delegation is not unit-testable.
 * Note also that it is production code.
 */

using namespace std;

namespace StarTrek {

Galaxy::Galaxy(Untouchables::WebGadget* webContext) : webContext_(webContext) {
}

string Galaxy::parameter(string parameterName) {
    return webContext_->parameter(parameterName);
}

void* Galaxy::variable(string variableName) {
    return webContext_->variable(variableName);
}

void Galaxy::writeLine(string message) {
    webContext_->writeLine(message);
}

}
