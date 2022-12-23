#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef int dado;
const int INVALIDO = -1;

class torneio {
  private:
    dado* heap;
    int capacidade;
    int tamanho;
    int inicioDados;
    int contador;
    inline int pai(int i);
    inline int esquerdo (int i);
    inline int direito (int i);
    void arruma();
    void copiaMaior(int i);
    void copiaMenor(int i);
    void copiaSubindo(int i);
  public:
    torneio(dado vet[], int tam);
    ~torneio();
    void insere (dado d);
    void imprime ();
    dado retiraRaiz ();
};

torneio::torneio(dado vet[], int tam){
  //contador = 1;
  capacidade = 1;

  while (capacidade < tam){
    capacidade *= 2;
  }

  capacidade = capacidade - 1 + tam;
  contador = capacidade;

  heap = new dado[capacidade];
  inicioDados = capacidade - tam;
  for (int i = 0; i < tam; i++){
    heap[i+inicioDados] = vet[i];
  }
  tamanho = tam;
  arruma();
}

torneio::~torneio(){
  delete[] heap;
}

void torneio::arruma(){
  for (int i = inicioDados - 1; i>=0; i--){
    
  }
}

int torneio::pai (int i){
  return (i-1)/2;
}

int torneio::esquerdo (int i){
  return 2*i+1;
}

int torneio::direito(int i){
  return 2*i+2;
}

void torneio::copiaMenor(int i){
  int esq = esquerdo(i);
  int dir = direito(i);
  int menor = -1;

  if (esq < capacidade){
    if ((dir < capacidade) and (heap[dir] < heap[esq])){
      menor = dir;
    } else {
      menor = esq;
    }
    heap[i] = heap[menor];
  } else {
    heap[i] = INVALIDO;
  }
}

void torneio::copiaMaior(int i){
  int esq = esquerdo(i);
  int dir = direito(i);
  int maior = -1;
  //int menor = -1;

  
    if (esq < capacidade){
      if ((dir < capacidade) and (heap[dir] > heap[esq])){
        maior = dir;
      } else {
        maior = esq;
      }
      heap[i] = heap[maior];
    } else {
      heap[i] = INVALIDO;
    }
  
  //contador++;   
}

void torneio::copiaSubindo (int i){
  int p = pai(i);
  if (contador % 2 == 0){
    if ((heap[i] < heap[p])){
      heap[p] = heap[i];
      copiaSubindo(p);
    } 
  } else {
    if ((heap[i] > heap[p])){
      heap[p] = heap[i];
      copiaSubindo(p);
    }
  }
  //contador++;
}

void torneio::insere (dado d){
  if (tamanho == capacidade){
    cerr << "Erro ao adicionar"<< endl;
    exit(EXIT_FAILURE);
  }
  heap[tamanho+inicioDados] = d;
  copiaSubindo(tamanho+inicioDados);
  tamanho++;
}

void torneio::imprime (){
  for (int i = 0; i < capacidade; i++){
    cout << heap[i] << " ";
  }
  cout << endl;
}

dado torneio::retiraRaiz(){
  if (tamanho == 0){
    cerr << "Erro ao retirar raiz" << endl;
    exit(EXIT_FAILURE);
  }
  dado aux = heap[0];
  swap(heap[0], heap[tamanho-1]);
  tamanho--;
  copiaMaior(0);
  return aux;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main () {
  int tam;
  cin >> tam; 
  int* vet = new int[tam];

  for (int i = 0; i < tam; i++){
    cin >> vet[i];
  } 

  torneio tor(vet, tam);

  tor.imprime();
  cout << tor.retiraRaiz() << endl;

  return 0;
}