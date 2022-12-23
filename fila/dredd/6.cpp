#include <iostream>
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

int fila::espia (){
	int aux = mInicio -> mValor;
	return aux;
}

int main (){
  fila f;
  int numElementos, elemento, subFila;
  cin >> numElementos;

  for (int i = 0; i<numElementos; i++){
    cin >> elemento;
    f.enfileira(elemento);
  }

  cin >> subFila;

  bool achei = false;
  while(numElementos >= subFila){
    //int inicio = f.espia();
    int x=0;
    achei = false;
    for (int i = 0; i<subFila and achei == false; i++){
      int aux = f.desenfileira();
      if (aux < 0){
        cout << aux << " ";
        achei = true;
      }
      if (i > 0){
        f.enfileira(aux);
      }
      x++;
    }
    if (achei == false){
      cout << "inexistente ";
    }
    numElementos--;
    for (int i = 0; i <= numElementos - (x); i++){
      int aux = f.desenfileira();
      f.enfileira(aux);
    }
  }
  return 0;
}