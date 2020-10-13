#ifndef ALGORITMO_H_
#define ALGORITMO_H_

/*
 *Librerias a ocupar
 */

#include <bits/stdc++.h>
#include <algorithm>
#include <set>
#include <iterator>
#include <utility>

using namespace std;

class Algoritmo {
public:
	set<pair<vector<int>, int > >* poblacion;
	int max_min;
	int poblacion_maxima;
	float pCruza;
	float pMutacion;
	int sum_fitness;
	int n;
	int iteraciones;
	int mod;

	//funciones a utilizar en el programa

	float random_01();
	int random_1N(int n);
	int calFitness(vector<int> datos, int max_min);
	set< pair<vector<int>, int > >::iterator ruleta();
	void mostrar_poblacion(bool tabla);
	int reducirPob(int fitnnes_min);
	pair<vector<int>, int > correcion(vector<int> in);
	void terminar(vector<int> out);

	//operadores geneticos
	vector<int> mutacion(vector<int> hijo);
	vector<int> cruza(vector<int> A, vector<int> B, int v);

	Algoritmo(int n, int ini, int max, float pCruza, float pMutacion, int iteraciones, int mod); // poblacion inicial
};

#endif /* ALGORITMO_H_ */
