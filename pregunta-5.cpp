/*Faltan algunas pruebas, pero por ahora funciona*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Estructura para representar una caja con sus dimensiones y peso
struct box{
    int x, y, z, w;
};

//Comparador para ordenar las cajas por sus dimensiones
bool compare(box a, box b){
    if(a.x != b.x) return a.x < b.x;
    if(a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

//Verifica todas las combinaciones posibles de igualdades y desigualdades entre las dimensiones
bool puedeGuardar(const box &b1, const box &b2){
    int menorIgual = (b1.x <= b2.x) + (b1.y <= b2.y) + (b1.z <= b2.z);
    int menorEstricto = (b1.x < b2.x) + (b1.y < b2.y) + (b1.z < b2.z);
    return menorIgual == 3 && menorEstricto > 0 && b1.w < b2.w;
}

//"Convierte" el vector ingresado en caja
vector<box> processBoxes(const vector<vector<int>>& input){
    int n = input.size();
    vector<box> boxes(n);
    for(int i = 0; i < n; ++i){
        vector<int> dims = {input[i][0], input[i][1], input[i][2]};
        sort(dims.begin(), dims.end());
        boxes[i] = {dims[0], dims[1], dims[2], input[i][3]};
    }
    return boxes;
}

//Encontrar la mayor cantidad de cajas que se pueden guardar
int maxBoxes(const vector<vector<int>>& input){
    vector<box> boxes = processBoxes(input);
    int n = boxes.size();
    vector<int> maxCount(n,1);
    sort(boxes.begin(), boxes.end(), compare);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < i; ++j){
            if(puedeGuardar(boxes[j], boxes[i])){
                maxCount[i] = max(maxCount[i], maxCount[j] + 1);
            }
        }
    }
    return *max_element(maxCount.begin(), maxCount.end());
}

int main(){
    vector<vector<int>> ejemplos[] = {
        {{41, 50, 30, 3}, {30, 25, 40, 1}, {40, 49, 30, 2}},
        {{40, 50, 30, 2}, {21, 22, 23, 1}, {30, 51, 40, 1}, {41, 49, 30, 3}}
    };

    for(int i = 0; i < 2; ++i){
        int resultado = maxBoxes(ejemplos[i]);
        cout << "Ejemplo " << (i + 1) << ": " << resultado << " cajas" << endl;
    }

    return 0;
}