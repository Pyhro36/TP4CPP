#ifndef SEGMENT_H
#define SEGMENT_H

#include "Polygon.h"

/// class Segment - 
class Segment : public Polygon {
    // Operations
public:
    Segment(const std::string & name, const Point & firstPoint, const Point & secondPoint);
    virtual bool contain(const Point & point) const;
    std::string describe() const;

private:
    bool isBetween(int x,int firstBound,int secondBound) const;
};

#endif