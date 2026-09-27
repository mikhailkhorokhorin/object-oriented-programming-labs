#pragma once

class Point {
public:
    Point(int x = 0, int y = 0);

    int getX() const;
    int getY() const;

    double distanceTo(const Point& other) const;

    bool operator==(const Point& other) const = default;

private:
    int x_;
    int y_;
};
