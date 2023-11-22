#include <iostream>
using namespace std;

typedef char Dado;

class noh {
	friend class pilha;
	private:
		Dado mValor;
		noh* mProximo;
	public:
		noh (Dado valor);
};

noh::noh (Dado valor){
	mValor = valor;
	mProximo = NULL;
}

class pilha {
	private:
		noh* mTopo;
		int mTamanho;
		
	public:
		pilha();
		~pilha();
		unsigned tamanho();
		void empilha (Dado valor);
		void limpaPilha();
		Dado desempilha();
		bool vazia();
};

pilha::pilha(){
	mTopo = NULL;
	mTamanho = 0;
}

pilha::~pilha(){
	limpaPilha();
}

void pilha::limpaPilha(){
	while (not vazia()){
		desempilha();
	}
}

unsigned pilha::tamanho(){
	return mTamanho;
}

bool pilha::vazia (){
	return (mTamanho == 0);
}

void pilha::empilha(Dado valor){
	noh* novo = new noh (valor);
	novo ->mProximo = mTopo;
	mTopo = novo;
	mTamanho++;
}

Dado pilha::desempilha (){
	Dado valor = mTopo -> mValor;
	noh* temp = mTopo;
	mTopo = mTopo -> mProximo;
	delete temp;
	mTamanho--;
	return valor;
}

int main (){
	pilha p1;
	Dado dado;
	//cin >> dadol;
	

	do {
		cin >> dado;
		if(dado != 'g'){
			p1.empilha(dado);
		}
	}
	while(dado != 'g');
	
	cout << "tamanho: " << p1.tamanho() << endl;
	
	cout << "elementos: ";
	
	while (not p1.vazia()) {
		cout << p1.desempilha() << " ";
	}
	cout << endl;
	
return 0;
}
