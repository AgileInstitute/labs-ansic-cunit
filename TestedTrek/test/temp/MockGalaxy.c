#include <string>
#include <map>

#include <StarTrek/Galaxy.h>
#include <MockGalaxy.h>

using namespace std;

namespace Untouchables {
    class WebGadget;
}

string galaxyOutput;
map<string, void*> galaxyDictionary;

namespace StarTrek {

Galaxy::Galaxy(Untouchables::WebGadget* webGadget) : webContext_(webGadget)  {
}

string StarTrek::Galaxy::parameter(string parameterName) {
    string* result = (string*)galaxyDictionary[parameterName];

    return *result; 
}

void* StarTrek::Galaxy::variable(string variableName) {
    return galaxyDictionary[variableName];
}

void StarTrek::Galaxy::writeLine(string message) {
    string fakeNewLine = " || ";
    galaxyOutput += message;
    galaxyOutput += fakeNewLine;
}

}

