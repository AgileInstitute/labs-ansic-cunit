#include <exception>

class LunExServiceUnavailableException : public std::exception {
public:
	virtual const char* what(); 
};
