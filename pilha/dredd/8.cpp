#include <iostream>
using namespace std;

typedef int Dado;

class noh {
	friend class Pilha;
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

class Pilha {
	private:
		noh* mTopo;
		int mTamanho;
		//Dado menor;
	public:
		Pilha();
		~Pilha();
		unsigned tamanho();
		void empilha (Dado valor);
		void limpaPilha();
		Dado desempilha();
		bool vazia();
    Dado menorValor();
};

Pilha::Pilha(){
	mTopo = NULL;
	mTamanho = 0;
}

Pilha::~Pilha(){
	limpaPilha();
}

void Pilha::limpaPilha(){
	while (not vazia()){
		desempilha();
	}
}

unsigned Pilha::tamanho(){
	return mTamanho;
}

bool Pilha::vazia (){
	return (mTamanho == 0);
}

void Pilha::empilha(Dado valor){
	noh* novo = new noh (valor);
	novo ->mProximo = mTopo;
	mTopo = novo;
	mTamanho++;
}

Dado Pilha::desempilha (){
  if (vazia()){
    cout << "VAZIA" << endl;
  } else {
	  Dado valor = mTopo -> mValor;
	  noh* temp = mTopo;
	  mTopo = mTopo -> mProximo;
	  delete temp;
	  mTamanho--;
	  return valor;
  }
}

Dado Pilha::menorValor (){
  noh* aux = mTopo;
  Dado menor = mTopo -> mValor;
  do {
    if (aux -> mValor < menor){
      menor = aux-> mValor;
    }
    aux = aux -> mProximo;
  } while (aux != NULL);
  delete aux;
  return menor;
}

int main (){
  Pilha pilha;
  char opcao;
  int numero;

  do {
    cin >> opcao;
    switch (opcao){
      case 'e':
        cin >> numero;
        pilha.empilha(numero);
        break;
      case 'd':
        if (pilha.vazia()){
          cout << "VAZIA" << endl;
        } else {
          cout << pilha.desempilha() << endl;
        }
        break;
      case 'm':
        if(pilha.vazia()){
          cout << "VAZIA" << endl;
        } else {
          cout << pilha.menorValor() << endl;
        }
        break;
      case 's':
        while (not pilha.vazia()){
          cout << pilha.desempilha() << " ";
        }
        cout << endl;
        break;
    }
  } while (opcao != 's');


  return 0;
}