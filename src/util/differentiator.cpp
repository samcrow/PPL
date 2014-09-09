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
}

}
