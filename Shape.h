#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "Point.h"

/// class Shape -
class Shape {
    // Attributes
protected:
    std::string name;
    // Operations
public:
    Shape(std::string shapeName);

    virtual bool contain(Point point) const = 0;
    virtual void move(Point vector) = 0;
    virtual std::string describe() const = 0;
    std::string getName();

protected:
    virtual void appendToName(std::string newNameEnding);
};

#endif