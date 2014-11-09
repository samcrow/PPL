#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H
#include "../namespaces.h"
#include <chrono>

namespace PPLNAMESPACE {

/**
 * Differentiates a value over time
 */
class Differentiator
{
public:
    Differentiator();

    bool hasFirst() const;
    void setFirst(double first);

    double differentiate(double newValue);

private:

    double previous;

    typedef std::chrono::high_resolution_clock clock;
    typedef clock::duration duration;
    typedef clock::time_point time_point;

    time_point lastValueTime;
};

}
#endif // DIFFERENTIATOR_H
