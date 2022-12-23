#include <iostream>

using namespace std;

class pilhav{
	private:
		int capacidade;
		int dados[20];
		int tamanho;
		int posTopo;
	public:
		pilhav();
		~pilhav();
		void empilha (int valor);
		int desempilha();
};

pilhav::pilhav (){
	tamanho = 0;
	posTopo = -1;
}

pilhav::~pilhav(){
	desempilha();
}

void pilhav::empilha (int valor) {
	posTopo++;
	dados[posTopo] = valor;
	tamanho++;
} 

int pilhav::desempilha(){
	int aux = dados[posTopo];
	posTopo--;
	tamanho--;
	return aux;
}

int main () {
	pilhav p;
	
	int num = 10;
	
	p.empilha(num);
	
	cout << p.desempilha() << endl;
	
	return 0;
}
