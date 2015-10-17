#ifndef SECURITY_EXCHANGE_TRASMISSION_INTERFACE_HEADER
#define SECURITY_EXCHANGE_TRASMISSION_INTERFACE_HEADER

namespace ITC {

class SecurityExchangeTransmissionInterface {
public:
	virtual double currentPrice(const char* symbol) = 0;
	virtual ~SecurityExchangeTransmissionInterface();
};

}

#endif
