//============================================================================
// Integrante  : Francisca Alarcon
// Descripcion : Ubicar n-reinas en un tablero de ajedrez de largo n sin que estas colicionen entre si.
//============================================================================

#include <iostream>
#include "Algoritmo.h"

using namespace std;

int main(int argc, char *argv[]) {
	// cantidad de reinas
	int n = atoi(argv[1]);

	// tamaño poblacion inicial
	int ini = atoi(argv[2]);

	// semilla a utilizar
	int seed = atoi(argv[3]);

	// max individuos por generacion
	int max = atoi(argv[4]);

	// provavilidad de cruza
	float pCruza = ((float)atoi(argv[5]) / (float)100);

	// probabilidad de mutacion
	float pMutacion = ((float)atoi(argv[6]) / (float)100);

	//numero de iteraciones max
	int iteraciones = atoi(argv[7]);

	//numero de iteraciones para incrementar el fitness minimo (nueva pob)
	int mod = atoi(argv[8]);

	// inicializacion de semilla
	srand(seed);
	
	cout << "Ejecutando Algoritmo genetico..." << endl;

	
	cout << "Datos y resultados:" << endl;
	cout << "- Fitness maximo (resultado optimo): " << ((n * n) - 1) / 2 << endl;
	cout << "- Tamaño de la cuadricula: " << n << endl;
	cout << "- Poblacion inicial: " << ini << endl;
	cout << "- Poblacion maxima por generacion: " << max << endl;
	cout << "- Probabilidad de cruza: " << pCruza; printf("%c\n",37);
	cout << "- Probabilidad de mutacion: " << pMutacion; printf("%c\n",37);
	Algoritmo *reinas = new Algoritmo(n, ini, max, pCruza, pMutacion, iteraciones, mod);
	

	return 0;
}
