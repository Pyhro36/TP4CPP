#ifndef SEGMENT_H
#define SEGMENT_H

#include "Polygon.h"

/// class Segment - 
class Segment : public Polygon {
    // Operations
public:
    Segment(std::string name, Point firstPoint, Point secondPoint);
    virtual bool contain(Point point) const;
    std::string describe() const;

private:
    bool isBetween(int x,int firstBound,int secondBound) const;
};

#endif