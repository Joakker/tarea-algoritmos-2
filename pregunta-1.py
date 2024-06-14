from random import randrange


def algoritmo(
    *, P: list[int] = [8, 20, 10, 3, 50, 2, 5], U: list[int] = [10, 2, 50, 8, 20, 5, 3]
) -> list[int]:
    """
    Realiza el algoritmo

        P: lista de las capacidades de cada cpu
        U: lista de los requerimientos de cada usuario

    Retorna: Una lista de indices donde `A[i]` es el indice de la mejor
    cpu para los requerimientos de `U[i]`
    """

    assert len(P) == len(U), "La longitud de P y U debe ser la misma"

    A: list[int] = [-1 for _ in P]  # Acá pondremos los resultados
    N: int = len(P)

    asignados: set[int] = set()

    # TODO: Mejor Algoritmo
    # O(n^2)
    for i, u in enumerate(U):
        while True:
            index = randrange(0, N)
            if index not in asignados and P[index] == u:
                A[i] = index
                asignados.add(index)
                break

    return A


if __name__ == "__main__":
    print(algoritmo())
