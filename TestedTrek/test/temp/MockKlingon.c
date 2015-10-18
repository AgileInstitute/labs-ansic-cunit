#include <StarTrek/Klingon.h>
#include <MockKlingon.h>

MockKlingon::MockKlingon(int distance) : deleteCalled_(false) {
    distance_ = distance;
}

MockKlingon::MockKlingon(int distance, int energy) : deleteCalled_(false) {
    distance_ = distance;
    this->energy(energy);
}

void MockKlingon::destroy() {
    deleteCalled_ = true;
}

bool MockKlingon::deleteWasCalled() {
    return deleteCalled_;
}
