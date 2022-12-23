#include <iostream>
#include <string>

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
  pilha pila1, pila2;
  char aux[255];
  int i = 0;
  
  cin >> aux;


  int size = sizeof(aux);
  while (size > i){
    if (aux[i] == '('){
      pila1.empilha(aux[i]);
    }
    if (aux[i] == ')'){
      pila2.empilha(aux[i]);
    }
    i++;
  }


  if (pila1.tamanho() == pila2.tamanho()){
    cout << "correto" << endl;
  }
  cout << aux << endl;
  cout << "( " << pila1.tamanho() << endl;
  cout << ") " << pila2.tamanho() << endl;

  return 0;
}

//func(x,(y+3)*4)