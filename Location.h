#ifndef PROJECT_LOCATION_H
#define PROJECT_LOCATION_H

enum class Location : int {
    HUB = 10000,
    NOHUB = 100000
};

Location otherLocation(Location location);

#endif //PROJECT_LOCATION_H
