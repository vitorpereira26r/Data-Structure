#include <iostream>
using namespace std;

typedef string Dado;

class noh{
  friend class lista;
  private:
    Dado dado;
    unsigned quantity;
    noh* proximo;
    noh* anterior;
  public:
    noh (Dado d, unsigned q){
      dado = d;
      quantity = q;
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
    void insereInicio(Dado dao, unsigned quantity);
    void insereFim (Dado dado, unsigned quantity);
    void insere (Dado dado, unsigned quantity);
    void removeTodos();
    bool vazia(){
      return (inicio == NULL);
    }
    void imprimeLista();
    int procura (Dado valor);
    void removeInicio();
    void removeFim();
    void removeValor (Dado valor);
    void imprimirItem(Dado item);
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

void lista::insere (Dado dado, unsigned quantity){
  int busca = procura(dado);
  if (busca == -1){
    insereFim(dado, quantity);
  }
}

void lista::insereFim (Dado dado, unsigned quantity){
  noh* novo = new noh(dado, quantity);

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

void lista::insereInicio (Dado dado, unsigned quantity){
  noh* novo = new noh(dado, quantity);

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

  cout << "[";

  while (aux != NULL) {
    cout << "(" << aux -> dado << ", " << aux -> quantity << ")";
    aux = aux -> proximo;
  } 
  cout << "]" << endl;

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

void lista::imprimirItem (Dado item){
  noh* auxiliar = inicio;
  int busca = procura (item);
  if (busca == -1) {
    cout << "item nao existente" << endl;
  } else {
    while (auxiliar != NULL) {
      if (auxiliar -> dado == item){
        cout << "[(" << auxiliar -> dado << ", " << auxiliar -> quantity << ")]" << endl;
      }
      auxiliar = auxiliar -> proximo;
    } 
  }
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
    cout << "item nao exixtente" << endl;
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

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main () {
  char option;
  lista lista1;
  string nomeProduto;

  do {
    cin >> option;
    switch (option)
    {
      case 'i':
        //insere na lista
        unsigned quantity;
        cin >> nomeProduto;
        cin >> quantity;
        lista1.insere(nomeProduto, quantity);
        break;
      case 'r':
        //remove da lista
        cin >> nomeProduto;
        lista1.removeValor(nomeProduto);
        break;
      case 'c':
        //consulta se o elemento está na lista
        cin >> nomeProduto;
        lista1.imprimirItem(nomeProduto);
        break;
      case 'p':
        //imprime a lista inteira
        lista1.imprimeLista();
        break;
    }
  } while (option != 'q');
  lista1.imprimeLista();

  return 0;
}