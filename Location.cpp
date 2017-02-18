#include "Location.h"

Location otherLocation(Location location) {
    if (location == Location::HUB) {
        return Location ::NOHUB;
    }
    else {
        return Location ::HUB;
    }
}