#include <iostream>
using namespace std;

class noh1 {
	friend class filaPrioritaria;
	private:
		string mNome;
		noh1* mProx;
	public:
		noh1 (string nome){
			mNome = nome;
			mProx = NULL;
		}
};

class filaPrioritaria {
	private:
		noh1* mInicio;
		noh1* mFim;
		int mTamanho;
	public:
		filaPrioritaria();
		~filaPrioritaria();
		void enfileira(string nome);
		string desenfileira();
		int tamanho();
		void limpaFila();
		bool vazia();
		string espia ();
};

filaPrioritaria::filaPrioritaria () {
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

filaPrioritaria::~filaPrioritaria () {
	limpaFila();
}

void filaPrioritaria::enfileira (string nome){
	noh1* novo = new noh1 (nome);
	if (mTamanho == 0){
		mInicio = novo;
	} else {
		mFim ->mProx = novo;
	}
	mFim = novo;
	mTamanho++;
}

string filaPrioritaria::desenfileira () {
	string nome = mInicio -> mNome;
	noh1* temporario = mInicio;
	mInicio = mInicio ->mProx;
	delete temporario;
	mTamanho--;
	if (mTamanho == 0){
		mFim = NULL;
	}
	return nome;
}

int filaPrioritaria::tamanho() {
	return mTamanho;
}

void filaPrioritaria::limpaFila () {
	while (not vazia()){
		desenfileira();
	}
}

bool filaPrioritaria::vazia () {
	return (mTamanho == 0);
}

string filaPrioritaria::espia (){
	string aux = mInicio -> mNome;
	return aux;
}

//------------------------------------------

class noh2 {
	friend class filaNormal;
	private:
		string mNome;
		noh2* mProx;
	public:
		noh2 (string nome){
			mNome = nome;
			mProx = NULL;
		}
};

class filaNormal {
	private:
		noh2* mInicio;
		noh2* mFim;
		int mTamanho;
	public:
		filaNormal();
		~filaNormal();
		void enfileira(string nome);
		string desenfileira();
		int tamanho();
		void limpaFila();
		bool vazia();
		string espia ();
};

filaNormal::filaNormal () {
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

filaNormal::~filaNormal () {
	limpaFila();
}

void filaNormal::enfileira (string nome){
	noh2* novo = new noh2 (nome);
	if (mTamanho == 0){
		mInicio = novo;
	} else {
		mFim ->mProx = novo;
	}
	mFim = novo;
	mTamanho++;
}

string filaNormal::desenfileira () {
	string nome = mInicio -> mNome;
	noh2* temporario = mInicio;
	mInicio = mInicio ->mProx;
	delete temporario;
	mTamanho--;
	if (mTamanho == 0){
		mFim = NULL;
	}
	return nome;
}

int filaNormal::tamanho() {
	return mTamanho;
}

void filaNormal::limpaFila () {
	while (not vazia()){
		desenfileira();
	}
}

bool filaNormal::vazia () {
	return (mTamanho == 0);
}

string filaNormal::espia (){
	string aux = mInicio -> mNome;
	return aux;
}

//--------------------------------

int main () {
  filaNormal normal;
  filaPrioritaria prioritaria; 
  string comando, nome;
  int i = 0;

  do {
    cin >> comando;
    if (comando == "normal"){
      cin >> nome;
      normal.enfileira(nome);
    } else if (comando == "prioridade"){
      cin >> nome;
      prioritaria.enfileira(nome);
    } else if (comando == "atender"){
      if (not normal.vazia() or not prioritaria.vazia()){
				if ((not prioritaria.vazia() and i < 3) or ((not prioritaria.vazia()) and (normal.vazia()))){
					cout << prioritaria.desenfileira() << endl;
					i++;
				} else {
					cout << normal.desenfileira() << endl;
					i=0;
				} 
			} else {
				cout << "AGUARDE" << endl;
			}
    }
  } while (comando != "fim");


  //cout << "here2 ";
  return 0;
}