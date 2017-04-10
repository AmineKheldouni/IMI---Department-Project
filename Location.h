#include <vector>

using namespace std;

enum class Location : int {
    PARIS = 10000,
    LONDRES = 100000,
    NEWYORK = 500000,
    AMSTERDAM = 20000
};

Location nextLocation(const vector<Location> &vectorLocation, int position);


