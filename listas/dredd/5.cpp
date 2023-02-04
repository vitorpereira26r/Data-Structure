#include <iostream>
using namespace std;


class noh {
  friend class lista;
  private:
    // dado está constante para não poder ser alterado
    unsigned matricula;
    string nome;
    unsigned periodo;
    noh* proximo;
    noh* anterior;
  public:
    noh (unsigned m, string n, unsigned p){
      proximo = NULL;
      matricula = m;
      nome = n;
      periodo = p;
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
    lista(unsigned matricula, string nome, unsigned periodo);
    ~lista();
    //lista& operador=(const lista& umaLista);
    void insereFim (unsigned matricula, string nome, unsigned periodo);
    void insereInicio (unsigned matricula, string nome, unsigned periodo);
    void insereNohFim (noh* no);
    void imprime ();
    inline bool vazia ();
    void removeFim ();
    void removeInicio ();
    bool inverte ();
    unsigned getMatricula ();
    string getNome ();
    unsigned getPeriodo ();
};

// construtor de lista vazia
lista::lista(){
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// construtor de cópia
lista::lista(unsigned matricula, string nome, unsigned periodo){
  noh* novo = new noh(matricula, nome, periodo);
  
  if (vazia()){
    primeiro = novo;
    ultimo = novo;
  } else {
    ultimo -> proximo = novo;
    ultimo = novo;
  }
  tamanho++;
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

void lista::insereFim (unsigned matricula, string nome, unsigned periodo){
  // cria um novo nó primeiro
  noh* novo = new noh(matricula, nome, periodo);


  // insere o nó na lista
  // se a lista estiver vazia, insere o primeiro nó
  if (vazia()){
    primeiro = novo;
    ultimo = novo;
  } else {
    ultimo -> proximo = novo;
    primeiro -> anterior = ultimo;
    ultimo = novo;
  }
  tamanho++;
}

void lista::insereInicio (unsigned matricula, string nome, unsigned periodo){
  noh* novo = new noh(matricula, nome, periodo);


  // insere o nó na lista
  // se a lista estiver vazia, insere o primeiro nó
  if (vazia()){
    primeiro = novo;
    ultimo = novo;
  } else {
    novo -> proximo = primeiro;
    primeiro ->anterior = novo;
    primeiro = novo;
  }
  tamanho++;
}

void lista::imprime(){
  noh* aux = primeiro;

  cout << "[";
  while (aux != NULL){
    if (aux -> proximo == NULL){
      cout << aux->matricula << " - " << aux->nome;
    } else {
      cout << aux->matricula << " - " << aux->nome << ", ";
    }
    aux = aux -> proximo;
  }

  cout << "]" << endl;
  //cout << tamanho << endl;
  //cout << ultimo -> nome << endl;
  //cout << primeiro -> proximo << endl;
}

inline bool lista::vazia(){
  return (primeiro == NULL);
  // or
  // return (tamanho == 0);
}

void lista::removeFim (){
  if (vazia()){
    cerr << "Lista vazia"<< endl;
    exit(EXIT_FAILURE);
  }
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
}

void lista::removeInicio () {
  if (vazia()){
    cerr << "Lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* aux = primeiro;
  primeiro = primeiro -> proximo;
  delete aux;
  if (vazia()) ultimo = NULL;
  tamanho--;
}

bool lista::inverte (){
  noh* aux1 = primeiro;
  noh* aux2 = ultimo;
  noh* troca;

  while(true){
    troca = aux1;
    aux1 = aux2;
    aux2 = troca;
  }
}

unsigned lista::getMatricula () {
  return ultimo -> matricula;
}

string lista::getNome () {
  return ultimo -> nome;
}

unsigned lista::getPeriodo () {
  return ultimo -> periodo;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int main (){
  int num;
  lista lista1;
  cin >> num;
  unsigned matricula, periodo;
  string nome;

  for (int i = 0; i < num; i++){
    cin >> matricula;
    cin >> nome;
    cin >> periodo;
    lista1.insereFim(matricula, nome, periodo);
  }


  lista1.imprime();
  lista1.inverte();
  lista1.imprime();

  return 0;
}