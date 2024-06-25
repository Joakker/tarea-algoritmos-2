#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class Equipo {
public:
  // i: numero del equipo
  // n: numero de personas
  int i, n;

  Equipo(int i, int n) {
    this->i = i;
    this->n = n;
  }

  bool operator<(Equipo &other) { return this->n < other.n; }
  bool operator>(Equipo &other) { return this->n > other.n; }
};

class Bus {
public:
  // i: numero del bus
  // p: capacidad de pasajeros
  int i, p;

  // cuantos de cada equipo van en este bus
  std::map<int, int> quien;

  Bus(int i, int p) : i(i), p(p) { this->quien = std::map<int, int>(); }

  bool subir_equipo(std::vector<Equipo> &equipos, int i) {
    if (equipos[i].n == 0) {
      return true;
    }

    auto e = &equipos[i];

    if (e->n == 0) {
      return true;
    }

    if (e->n <= this->p) {
      this->quien[e->i] = e->n;
      this->p -= e->n;
      e->n = 0;
      return false;
    } else if (this->p != 0) {
      this->quien[e->i] = this->p;
      e->n -= this->p;
      this->p = 0;
      return true;
    }

    return false;
  }
  bool operator<(Bus &other) { return this->p < other.p; }
  bool operator>(Bus &other) { return this->p > other.p; }
};

int main() {
  auto m = 4;
  auto P = 50;
  auto n = 6;

  std::vector<Equipo> equipos = {Equipo(0, 40), Equipo(1, 30), Equipo(2, 40),
                                 Equipo(3, 50), Equipo(4, 10), Equipo(5, 30)};

  // O(n*log(n))
  std::sort(equipos.begin(), equipos.end());

  std::vector<Bus> buses;
  for (auto i = 0; i < m; i++) {
    buses.push_back(Bus(i, P));
  }

  // O(m * n)
  for (auto i = 0; i < m; i++) {
    for (auto &bus : buses) {
      if (bus.subir_equipo(equipos, i)) {
        break;
      }
      std::sort(buses.begin(), buses.end(), std::greater<>());
    }
  }

  for (auto bus : buses) {
    std::cout << "El " << bus.i << " bus tiene ";

    for (auto [equipo, cantidad] : bus.quien) {
      std::cout << cantidad << " personas del " << equipo << " equipo ";
    }

    std::cout << std::endl;
  }
}
