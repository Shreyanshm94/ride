#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>

class Location {
public:
    int x, y;

    Location(int x = 0, int y = 0) : x(x), y(y) {}

    double distanceTo(const Location& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

class RideRequest {
public:
    int requestId;
    Location start, destination;

    RideRequest(int id, const Location& start, const Location& dest) 
        : requestId(id), start(start), destination(dest) {}
