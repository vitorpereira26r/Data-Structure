#include <iostream>
#include <cmath>
using namespace std;

class noh {
	friend class fila;
	private:
		int mValor;
		noh* mProx;
	public:
		noh (int valor){
			mValor = valor;
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
	int valor = mInicio -> mValor;
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

int converteBinario (int num) {
  fila f1;
  int resto, i =0;
  int n=0;
  while (num > 1){
    resto = (num % 2)*round(pow(10,i));
    num = num / 2;
    n += resto;
    i++;
  }
  if (num == 1){
    resto = round(pow(10, i));
    //cout << resto << " "<< i << " ";
    n += resto;
  }
  return n;
}

int main (){
  fila f1;
  int n, bin;
  cin >> n;

  for (int i = 1; i <= n; i++){
    bin = converteBinario(i);
    f1.enfileira(bin);
  }

  while(not f1.vazia()){
    cout << f1.desenfileira() << " ";
    //cout << "chegou aqui";
  }

  
  return 0;
}