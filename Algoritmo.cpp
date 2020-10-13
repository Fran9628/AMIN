#include "Algoritmo.h"

/**Constructor algoritmo genético
 * n : tamaño del tablero de ajedréz
 * ini: tamaño inicial de la población
 * max: número número máximo genes en la poblacion
 * pCruza: probabilidad de cruza entre genes
 * pMutacion: probabilidad de mutacion de un nuevo hijo
 * ini no puede ser mas grande que n!
 * poblacion_maxima no puede ser mas grande que n!
 */
Algoritmo::Algoritmo(int n, int ini, int max, float pCruza, float pMutacion, int iteraciones, int mod) {
	this->poblacion_maxima = max;
	this->pCruza = pCruza;
	this->pMutacion = pMutacion;
	this->max_min = ((n * n) - 1) / 2;
	this->poblacion = new set<pair<vector<int>, int > >();
	this->sum_fitness = 0;
	this->n = n;
	this->iteraciones = iteraciones;
	this->mod = mod;

	vector<int> dato(n);
	for (int i = 0; i < n; ++i) {
		dato[i] = i;
	}
	int old;
	//poblacion inicial
	int aux;
	while (poblacion->size() < ini) {
		old = poblacion->size();
		random_shuffle(dato.begin(), dato.end());
		//calculo de fitness
		aux = this->calFitness(dato, this->max_min);
		poblacion->insert(make_pair(dato,aux));
		if (old != poblacion->size()) {
			if (this->max_min != aux)
				this->sum_fitness += aux;
			else
				this->terminar(dato); 
				//condicion de termino en caso de encontrar el elemento al momento de generar la poblacion
		}
	}

	int itt=0;
	int fitnnes_min = this->max_min/2;
	do{
		itt++;
		if(itt % this->mod == 0) {
			if(fitnnes_min+1 < max_min)
				fitnnes_min++;
		}
		cout << "iteracion: "<< itt << " ";
		fitnnes_min=this->reducirPob(fitnnes_min);
	}while(this->iteraciones >= itt);

	cout << "No se encontro solucion"<< endl;
	
}

int Algoritmo::reducirPob(int fitnnes_min){
	set<pair<vector<int>, int > >* new_poblacion = new set<pair<vector<int>, int > >();
	set< pair<vector<int>, int > >::iterator actual = this->poblacion->begin();
	//inserta en la nueva poblacion los mejores, sin eliminar aun los mas malos
	this->sum_fitness = 0;
	while(actual != this->poblacion->end()){
		if(actual->second >= fitnnes_min){
			new_poblacion->insert(*actual);
			this->sum_fitness+=actual->second;
		}
		actual++;
	}

	while(new_poblacion->size() < this->poblacion_maxima){
		vector <int> A;
		vector <int> B;
		set<pair<vector<int>, int > >::iterator result_ruleta_A;
		set<pair<vector<int>, int > >::iterator result_ruleta_B;

		result_ruleta_A = this->ruleta();
		for(int i =0; i< result_ruleta_A->first.size();i++)
			A.push_back(result_ruleta_A->first.at(i));

		result_ruleta_B = this->ruleta();
		for(int i =0; i< result_ruleta_B->first.size();i++)
			B.push_back(result_ruleta_B->first.at(i));
		//intento de cruza
		pair<vector<int>, int > aux;
		int k;
		if(this->random_01() <= this->pCruza){
			k = new_poblacion->size();
			//hijo 1
			if(this->random_01() <= this->pMutacion){
				//mutacion 
				aux = this->correcion( this->mutacion( this->cruza(A,B,1) ) );
				new_poblacion->insert( aux );
			}else{
				//no mutacion
				aux = this->correcion( this->cruza(A,B,1) ); 
				new_poblacion->insert( aux );
			}
			if(k != new_poblacion->size())
				this->sum_fitness+=aux.second;

			k = new_poblacion->size();
			//hijo 2
			if(this->random_01() <= this->pMutacion){
				//mutacion 
				aux = this->correcion(this->mutacion(this->cruza(A,B,2)));
				new_poblacion->insert(aux);

			}else{
				//no mutacion 
				aux = this->correcion(this->cruza(A,B,2));
				new_poblacion->insert(aux);
			}
			if(k != new_poblacion->size())
				this->sum_fitness+=aux.second;
		}

	}
	delete this->poblacion;
	this->poblacion = new_poblacion;


	int best = 0;
	actual = this->poblacion->begin();
	while(actual != this->poblacion->end()){
		if(actual->second > best){
			best = actual->second;
		}
		actual++;
	}
	cout << "- Mejor solucion actual ("<<best<<"/"<<this->max_min<<") - fitnnes_min: "<<fitnnes_min<<endl; 
	return best;
}

