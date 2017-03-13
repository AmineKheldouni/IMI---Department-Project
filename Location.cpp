#include "Location.h"


Location nextLocation(const vector<Location> &vectorLocation, int position) {
    position = position % vectorLocation.size();
    if (position == vectorLocation.size() - 1) {
        return vectorLocation[0];
    }
    else {
        return vectorLocation[position + 1];
    }
}