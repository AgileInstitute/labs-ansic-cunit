#ifndef WEBGADGET_HEADER
#define WEBGADGET_HEADER

#include <iostream>
#include <string>

using namespace std;

namespace Untouchables {

class WebGadget {
private:
	string commandParameter_;
	string commandArgument_;
	void* targetVariable_;

public:
	WebGadget(string commandParameter, string commandArgument,
			void* targetVariable) : 
		commandParameter_(commandParameter),
		commandArgument_(commandArgument),
		targetVariable_(targetVariable) {
	}

	string parameter(string parameterName) {
		if (parameterName == "command")
			return commandParameter_;
		else
			return commandArgument_;
	}

	void* variable(string variableName) {
		(void)variableName;
		return targetVariable_;
	}

	void writeLine(string message) {
		cout << endl << message << endl;
	}

	// do not implement, to disallow copying by accident
	WebGadget(const WebGadget&);
	WebGadget& operator=(const WebGadget&);

};
}

#endif
