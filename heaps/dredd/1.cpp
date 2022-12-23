#include <iostream>
#include <cstdlib>

using namespace std;

typedef int dado;

class MinHeap{
  private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai (int i);
    inline int esquerdo (int i);
    inline int direito (int i);
    void arruma(); // heapify
    void corrigeDescendo (int i); 
    void corrigeSubindo (int i);
  public:
    MinHeap (int cap);
    MinHeap (dado vet[], int tam);
    ~MinHeap();
    void imprime ();
    dado espiaRaiz();
    dado retiraRaiz();
    void insere(dado d);
};

MinHeap::MinHeap(dado vet[], int tam){
  capacidade = tam;

  heap = new dado[capacidade];
  for (int i = 0; i < tam; i++){
    heap[i] = vet[i];
    tamanho = tam;
  }
  arruma();
}

MinHeap::~MinHeap(){
  delete[] heap;
}

void MinHeap::arruma(){
  for (int i = (tamanho/2-1); i>=0; i--){
    corrigeDescendo(i);
    cout << i << ": ";
    imprime();
  }
}

int MinHeap::pai (int i){
  return (i-1)/2;
}

int MinHeap::esquerdo (int i){
  return 2*i+1;
}

int MinHeap::direito(int i){
  return 2*i+2;
}

void MinHeap::corrigeDescendo(int i){
  int esq = esquerdo(i);
  int dir = direito(i);
  int menor;

  if ((esq < tamanho) and (heap[esq] > heap[i])){
    menor = esq;
  } else {
    menor = i;
  }

  if ((dir < tamanho) and (heap[dir] < heap[menor])){
    menor = dir;
  }

  if (menor != i){
    swap(heap[i], heap[menor]);
    corrigeDescendo(menor);
  }  
}

void MinHeap::corrigeSubindo(int i){
  int p = pai(i);
  if (heap[i] < heap[p]){
    swap(heap[i], heap[p]);
    corrigeSubindo(p);
  }
}

void MinHeap::imprime(){
  for (int i = 0; i < tamanho; i++){
    cout << heap[i] << " ";
  }
  cout << endl;
}

dado MinHeap::espiaRaiz(){
  return heap[0];
}

dado MinHeap::retiraRaiz(){
  if (tamanho == 0){
    cerr << "Erro ao retirar raiz" << endl;
    exit(EXIT_FAILURE);
  }
  dado aux = heap[0];
  swap(heap[0], heap[tamanho-1]);
  tamanho--;
  corrigeDescendo(0);
  return aux;
}

void MinHeap::insere(dado d){
  if (tamanho == capacidade){
    cerr << "Erro ao inserir" << endl;
    exit(EXIT_FAILURE);
  }
  heap[tamanho] = d;
  corrigeSubindo(tamanho);
  tamanho++;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main (){
  int tam;
  cin >> tam;
  int* vet = new int[tam];

  for (int i = 0; i < tam; i++){
    cin >> vet[i];
  }
  MinHeap h(vet, tam);

  return 0;
}