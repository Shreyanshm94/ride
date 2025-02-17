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
};

class Vehicle {
public:
    int vehicleId;
    std::string driverName;
    Location currentLocation;
    bool isAvailable;

    // Default constructor
    Vehicle() : vehicleId(0), driverName(""), currentLocation(Location()), isAvailable(true) {}

    // Parameterized constructor
    Vehicle(int id, const std::string& name, const Location& location) 
        : vehicleId(id), driverName(name), currentLocation(location), isAvailable(true) {}

    double calculateDistance(const Location& loc) const {
        return currentLocation.distanceTo(loc);
    }
};

class RideSharingSystem {
private:
    std::unordered_map<int, Vehicle> vehicles; // vehicleId -> Vehicle
    std::queue<RideRequest> rideQueue;

public:
    void addVehicle(int id, const std::string& driverName, const Location& location) {
        vehicles[id] = Vehicle(id, driverName, location);
    }

    void requestRide(int requestId, const Location& start, const Location& destination) {
        RideRequest request(requestId, start, destination);
        rideQueue.push(request);
        processRideRequest();
    }

private:
    void processRideRequest() {
        if (rideQueue.empty()) return;

        RideRequest request = rideQueue.front();
        rideQueue.pop();

        double minDistance = std::numeric_limits<double>::max();
        int chosenVehicleId = -1;

        // Using explicit iterator type to avoid 'auto' warning
        for (std::unordered_map<int, Vehicle>::iterator it = vehicles.begin(); it != vehicles.end(); ++it) {
            int id = it->first;
            Vehicle& vehicle = it->second;

            if (vehicle.isAvailable) {
                double distance = vehicle.calculateDistance(request.start);
                if (distance < minDistance) {
                    minDistance = distance;
                    chosenVehicleId = id;
                }
            }
        }

        if (chosenVehicleId != -1) {
            assignRide(chosenVehicleId, request);
        } else {
            std::cout << "No available vehicles at the moment. Ride request queued." << std::endl;
        }
    }

    void assignRide(int vehicleId, const RideRequest& request) {
        Vehicle& vehicle = vehicles[vehicleId];
        vehicle.isAvailable = false;
        std::cout << "Ride assigned to Vehicle " << vehicleId << " driven by " << vehicle.driverName << std::endl;
        std::cout << "Pickup location: (" << request.start.x << ", " << request.start.y << ")\n";
        std::cout << "Destination: (" << request.destination.x << ", " << request.destination.y << ")\n";

        // Simulate ride completion
        completeRide(vehicleId, request.destination);
    }

    void completeRide(int vehicleId, const Location& destination) {
        Vehicle& vehicle = vehicles[vehicleId];
        vehicle.currentLocation = destination;
        vehicle.isAvailable = true;
        std::cout << "Ride completed by Vehicle " << vehicleId << ". Vehicle is now available." << std::endl;
    }
};

int main() {
    RideSharingSystem system;
    int numVehicles, numRequests;

    // Take input for vehicles
    std::cout << "Enter the number of vehicles: ";
    std::cin >> numVehicles;

    for (int i = 0; i < numVehicles; ++i) {
        int vehicleId;
        std::string driverName;
        int x, y;

        std::cout << "Enter vehicle " << i + 1 << " details:\n";
        std::cout << "Vehicle ID: ";
        std::cin >> vehicleId;
        std::cout << "Driver Name: ";
        std::cin >> driverName;
        std::cout << "Current Location (x y): ";
        std::cin >> x >> y;

        system.addVehicle(vehicleId, driverName, Location(x, y));
    }

    // Take input for ride requests
    std::cout << "Enter the number of ride requests: ";
    std::cin >> numRequests;

    for (int i = 0; i < numRequests; ++i) {
        int requestId, xStart, yStart, xDest, yDest;

        std::cout << "Enter ride request " << i + 1 << " details:\n";
        std::cout << "Request ID: ";
        std::cin >> requestId;
        std::cout << "Pickup Location (x y): ";
        std::cin >> xStart >> yStart;
        std::cout << "Destination Location (x y): ";
        std::cin >> xDest >> yDest;

        system.requestRide(requestId, Location(xStart, yStart), Location(xDest, yDest));
    }

    return 0;
}
 
