#include <iostream>
using namespace std;

class noh1 {
  friend class fila1;
  private:
    int mValor;
    noh1* mProx;
  public:
    noh1 (int valor){
      mValor = valor;
      mProx = NULL;
    }
};

class fila1 {
  private:
    noh1* mInicio1;
    noh1* mFim1;
    int mTamanho1;
  public:
    fila1 ();
    ~fila1();
    void enfileira (int valor);
    int desenfileira ();
    bool vazia ();
    int espia ();
    void limpaPilha ();
};

fila1::fila1 () {
  mInicio1 = NULL;
  mFim1 = NULL;
  mTamanho1 = 0;
}

fila1::~fila1(){
  limpaPilha();
}

void fila1::enfileira (int valor) {
  noh1* novo = new noh1 (valor);
	if (mTamanho1 == 0){
		mInicio1 = novo;
	} else {
		mFim1 ->mProx = novo;
	}
	mFim1 = novo;
	mTamanho1++;
}

int fila1::desenfileira () {
	int valor = mInicio1 -> mValor;
	noh1* temporario = mInicio1;
	mInicio1 = mInicio1 ->mProx;
	delete temporario;
	mTamanho1--;
	if (mTamanho1 == 0){
		mFim1 = NULL;
	}
	return valor;
}

bool fila1::vazia (){
  return (mTamanho1 == 0);
}

int fila1::espia (){
  int aux = mInicio1 -> mValor;
  return aux;
}

void fila1::limpaPilha (){
  while(not vazia()){
    desenfileira();
  }
}

//-----------------------------------------------
class noh2 {
  friend class fila2;
  private:
    int mValor;
    noh2* mProx;
  public:
    noh2 (int valor){
      mValor = valor;
      mProx = NULL;
    }
};

class fila2 {
  private:
    noh2* mInicio2;
    noh2* mFim2;
    int mTamanho2;
  public:
    fila2 ();
    ~fila2();
    void enfileira (int valor);
    int desenfileira ();
    bool vazia ();
    int espia ();
    void limpaPilha ();
};

fila2::fila2 () {
  mInicio2 = NULL;
  mFim2 = NULL;
  mTamanho2 = 0;
}

fila2::~fila2(){
  limpaPilha();
}

void fila2::enfileira (int valor) {
  noh2* novo = new noh2 (valor);
	if (mTamanho2 == 0){
		mInicio2 = novo;
	} else {
		mFim2 ->mProx = novo;
	}
	mFim2 = novo;
	mTamanho2++;
}

int fila2::desenfileira () {
	int valor = mInicio2 -> mValor;
	noh2* temporario = mInicio2;
	mInicio2 = mInicio2 ->mProx;
	delete temporario;
	mTamanho2--;
	if (mTamanho2 == 0){
		mFim2 = NULL;
	}
	return valor;
}

bool fila2::vazia (){
  return (mTamanho2 == 0);
}

int fila2::espia (){
  int aux = mInicio2 -> mValor;
  return aux;
}

void fila2::limpaPilha (){
  while(not vazia()){
    desenfileira();
  }
}

//--------------------------------------

int main () {
  fila1 f1;
  fila2 f2;
  int numF1, numF2;
  int aux1, aux2, aux3, aux4;
  bool igual = false;

  cin >> numF1;
  for (int i = 0; i < numF1; i++){
    cin >> aux1;
    f1.enfileira(aux1);
  }

  cin >> numF2;
  for (int i = 0; i < numF2; i++){
    cin >> aux2;
    f2.enfileira(aux2);
  }

  for (int i = 0; i < numF1; i++){
    aux3 = f1.espia();
    igual = false;
    for (int i = 0; i < numF2 and not igual; i++){
      aux4 = f2.espia();
      if (aux3 != aux4){
        aux4 = f2.desenfileira();
        f2.enfileira(aux4);
      } else {
        f1.desenfileira();
        igual = true;
      }
    }
    if (igual == false){
      aux3 = f1.desenfileira();
      f1.enfileira(aux3);
    }
  }

  while (not f1.vazia()){
    cout << f1.desenfileira() << " ";
  }
  
  return 0;
}