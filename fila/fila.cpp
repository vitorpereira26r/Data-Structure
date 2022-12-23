#include <iostream>
using namespace std;

class noh {
	friend class fila;
	//friend class person;
	private:
		int dado;
		noh* mProx;
	public:
		noh (int valor){
			dado = valor;
			mProx = NULL;
		}
};

class fila {
	private:
		noh* mInicio;
		noh* mFim;
		int mTamanho;
	public:
		fila();
		~fila();
		void enfileira(int valor);
		int desenfileira();
		int tamanho();
		void limpaFila();
		bool vazia();
		int espia ();
};

fila::fila () {
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

fila::~fila () {
	limpaFila();
}

void fila::enfileira (int valor){
	noh* novo = new noh (valor);
	if (mTamanho == 0){
		mInicio = novo;
	} else {
		mFim ->mProx = novo;
	}
	mFim = novo;
	mTamanho++;
}

int fila::desenfileira () {
	int valor = mInicio ->dado;
	noh* temporario = mInicio;
	mInicio = mInicio ->mProx;
	delete temporario;
	mTamanho--;
	if (mTamanho == 0){
		mFim = NULL;
	}
	return valor;
}

int fila::tamanho() {
	return mTamanho;
}

void fila::limpaFila () {
	while (not vazia()){
		desenfileira();
	}
}

bool fila::vazia () {
	return (mTamanho == 0);
}

int fila::espia (){
	int aux = mInicio -> dado;
	return aux;
}

//------------------------

int main () {
	fila f1;
	
	return 0;
}
