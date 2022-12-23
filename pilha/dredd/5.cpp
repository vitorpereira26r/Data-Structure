#include <iostream>

using namespace std;
//L = {A*i B C*2i | i > 0}

class nohAs {
	friend class pilhaAs;
	private:
		char mA;
		nohAs* mProx;
	public:
		nohAs (char a){
			mA = a;
			mProx = NULL;
		}
};

class pilhaAs {
	private:
		nohAs* mTopo;
		int tamanho;
	public:
		pilhaAs();
		~pilhaAs();
		void empilha(char a);
		char desempilha();
		int tamanhoA();
};

pilhaAs::pilhaAs () {
	mTopo = NULL;
	tamanho = 0;
}

pilhaAs::~pilhaAs () {
	while (tamanhoA() > 0){
		desempilha();
	}
}

void pilhaAs::empilha (char a){
	nohAs* novo = new nohAs(a);
	novo -> mProx = mTopo;
	mTopo = novo;
	tamanho++;
}

char pilhaAs::desempilha () {
	char valor = mTopo -> mA;
	nohAs* temp = mTopo;
	mTopo = mTopo -> mProx;
	delete temp;
	tamanho--;
	return valor;
}

int pilhaAs::tamanhoA () {
	return tamanho;
}

//----------------------------------------------------------------------------

class nohCs {
	friend class pilhaCs;
	private:
		char mC;
		nohCs* mProx;
	public:
		nohCs (char c){
			mC = c;
			mProx = NULL;
		}
};

class pilhaCs {
	private:
		nohCs* mTopo;
		int tamanho;
	public:
		pilhaCs();
		~pilhaCs();
		void empilha(char c);
		char desempilha();
		int tamanhoC();
};

pilhaCs::pilhaCs(){
	mTopo = NULL;
	tamanho = 0;
}

pilhaCs::~pilhaCs (){
	while (tamanhoC() > 0){
		desempilha();
	}
}

void pilhaCs::empilha (char c){
	nohCs* novo = new nohCs (c);
	novo -> mProx = mTopo;
	mTopo = novo;
	tamanho++;
}

char pilhaCs::desempilha(){
	char valor = mTopo -> mC;
	nohCs* temp = mTopo;
	mTopo = mTopo -> mProx;
	delete temp;
	tamanho--;
	return valor;
}

int pilhaCs::tamanhoC () {
	return tamanho;
}

int main () {
	pilhaCs pC;
	pilhaAs pA;
	char letra;
	
	do {
		cin >> letra;
		if (letra != 'B'){
			if (letra == 'A'){
				pA.empilha(letra);
			}
			else if (letra == 'C'){
				pC.empilha(letra);
			}
		}
	}while (letra != 'X');
	
	while (pA.tamanhoA() > 0 and pC.tamanhoC() > 0){
		pA.desempilha();
		for (int i = 0; i < 2; i++){
			pC.desempilha();
		}
	}
	
	if (pA.tamanhoA() > 0 or pC.tamanhoC() > 0){
		cout << "nao" << " ";
	} else {
		cout << "sim" << " ";
	}
	
	cout << pA.tamanhoA() << " " << pC.tamanhoC() << endl;
		
	
	
	return 0;
}

