#include <iostream>
using namespace std;

class fila {
  private:
    int capacidade;
    int *dados;
    int tamanho;
    int mInicio;
    int mFim;
  public:
    fila(int cap);
    ~fila();
    void insere(int valor);
    int remove ();
    void limpaPilha();
    void informacoes();
};

fila::fila (int cap){
  dados = new int[cap];
  capacidade = cap;
  tamanho = 0;
  mInicio = -1;
  mFim = -1;
}

fila::~fila(){
  limpaPilha();
}

void fila::insere (int valor){
  if (tamanho == capacidade){
    cout << "fila cheia" << endl;
  } 
  if (mInicio == -1){
    mInicio++;
  }
  mFim++;
  dados[mFim] = valor;
  tamanho++;
}

int fila::remove (){
  int aux = dados[mInicio];
  if (mInicio == mFim){
    mFim = -1;
    mInicio = -1;
  } else {
    mInicio = (mInicio+1) % capacidade;
  }
  tamanho--;
  return aux;
}

void fila::limpaPilha (){
  while (tamanho >= 0){
    remove();
  }
}

void fila::informacoes (){
  cout << "tamanho=" << tamanho << " capacidade=" << capacidade << " inicio=" << mInicio << " fim=" << mFim << endl;
  for (int i = mInicio; i <= mFim; i++){
    cout << dados[i] << " ";
  }
  cout << endl;
}

//---------------------------

int main (){
  int capacidade, valor;
  char comando;
  cin >> capacidade;
  fila f(capacidade);

  do {
    cin >> comando;
    switch (comando){
      case 'e':
        cin >> valor;
        f.insere(valor);
        break;
      case 'd':
        cout << f.remove() << endl;
        break;
      case 'i':
        f.informacoes();
        break;
    }
  } while (comando != 't');

  return 0;
}