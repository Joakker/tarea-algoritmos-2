from dataclasses import dataclass, field


@dataclass(frozen=False, order=True)
class Equipo:
    i: int = field(compare=False)
    """El número de equipo"""
    n: int = field(compare=True)
    """La cantidad de personas"""


@dataclass(frozen=False, order=True)
class Autobus:
    i: int = field(compare=False)
    """El indice del bus"""

    p: int = field(compare=True)
    """El número de asientos disponibles"""

    quien: dict[int, int] = field(compare=False, default_factory=dict)
    """Qué equipo usa cuántos asientos"""

    def subir_equipo(self, equipos: list[Equipo], i: int) -> bool:
        assert i < len(equipos)

        if equipos[i].n == 0:
            return True

        e = equipos[i]

        if e.n == 0:
            return True

        if e.n <= self.p:
            self.quien[e.i] = e.n
            self.p -= e.n
            e.n = 0
            return False
        elif self.p != 0:
            self.quien[e.i] = self.p
            e.n -= self.p
            self.p = 0
            return True

        return False


def algoritmo(
    *, equipos: list[int] = [40, 30, 40, 50, 10, 30], m: int = 4, n=6, P: int = 50
) -> None:
    """
    equipos:    lista de la cantidad de personas en el equipo
    m:          n° de autobuses
    n:          n° de equipos
    P:          n° de asientos en cada autobús
    """

    assert len(equipos) == n

    autobuses = [Autobus(i, P) for i in range(m)]
    equipos_ord = sorted((Equipo(i, n) for i, n in enumerate(equipos)), reverse=True)

    for i in range(len(equipos_ord)):
        for autobus in autobuses:
            if autobus.subir_equipo(equipos_ord, i):
                break
        autobuses.sort(reverse=True)

    for autobus in sorted(autobuses, key=lambda a: a.i):
        print(f"El {autobus.i+1}° autobús tiene", end=" ")
        print(
            *[
                f"{value} personas del equipo {key + 1}"
                for key, value in autobus.quien.items()
            ],
            sep=", ",
        )


if __name__ == "__main__":
    algoritmo()
