#include "basicgraphicscontext.h"

namespace PPLNAMESPACE {

BasicGraphicsContext::BasicGraphicsContext(float top, float bottom, float left, float right) :
    top_(top),
    bottom_(bottom),
    left_(left),
    right_(right)
{
}

const Color& BasicGraphicsContext::fillColor() {
    return fillColor_;
}

const Color& BasicGraphicsContext::strokeColor() {
    return strokeColor_;
}

float BasicGraphicsContext::strokeWidth() {
    return strokeWidth_;
}

void BasicGraphicsContext::setStroke(const Color& newStrokeColor)
{
    strokeColor_ = newStrokeColor;
}

void BasicGraphicsContext::setStrokeWidth(float width)
{
    strokeWidth_ = width;
}

void BasicGraphicsContext::setFill(const Color& newFillColor)
{
    fillColor_ = newFillColor;
}

float BasicGraphicsContext::top() {
    return top_;
}
float BasicGraphicsContext::bottom() {
    return bottom_;
}
float BasicGraphicsContext::left() {
    return left_;
}
float BasicGraphicsContext::right() {
    return right_;
}

}
