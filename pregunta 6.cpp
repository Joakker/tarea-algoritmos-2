#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m = 3;
    vector<int> boxes = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int n = boxes.size();

    sort(boxes.rbegin(), boxes.rend());

    vector<int> drivers(m, 0);
    for (const auto& box : boxes) {
        int minLoadIndex = min_element(drivers.begin(), drivers.end()) - drivers.begin();
        drivers[minLoadIndex] += box;
    }

    int maxLoad = *max_element(drivers.begin(), drivers.end());
    cout << "Maxima carga p conductor: " << maxLoad << endl;

    return 0;
}
