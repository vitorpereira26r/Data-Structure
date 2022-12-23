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
    int espiaFim ();
    void imprimeTudo();
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

int fila::espiaFim (){
  int aux = mFim -> mValor;
  return aux;
}

void fila::imprimeTudo (){
  for (int i = 0; i < mTamanho; i++){
    int aux = desenfileira();
    cout << aux << " ";
    enfileira(aux);
  }
  cout << endl;
}

//--------------------------

void mescla(fila f1, fila f2, fila result){
  //cout << "entrou na função" << endl;

  if (f1.espia() >= f2.espia())
  {
    result.enfileira(f2.desenfileira());
  }
  else 
  {
    result.enfileira(f1.desenfileira());
  }
  //cout << "passou 1" << endl;
  
  while (not f1.vazia() or not f2.vazia()){
    if (f1.vazia() and not f2.vazia()){
      result.enfileira(f2.desenfileira());
    } else if (not f1.vazia() and f2.vazia()){
      result.enfileira(f1.desenfileira());
    } else if (not f1.vazia() and not f2.vazia()){
      if (f1.espia() >= f2.espia()){
        result.enfileira(f2.desenfileira());
        result.enfileira(f1.desenfileira());
      } else {
        result.enfileira(f1.desenfileira());
        result.enfileira(f2.desenfileira());
      }
    }
  }
  //cout << "passou"<< endl;

  while (not result.vazia()){
    cout << result.desenfileira() << " ";
  }
  cout << endl;
}

//--------------------------

int main (){
  fila fA, fB, result;
  char comando, fila;
  int aux;

  do {
    cin >> comando;
    if (comando == 'i'){
      cin >> fila;
      if (fila == 'a'){
        cin >> aux;
        fA.enfileira(aux);
      } else if (fila == 'b'){
        cin >> aux;
        fB.enfileira(aux);
      }
    } else if (comando == 'e'){
      cin >> fila;
      if (fila == 'a'){
        fA.imprimeTudo();
      } else if (fila == 'b'){
        fB.imprimeTudo();
      }
    } else if (comando == 'm'){
      mescla(fA, fB, result);
    }
  } while (comando != 't');

  return 0;
}