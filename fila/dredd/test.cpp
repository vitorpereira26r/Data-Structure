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
//--------------------------------------

int main()
{
  fila f1, f2, result;
  int quantidade;

  cin >> quantidade;
  for (int i = 0; i < quantidade; i++)
  {
    int aux;
    cin >> aux;
    f1.enfileira(aux);
  }

  cin >> quantidade;
  for (int i = 0; i < quantidade; i++)
  {
    int aux;
    cin >> aux;
    f2.enfileira(aux);
  }

  if (result.vazia())
  {
    if (f1.espia() >= f2.espia())
    {
      result.enfileira(f2.desenfileira());
    }
    else 
    {
      result.enfileira(f1.desenfileira());
    }
  }
  
  while (not f1.vazia() or not f2.vazia())
  {
    if (not f1.vazia() and f2.vazia())
    {
      if (f1.espia() != result.espiaFim())
      {
        result.enfileira(f1.desenfileira());
      }
      else
      {
        f1.desenfileira();
      }
    }
    else if (f1.vazia() and not f2.vazia())
    {
      if (f2.espia() != result.espiaFim())
      {
        result.enfileira(f2.desenfileira());
      }
      else
      {
        f2.desenfileira();
      }
    }
    else if (not f2.vazia() and not f1.vazia())
    {
      if (f1.espia() >= f2.espia())
      {
        if (f2.espia() != result.espiaFim())
        {
          result.enfileira(f2.desenfileira());
        }
        else
        {
          f2.desenfileira();
        }
      }
      else 
      {
        if (f1.espia() != result.espiaFim())
        {
          result.enfileira(f1.desenfileira());
        }
        else
        {
          f1.desenfileira();
        }
      }
    }
  }
  


  while (not result.vazia()){
    cout << result.desenfileira() << " ";
  }
  //cout << "here";
  return 0;
}