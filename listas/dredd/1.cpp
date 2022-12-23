#include <iostream>
using namespace std;

typedef int Dado;

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
    void imprimeReverso (noh* umNoh); // imprime o reverso a partir de um nó
  public:
    lista();
    lista(const lista& umaLista);
    ~lista();
    //lista& operador=(const lista& umaLista);
    inline void insere (Dado dado);
    void insereFim (Dado dado);
    void insereInicio (Dado dado);
    void insereNaPosicao (int posicao, Dado dado);
    int procura (Dado valor); // retorna a posição do nó com o valor
    void imprime ();
    void imprimeReverso ();
    void imprimeReversoAux(noh* umNoh);
    inline bool vazia ();
    Dado removeFim ();
    Dado removeInicio ();
};

// construtor de lista vazia
lista::lista(){
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// construtor de cópia
lista::lista(const lista& umalista){
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;

  // percorre a lista recebida como parametro copiando os dados
  noh* aux = umalista.primeiro;

  while (aux != NULL){
    insereFim(aux->dado);
    aux = aux -> proximo;
  }
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
/*
lista& lista::operador=(const lista& umaLista){
  // limpa a lista atual
  removeTodos();
  // percorre a lista recebida como parâmetro, copiando os dados
  noh* aux = umaLista.primeiro;

  while (aux != NULL){
    insereFim(aux -> dado);
    aux = aux -> proximo;
  }

  return *this;
}*/

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

void lista::insereInicio (Dado dado){
  // primeiro cria o novo nó
  noh* novo = new noh(dado);

  // insere o nó na lista
  // se estiver vazia, insere o primeiro nó
  if(vazia()){
    primeiro = novo;
    ultimo = novo;
  } else {
    novo -> proximo = primeiro;
    primeiro = novo;
  }
  tamanho++;
}

void lista::insereNaPosicao (int posicao, Dado dado){
  noh* novo = new noh(dado);

  // verifica se é possível adicionar na posição
  if ((posicao <= tamanho) and (posicao >= 0)){
    if (vazia()){
      primeiro = novo;
      ultimo = novo;
    } else if (posicao == 0){
      novo -> proximo = primeiro;
      primeiro = novo;
    } else if (posicao == tamanho){
      ultimo -> proximo = novo;
      ultimo =novo;
    } else {
      noh* aux = primeiro;
      int posAux = 0;

      while (posAux < (posicao-1)){
        aux = aux -> proximo;
        posAux++;
      }
      novo -> proximo = aux -> proximo;
      aux -> proximo = novo;
    }
    tamanho++;
  } else {
    cerr << "posicao inexistente" << endl;
    exit(EXIT_FAILURE);
  }
}

int lista::procura(Dado valor){
  noh* aux = primeiro;
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

void lista::imprime(){
  noh* aux = primeiro;

  while (aux != NULL){
    cout << aux->dado << " ";
    aux = aux -> proximo;
  }

  cout << endl;
}

void lista::imprimeReverso (){
  imprimeReversoAux(primeiro);
  cout << endl;
}

void lista::imprimeReversoAux (noh* umNoh){
  if (umNoh != NULL){
    imprimeReversoAux(umNoh -> proximo);
    cout << umNoh->dado << " ";
  }
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

  Dado valor = ultimo -> dado;
  noh* aux = primeiro;
  noh* anterior;

  while (aux -> proximo != NULL){
    anterior = aux;
    aux = aux -> proximo;
  } // chegou no penultimo

  delete ultimo;
  anterior -> proximo = NULL;
  ultimo = anterior;

  if (vazia()) primeiro = NULL;
  tamanho--;
  return valor;
}

Dado lista::removeInicio () {
  if (vazia()){
    cerr << "Lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  Dado valor = primeiro ->dado;
  noh* aux = primeiro;
  primeiro = primeiro -> proximo;
  delete aux;
  if (vazia()) ultimo = NULL;
  tamanho--;
  return valor;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main (){
  lista lista1, lista2, lista3;
  int valor1, valor2;

  do {
    cin >> valor1;
    if (valor1 != -1){
      lista1.insere(valor1);
    }
  } while (valor1 != -1);

  do {
    cin >> valor2;
    if (valor2 != -1){
      lista2.insere(valor2);
    }
  } while (valor2 != -1);

  Dado um = 0;
  while ((! lista1.vazia()) || (! lista2.vazia())){
    if ((! lista1.vazia()) && (! lista2.vazia())){
      Dado aux1 = lista1.removeInicio();
      Dado aux2 = lista2.removeInicio();
      Dado soma = aux1 + aux2 + um;
      Dado resto = soma - 10;
      if (resto >= 0){
        lista3.insere(resto);
        um = 1;
      } else {
        lista3.insere(soma);
        um = 0;
      }
    } else if ((! lista1.vazia()) && (lista2.vazia())){
      Dado aux = lista1.removeInicio();
      Dado soma = aux + um;
      Dado resto = soma - 10;
      if (resto >= 0){
        lista3.insere(resto);
        um = 1;
      } else {
        lista3.insere(soma);
        um = 0;
      }
    } else if ((lista1.vazia()) && (! lista2.vazia())){
      Dado aux = lista2.removeInicio();
      Dado soma = aux + um;
      Dado resto = soma - 10;
      if (resto >= 0) {
        lista3.insere(resto);
      } else {
        lista3.insere(soma);
        um = 0;
      }
    }
  }

  lista3.imprime();

  return 0;
}