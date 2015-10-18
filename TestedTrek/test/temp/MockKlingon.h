#ifndef MOCK_KLINGON_H
#define MOCK_KLINGON_H

#include <StarTrek/Klingon.h>

class MockKlingon : public StarTrek::Klingon {
private:
    bool deleteCalled_;

public:
    MockKlingon(int distance);

    MockKlingon(int distance, int energy);

    virtual void destroy(); 

    bool deleteWasCalled();
};

#endif
