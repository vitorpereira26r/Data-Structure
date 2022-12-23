#include <iostream>

using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo

// pilha implementada em arranjo 
class pilhav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap = 20);
        ~pilhav();
        void empilha(Dado valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
        void info();  // imprime informações da pilha (tamanho e  posição do topo)
};

pilhav::pilhav (int cap){
	dados = new Dado[cap];
	tamanho = 0;
	posTopo = -1;
}

pilhav::~pilhav () {
	while (tamanho >=0){
		desempilha();
	}
}

void pilhav::empilha (Dado valor) {
	posTopo++;
	dados[posTopo] = valor;
	tamanho++;
}

Dado pilhav::desempilha () {
	Dado aux = dados[posTopo];
	posTopo--;
	tamanho--;
	return aux;
}

Dado pilhav::espia () {
	return dados[posTopo];
}

void pilhav::depura () {
	for (int i = 0; i < posTopo+1; i++){
		cout << dados[i] << " ";
	}
	cout << endl;
}

void pilhav::info(){
	cout << tamanho << " " << posTopo;
}

int main () {
	pilhav p1;
	int num;
	for (int i = 0; i < 5; i++){
		cin >> num;
		p1.empilha(num);
	}
	
	for (int i = 0; i < 3; i++){
		cout << p1.desempilha() << " ";
	}
	cout << endl;
	
	for (int i = 0; i < 4; i++){
		cin >> num;
		p1.empilha(num);
	}
	
	for (int i = 0; i < 3; i++){
		cout << p1.desempilha() << " ";
	}
	cout << endl;
	
	cout << p1.espia() << endl;
	p1.depura();
	p1.info();

	
return 0;
}
