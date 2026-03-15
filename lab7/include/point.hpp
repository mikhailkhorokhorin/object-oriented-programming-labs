#pragma once

#include <cmath>

class Point {
   private:
    int x;
    int y;

   public:
    Point(int x = 0, int y = 0);

    int getX() const;
    int getY() const;

    double distanceTo(const Point& other) const;
};
