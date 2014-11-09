#include "differentiator.h"
#include <cmath>

namespace PPLNAMESPACE {

Differentiator::Differentiator() :
    previous(std::nan(nullptr))
{
}

bool Differentiator::hasFirst() const {
    return !std::isnan(previous);
}

void Differentiator::setFirst(double first) {
    previous = first;
    lastValueTime = clock::now();
}

double Differentiator::differentiate(double newValue) {
    const time_point now = clock::now();
    const double dv = newValue - previous;
    const duration dt = now - lastValueTime;

    previous = newValue;
    lastValueTime = now;
    // Convert to microseconds, then seconds
    return dv / (0.000001 * double(std::chrono::duration_cast<std::chrono::microseconds>(dt).count()));
}

}
