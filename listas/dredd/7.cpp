#include <iostream>
#include <string>
using namespace std;

typedef char Dado;

class noh {
  friend class lista;
  private:
    // dado está constante para não poder ser alterado
    const Dado dado;
    noh* proximo;
  public:
    noh(Dado d) : dado(d){
      proximo = NULL;
    }
};

class lista {
  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); 
  public:
    lista();
    ~lista();
    //lista& operador=(const lista& umaLista);
    inline void insere (Dado dado);
    void insereFim (Dado dado);
    inline bool vazia ();
    Dado removeFim ();
    Dado removeInicio ();
    string palindromo ();
};

// construtor de lista vazia
lista::lista(){
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

lista::~lista(){
  removeTodos();
}

void lista::removeTodos (){
  noh* aux = primeiro;
  noh* temp;

  while (aux != NULL){
    temp = aux;
    aux = aux -> proximo;
    delete temp;
  }

  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

void lista::insere (Dado dado){
  insereFim(dado);
}

void lista::insereFim (Dado dado){
  // cria um novo nó primeiro
  noh* novo = new noh(dado);

  // insere o nó na lista
  // se a lista estiver vazia, insere o primeiro nó
  if (vazia()){
    primeiro = novo;
    ultimo = novo;
  } else {
    ultimo -> proximo = novo;
    ultimo = novo;
  }
  tamanho++;
}

inline bool lista::vazia(){
  return (primeiro == NULL);
  // or
  // return (tamanho == 0);
}

Dado lista::removeFim (){
  if (vazia()){
    cerr << "Lista vazia"<< endl;
    exit(EXIT_FAILURE);
  }
  noh* aux = primeiro;
  noh* anterior;
  Dado retorna;

  while (aux -> proximo != NULL){
    anterior = aux;
    aux = aux -> proximo;
  } // chegou no penultimo

  retorna = ultimo ->dado;
  if (anterior){
    anterior -> proximo = NULL;
  }
  delete ultimo;
  if (anterior){
    ultimo = anterior;
  }

  if (vazia()) {
    primeiro = NULL;
    ultimo = NULL;
  }
  tamanho--;
  return retorna;
}

Dado lista::removeInicio () {
  if (vazia()){
    cerr << "Lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  Dado retorna = primeiro -> dado;
  noh* aux = primeiro;
  primeiro = primeiro -> proximo;
  delete aux;
  if (vazia()) ultimo = NULL;
  tamanho--;
  return retorna;
}

string lista::palindromo (){
  Dado aux1, aux2;

  while (tamanho > 1){
    aux2 = removeFim();
    aux1 = removeInicio();
    if (aux1 != aux2){
      return "nao";
    }
  }
  return "sim";
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main (){
  lista lista1;
  char letra;

  while ((cin >> letra) and (letra != '#')){
    if (letra != '#'){
      lista1.insere(letra);
    }
  }

  cout << lista1.palindromo() << endl;

  return 0;
}