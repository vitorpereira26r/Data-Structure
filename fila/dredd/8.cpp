#include <iostream>
using namespace std;

class noh {
	friend class fila;
	private:
		string mPlaca;
		noh* mProx;
	public:
		noh (string placa){
			mPlaca = placa;
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
		void enfileira(string placa);
		string desenfileira();
		int tamanho();
		void limpaFila();
		bool vazia();
		string espia ();
		void retiraCarro (string placaCarro);
    void imprimeFila ();
};

fila::fila () {
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

fila::~fila () {
	limpaFila();
}

void fila::enfileira (string placa){
	noh* novo = new noh (placa);
	if (mTamanho == 0){
		mInicio = novo;
	} else {
		mFim ->mProx = novo;
	}
	mFim = novo;
	mTamanho++;
}

string fila::desenfileira () {
	string placa = mInicio -> mPlaca;
	noh* temporario = mInicio;
	mInicio = mInicio ->mProx;
	delete temporario;
	mTamanho--;
	if (mTamanho == 0){
		mFim = NULL;
	}
	return placa;
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

string fila::espia (){
	string aux = mInicio -> mPlaca;
	return aux;
}

void fila::imprimeFila (){
  for (int i = 0; i < mTamanho; i++){
    string aux = desenfileira();
    cout << aux << endl;
    enfileira(aux);
  }
}

void fila::retiraCarro (string placaCarro){
  string aux;
  int controle = 0;
  bool retirado = false;

  do {
    controle++;
    if (espia() != placaCarro){
      aux = desenfileira();
      enfileira(aux);
    } else {
      desenfileira();
      retirado = true;
    }
  } while (retirado == false and controle < tamanho());

  if (retirado == false){
    cout << "NAO ENCONTRADO" << endl;
  }

  if (controle > 0 and retirado){
    cout << controle << endl;
    imprimeFila();
  }
}

int main () {
	fila f1;
	char comando;
  string placa, aux;

  do {
    cin >> comando;
    if (comando == 'E'){
      cin >> placa;
      f1.enfileira(placa);
    }
    else if (comando == 'D'){
      cin >> placa;
      if (f1.tamanho() <= 0){
        cout << "NAO ENCONTRADO" << endl;
      } else {
        f1.retiraCarro(placa);
      }
    }
  } while (comando != 'S');

	return 0;
}
