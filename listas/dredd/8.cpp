#include <iostream>
using namespace std;

typedef int Dado;

class noh{
  friend class lista;
  private:
    Dado dado;
    noh* proximo;
    noh* anterior;
  public:
    noh (Dado d){
      dado = d;
      proximo = NULL;
      anterior = NULL;
    }
};

class lista{
  private:
    noh* inicio;
    noh* fim;
    int tamanho;
  public:
    lista();
    ~lista();        
    void insereInicio(int c);
    void insereFim (int c);
    void insere (Dado dado);
    void removeTodos();
    bool vazia(){
      return (inicio == NULL);
    }
    void imprimeLista();
    void insereNaPosicao (int posicao, Dado dado);
    int procura (Dado valor);
    void removeInicio();
    void removeFim();
    void removeValor (Dado valor);
    void ordena ();
};

lista::lista(){
  inicio = NULL;
  fim = NULL;
  tamanho = 0;
}

lista::~lista (){
  removeTodos();
}

void lista::removeTodos (){
  noh* aux = inicio;
  noh* temp;

  while (aux != NULL){
    temp = aux;
    aux = aux -> proximo;
    delete temp;
  }

  tamanho = 0;
  inicio = NULL;
  fim = NULL;
}

void lista::insere (Dado dado){
  insereFim(dado);
}

void lista::insereFim (Dado dado){
  noh* novo = new noh(dado);

  if (vazia()){
    inicio = novo;
    fim = novo;
  } else {
    fim -> proximo = novo;
    novo -> anterior = fim;
    fim = novo;
  }
  tamanho++;
}

void lista::insereInicio (Dado dado){
  noh* novo = new noh(dado);

  if (vazia()){
    inicio = novo;
    fim = novo;
  } else {
    novo -> proximo = inicio;
    inicio ->anterior = novo;
    inicio = novo;
  }
  tamanho++;
}

void lista::insereNaPosicao (int posicao, Dado dado){
  noh* novo = new noh(dado);

  // verifica se é possível adicionar na posição
  if ((posicao <= tamanho) and (posicao >= 0)){
    if (vazia()){
      inicio = novo;
      fim = novo;
    } else if (posicao == 0){
      novo -> proximo = inicio;
      inicio -> anterior = novo;
      inicio = novo;
    } else if (posicao == tamanho){
      fim -> proximo = novo;
      novo -> anterior = fim;
      fim = novo;
    } else {
      noh* aux = inicio;
      int posAux = 0;

      while (posAux < (posicao-1)){
        aux = aux -> proximo;
        posAux++;
      }
      novo -> proximo = aux -> proximo;
      aux -> proximo -> anterior = novo;
      aux -> proximo = novo;
      novo -> anterior = aux;
    }
    tamanho++;
  } else {
    cerr << "posicao inexistente" << endl;
    exit(EXIT_FAILURE);
  }
}

int lista::procura(Dado valor){
  noh* aux = inicio;
  int posAux = 0;

  while ((aux != NULL) and (aux -> dado != valor)){
    posAux++;
    aux = aux->proximo;
  }

  if (aux == NULL){
    posAux = -1;
  }
  return posAux;
}

void lista::imprimeLista (){
  noh* aux = inicio;

  while (aux != NULL){
    cout << aux->dado << " ";
    aux = aux -> proximo;
  }
  cout << endl;

  // ao contrario 
  /*
  aux = ultimo;
  while (aux != NULL){
    cout << aux->dado << " ";
    aux = aux -> anterior;
  }
  cout << endl;
  */
}

void lista::removeInicio () {
  if (vazia()){
    cerr << "Lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* aux = inicio;
  inicio = inicio -> proximo;
  if (inicio != NULL){
    inicio -> anterior = NULL;
  }
  delete aux;
  if (vazia()) fim = NULL;
  tamanho--;
}

void lista::removeFim (){
  if (vazia()){
    cerr << "Lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* aux = fim;
  fim = fim -> anterior;
  if (fim != NULL){
    fim -> proximo = NULL;
  }
  delete aux;
  if (vazia()) fim = NULL;
  tamanho--;
}

void lista::removeValor (Dado valor){
  noh* aux = inicio;

  while ((aux != NULL) and (aux -> dado != valor)){
    aux = aux -> proximo;
  }

  if (aux == NULL){
    cerr << "valor não encontrado" << endl;
    exit(EXIT_FAILURE);
  } else {
    noh* anterior = aux -> anterior;
    noh* proximo = aux -> proximo;
    if (anterior != NULL){
      anterior -> proximo = proximo;
    } else {
      inicio = aux -> proximo;
    }
    if (proximo != NULL){
      proximo -> anterior = anterior;
    } else {
      fim = aux -> proximo;
    }
    delete aux;
  }
  tamanho--;
  if (vazia()){
    inicio = NULL;
    fim = NULL;
  }
}

void lista::ordena (){
  if (inicio == NULL){
    cerr << "lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  for (noh* i = inicio; i-> proximo != NULL; i = i-> proximo){
    noh* menor = i;
    for (noh* j = i -> proximo; j != NULL; j = j -> proximo){
      if (j -> dado < menor -> dado){
        menor = j;
      }
      int aux = i -> dado;
      i -> dado = menor -> dado;
      menor -> dado = aux;
    }
  }
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main (){
  lista lista1, lista2, lista3;
  int num1, num2;
  
  do {
    cin >> num1;
    if (num1 != -1){
      lista1.insereFim(num1);
    }
    if ((num1 % 2 == 0) and (num1 != -1)){
      lista3.insere(num1);
    }
  } while (num1 != -1);

  do {
    cin >> num2;
    if (num2 != -1){
      lista2.insereFim(num2);
      if (num2 % 2 != 0){
        lista3.insere(num2);
      }
    }
  } while (num2 != -1);

  //lista1.imprimeLista();
  //lista2.imprimeLista();
  //lista3.imprimeLista();

  lista3.ordena();

  //lista1.imprimeLista();
  //lista2.imprimeLista();
  lista3.imprimeLista();
  
  return 0;
}