pair<vector<int>, int > Algoritmo::correcion(vector<int> in){
	set <int> faltantes;
	set <int> iguales;
	for (int i = 0; i < in.size(); ++i){
		faltantes.insert(i);
	}
	int k = faltantes.size();
	for(int i : in){
		faltantes.erase(i);
		if(k == faltantes.size())
			iguales.insert(i);
		k = faltantes.size();
	}
	if(k != 0){
		vector <int> faltantes_v;
		for(int i : faltantes){
			faltantes_v.push_back(i);
		}
		random_shuffle(faltantes_v.begin(),faltantes_v.end());
		set <int>::iterator i = iguales.begin();
		for (int j = 0; j < in.size(); ++j){
			if(in[j] == *i){
				in[j] = faltantes_v.back();
				faltantes_v.pop_back();
				i++;
				if(i != iguales.end())
					j = 0;
			}
			if(faltantes_v.size()==0)
				break;
		}
	}

	int f = this->calFitness(in,this->max_min);
	if (this->max_min != f)
		return make_pair(in,f);
	else
		this->terminar(in); 
		//condicion de termino en caso de encontrar el elemento al momento de generar un hijo
}

void Algoritmo::terminar(vector<int> out) {
	cout << "- Solucion encontrada!!" << endl<<endl;
	for (int i = 0; i < this->n; i++) {
		for (int j = 0; j < this->n; j++) {
			if (i == out[j])
				cout << "* ";
			else
				cout << "- ";
		}
		cout << endl;
	}
	exit(0);
}

float Algoritmo::random_01() {
	double num = rand() % 99;
	num /= 100;
	return num;
}

int Algoritmo::random_1N(int n) {
	int num = 1 + (rand() % n);
	return num;
}

int Algoritmo::calFitness(vector<int> datos, int max_min) {
	int choques = max_min;
	for (int i = 0; i < datos.size(); ++i) {
		for (int j = i + 1; j < datos.size(); ++j) {
			if (abs(i - j) == abs(datos.at(i) - datos.at(j)))
				choques--;
		}
	}
	return choques;
}

vector<int> Algoritmo::mutacion(vector<int> hijo) {
	int x1, x2;
	vector<int> mutado(hijo);
	x1 = rand() % mutado.size();
	do {
		x2 = rand() % mutado.size();
	} while (x1 == x2);
	int aux = mutado[x1];
	mutado[x1] = mutado[x2];
	mutado[x2] = aux;
	return mutado;

}

set< pair<vector<int>, int > >::iterator Algoritmo::ruleta() {
	int tam = this->poblacion->size();
	vector<float> frec_acom(tam);
	int sum = this->sum_fitness;

	set< pair<vector<int>, int > >::iterator it;
	int i;

	it = this->poblacion->begin();
	frec_acom[0] = (float) it->second / (float) sum;
	i = 0;
	for (++it; it != this->poblacion->end(); ++it) {
		frec_acom[i] = frec_acom[i - 1] + ((float) it->second / (float) sum);
		i++;
	}

	float valor_aleatorio = random_01();
	it = this->poblacion->begin();
	for (i = tam - 2; i >= 0; i--) {
		if (valor_aleatorio > frec_acom[i]) {
			advance(it, i + 1);
			return it;
		}
	}
	return this->poblacion->begin();
}

void Algoritmo::mostrar_poblacion(bool tabla) {
	int pos = 0;
	int best_pos = 0;
	int best_fitness = 0;
	for (set< pair<vector<int>, int > >::iterator i = this->poblacion->begin();
			i != this->poblacion->end(); ++i) {
		int aux = i->second;
		if (best_fitness < aux) {
			best_pos = pos;
			best_fitness = aux;
		}
		if (tabla) {
			printf("[%5d,%5d]", pos, aux);
			if ((pos) % 10 == 0)
				cout << endl;
			else
				cout << "-";
		}
		pos++;
	}

	cout << endl << "El mejor postulante es el numero: " << best_pos
			<< " con un fitness de: " << best_fitness << "/" << this->max_min
			<< endl;
}

vector <int> Algoritmo::cruza(vector<int> A, vector<int> B, int v){
	if(v == 1){
		vector <int> hijo(A);
		for (int i = (hijo.size()/2); i < hijo.size(); ++i)
		{
			hijo[i]=B[i];
		}
		return hijo;
	}else{
		vector <int> hijo(B);
		for (int i = (hijo.size()/2); i < hijo.size(); ++i)
		{
			hijo[i]=A[i];
		}
		return hijo;
	}
}

