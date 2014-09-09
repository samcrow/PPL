#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H
#include "../namespaces.h"

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

private:

    double previous;
};

}
#endif // DIFFERENTIATOR_H
