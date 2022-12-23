#include <iostream>
using namespace std;

typedef int Dado;

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
    void inverte(int numero);
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

void pilha::inverte (int numero){
  int* vet = new int[numero];
  Dado x;
  int i = 0;
  while (not vazia()){
    vet[i] = desempilha();
    i++;
  }
  i = 0;
  while (i < numero){
    empilha(vet[i]);
    i++;
  }
  delete [] vet;
}

int main (){
  pilha p1;
  int numero;
  Dado entrada;
  cin >> numero;

  for (int i = 0; i < numero; i++){
    cin >> entrada;
    p1.empilha(entrada);
  }

  p1.inverte(numero);

  for (int i = 0; i < numero; i++){
    cout << p1.desempilha() << " ";
  }

  cout << endl;
	
  return 0;
}