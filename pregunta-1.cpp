#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <set>
#include <vector>

#define ODIO_CPP true

int main() {
  std::vector<int> P = {8, 20, 10, 3, 50, 2, 5};
  std::vector<int> U = {10, 2, 50, 8, 20, 5, 3};
  std::vector<int> A = std::vector<int>(P.size(), -1);

  auto asignados = std::set<size_t>();

  // O(n^2)
  for (auto u = U.begin(); u != U.end(); u++) { // O(n)
    auto idx = std::distance(U.begin(), u);

    while (ODIO_CPP) { // O(n)
      auto index = std::rand() % P.size();
      if (asignados.count(index) && P[index] == *u) {
        A[idx] = index;
        asignados.insert(index);
        break;
      }
    }
  }
}
