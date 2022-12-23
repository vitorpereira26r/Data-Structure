#include <iostream>   

typedef unsigned TCodProcesso;

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        bool Inserir(TCodProcesso codigo, int prioridade);
        // Retira e retorna a raiz
        bool Retirar(TCodProcesso* ptCodigo, int* ptPrioridade);
        // Verifica se a heap está vazia
        bool Vazia();
    private:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        int capacidade;
        int tamanho;
        TCodProcesso* dados;
        int* prioridade;
};

using namespace std;

Heap::Heap(int cap) {
  capacidade = cap;
  dados = new TCodProcesso[cap];
  prioridade = new int[cap];
  tamanho = 0;
}

Heap::~Heap() {
  delete[] dados;
}

void Heap::ArrumarDescendo(int i) {
  int esq = Esquerdo(i);
  int dir = Direito(i);
  int maior;

  if ((esq < tamanho) and (prioridade[esq] > prioridade[i])){
    maior = esq;
  } else {
    maior = i;
  }

  if ((dir < tamanho) and (prioridade[dir] > prioridade[maior])){
    maior = dir;
  }

  if (maior != i){
    swap(dados[i], dados[maior]);
    swap(prioridade[i], prioridade[maior]);
    ArrumarDescendo(maior);
  } 
    // Arruma as posicoes de i para baixo.
}

void Heap::ArrumarSubindo(int i) {
  int p = Pai(i);
  if (prioridade[i] > prioridade[p]){
    swap(dados[i], dados[p]);
    swap(prioridade[i], prioridade[p]);
    ArrumarSubindo(p);
  }
    // Arruma as posicoes de i para cima.
}

int Heap::Pai(int i) {
  return (i-1)/2;
}

int Heap::Esquerdo(int i) {
  return 2*i+1;
}

int Heap::Direito(int i) {
  return 2*i+2;
}

bool Heap::Retirar(TCodProcesso* ptCodigo, int* ptPrioridade) {
  if (tamanho == 0){
    return false;
  }
  unsigned* auxD = &dados[0];
  int* auxP = &prioridade[0];
  ptCodigo = auxD;
  ptPrioridade = auxP;
  swap(dados[0], dados[tamanho-1]);
  swap(prioridade[0], prioridade[tamanho-1]);
  tamanho--;
  ArrumarDescendo(0);
  return auxD, auxP;
    // Retira um codigo/prioridade, retornando os dois valores.
    // Retorna falso se o heap estiver vazio.
}

bool Heap::Vazia() {
    return (tamanho == 0);
}

bool Heap::Inserir(TCodProcesso codigo, int prioridade1) {
  if (tamanho == capacidade){
    return false;
  }
  dados[tamanho] = codigo;
  prioridade[tamanho] = prioridade1;
  ArrumarSubindo(tamanho);
  tamanho++;
    // Insere um codigo/prioridade no heap.
    // Retorna falso se o heap estiver cheio.
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Heap heap(capacidade);
    char comando;
    TCodProcesso codigo;
    int prioridade;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir um processo no heap
                cin >> codigo >> prioridade;
                heap.Inserir(codigo, prioridade);
                break;
            case 'o': // obter um processo do heap
                if (heap.Retirar(&codigo, &prioridade))
                    cout << codigo << ' ' << prioridade << endl;
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 's': //sair
                break;
        }
    } while (comando != 's');
    return 0;
}