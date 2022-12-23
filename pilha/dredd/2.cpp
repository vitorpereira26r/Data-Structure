#include <iostream>

using namespace std;

class noh2 {
	friend class pilha2;
	private:
		int mValor;
		noh2* mProximo;
	public:
		noh2 (int valor){
			mValor = valor;
			mProximo = NULL;
		}
};

class pilha2 {
	private:
		noh2* mTopo;
		int tamanho;
	public:
		pilha2();
		void empilha(int valor);
		int desempilha();
		int espia();
		bool vazia ();
		int tamanhoPilha ();
};

pilha2::pilha2 () {
	mTopo = NULL;
	tamanho = 0;
}

int pilha2::tamanhoPilha () {
	return tamanho;
}

void pilha2::empilha (int valor) {
	noh2* novo = new noh2 (valor);
	novo ->mProximo = mTopo;
	mTopo = novo;
	tamanho++;
	//cout <<"h";
}

int pilha2::desempilha () {
	int valor = mTopo -> mValor;
	noh2* temp = mTopo;
	mTopo = mTopo -> mProximo;
	delete temp;
	tamanho--;
	//cout << " hello";
	return valor;
}

int pilha2::espia () {
	return mTopo -> mValor;
}

bool pilha2::vazia () {
	return (tamanho == 0);
}


class noh {
	friend class pilha1;
	private:
		int mValor;
		noh* mProximo;
	public:
		noh (int valor){
			mValor = valor;
			mProximo = NULL;
		}
};

class pilha1{
	private:
		noh* mTopo;
		int tamanho;
	public:
		pilha1();
		void empilha(int valor);
		int desempilha();
		bool vazia ();
		void ordena ();
};

pilha1::pilha1 () {
	mTopo = NULL;
	tamanho = 0;
}

void pilha1::empilha (int valor) {
	noh* novo = new noh (valor);
	novo ->mProximo = mTopo;
	mTopo = novo;
	tamanho++;
}

int pilha1::desempilha () {
	int valor = mTopo -> mValor;
	noh* temp = mTopo;
	mTopo = mTopo -> mProximo;
	delete temp;
	tamanho--;
	return valor;
}

bool pilha1::vazia (){
	return (tamanho == 0);
}

void pilha1::ordena () {
	pilha2 auxiliar;
	int aux;
	
	while (not vazia()) {
		aux = desempilha();
		while (not auxiliar.vazia() and auxiliar.espia() > aux) {
			empilha(auxiliar.desempilha());
		}
		auxiliar.empilha(aux);
	}
	int tamAux = auxiliar.tamanhoPilha();
	for (int i = 0; i < tamAux; i++){
		empilha(auxiliar.desempilha());
	}
}


int main () {
	pilha1 p1;
	pilha2 p2;
	int tam, num;
	cin >> tam;
	
	for (int i = 0; i < tam; i++){
		cin >> num;
		p1.empilha(num);
	}
	
	p1.ordena();
	for (int i = 0; i < tam; i++){
		cout << p1.desempilha() << " ";
	}
	
	
	return 0;
}
