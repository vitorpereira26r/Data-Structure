#include <iostream>
using namespace std;

int sizeHash;

int Hash (int key){
  return key % sizeHash;
}

class Node {
  friend class lista;
  private:
    int key;
    string value;
    Node* proximo;
  public:
    Node(int key, string value){
      proximo = NULL;
      this -> key = key;
      this -> value = value;
    };
};

class lista {
  private:
    Node* first;
    Node* last;
    int size;
  public:
    lista();
    ~lista();
    void insereFim (int key, string value);
    void procura (int key);
    void imprime ();
    inline bool vazia ();
    void removeValor (int key);
    int getKey ();
    string getValue ();
    bool busca (int key);
};

class HashTable {
  private:
    lista* hashArray;
    int capacity;
    int size;
  public:
    HashTable();
    ~HashTable();
    void addToHash (int key, string value);
    void removeFromHash (int key);
    void search (int key);
    void print();
    void resize ();
};

HashTable::HashTable (){
  hashArray = new lista[sizeHash];
  capacity = sizeHash;
  this->size = 0;
}

HashTable::~HashTable(){
  delete [] hashArray;
}

void HashTable::addToHash (int key, string value){
  int position = Hash(key);
  hashArray[position].insereFim(key, value);
  size++;
  if((size*100 / sizeHash) >= 70){
    resize();
  }
}

void HashTable::removeFromHash(int key){
  int position = Hash(key);
  if(! hashArray[position].vazia()){
    hashArray[position].removeValor(key);
    size--;
  } else {
    cout << "ERRO" << endl;
  }
}

void HashTable::search (int key){
  int position = Hash(key);
  if (hashArray[position].vazia()){
    cout << "item nao encontrado" << endl;
  } else {
    hashArray[position].procura(key);
  }
}

void HashTable::print (){
  for (int i = 0; i < sizeHash; i++){
    cout << "Posicao " << i << ": ";
    hashArray[i].imprime();
    //cout << endl;
  }
  cout << "-----------------------" << endl;
}

void HashTable::resize (){
  sizeHash *= 2;
  lista* arrayAux = new lista[sizeHash];
  for (int i = 0; i < sizeHash/2; i++){
    while (! hashArray[i].vazia()){
      string value = hashArray[i].getValue();
      int key = hashArray[i].getKey();
      hashArray[i].removeValor(key);
      int position = Hash (key);
      arrayAux[position].insereFim(key, value);
    }
  }
  delete [] hashArray;
  hashArray = arrayAux;
}

lista::lista (){
  size = 0;
  first = NULL;
  last = NULL;
}

lista::~lista	(){
  Node* aux = first;
  Node* temp;

  while (aux != NULL){
    temp = aux;
    aux = aux -> proximo;
    delete temp;
  }

  size = 0;
  first = NULL;
  last = NULL;
}

int lista::getKey (){
  int key = first -> key;
  return key;
}

string lista::getValue (){
  string value = first -> value;
  return value;
}

void lista::insereFim (int key, string value){
  // cria um novo nó primeiro
  Node* novo = new Node(key, value);

  // insere o nó na lista
  // se a lista estiver vazia, insere o primeiro nó
  if (vazia()){
    first = novo;
    last = novo;
  } else {
    last -> proximo = novo;
    last = novo;
  }
  size++;
}

void lista::procura(int key){
  Node* aux = first;
  bool finded = false;

  if(first -> key == key){
    cout << first -> value << endl;
    finded = true;
  } else if (last -> key == key){
    cout << last -> value << endl;
    finded = true;
  } else {
    while (aux -> proximo != NULL){
      if (aux -> key == key){
        cout << aux -> value << endl;
        finded = true;
      }
      aux = aux -> proximo;
      //cout << "entrou no loop\n";
    }
    //cout << "passou 1" << endl;
  }
  //cout << "nem entrou\n";
  if (finded == false){
    cout << "item nao encontrado" << endl;
  }
}

bool lista::busca (int key){
  Node* aux = first;

  if(first -> key == key){
    //cout << "ERRO 1" << endl;
    return true;
  } else if (last -> key == key){
    //cout << "ERRO 2" << endl;
    return true;
  } else {
    //cout << "ERRO 3" << endl;
    while (aux -> proximo != NULL){
      //cout << "ERRO 4" << endl;
      if (aux -> key == key){
        //cout << "ERRO 5" << endl;
        return true;
      }
      //cout << "ERRO 6" << endl;
      aux = aux -> proximo;
    }
    //cout << "ERRO 7" << endl;
  }
  //cout << "ERRO 8" << endl;
  return false;
}

void lista::imprime(){
  Node* aux = first;
  int cont = 0;

  while (aux != NULL){
    if (cont == 0){
      cout << aux->key << " " << aux->value << " ";
    }
    else if(cont == 1){
      cout << endl << "Lista de colisao: ";
      cout << aux->key << " " << aux->value;
    } 
    else if (cont > 1){
      cout << ", " << aux->key << " " << aux->value << " ";
    }
    aux = aux -> proximo;
    cont++;
  }
  cout << endl;
}

inline bool lista::vazia(){
  return (first == NULL);
}

void lista::removeValor (int key){
  bool removed = false;
  bool encontrado = busca(key);

  if (encontrado){
    if(first -> key == key){
      first = first -> proximo;
      removed = true;
      //cout << "error 1" << endl;
    } else if (last -> key == key && removed == false){
      Node* aux = first;
      //cout << "error 2" << endl;
      while (aux -> proximo != last){
        aux = aux -> proximo;
        //cout << "error 3" << endl;
      }
      //cout << "error 4" << endl;
      aux -> proximo = NULL;
      removed = true;
    } else if (removed == false && first -> proximo != NULL){
      //cout << "error 5" << endl;
      Node* aux = first;
      while (aux -> proximo -> key != key || aux -> proximo != NULL){
        //cout << "error 6" << endl;
        aux = aux -> proximo;
        //cout << "error 7" << endl;
      }
      if (aux -> proximo -> key == key){
        //cout << "error 6" << endl;
        aux -> proximo = aux -> proximo -> proximo;
        removed = true;
      }
      //cout << "error 9" << endl;
    }
  } else {
    cout << "ERRO" << endl;
  }
}

int main () {
  cin >> sizeHash;
  HashTable myHash;
  char option;
  int key;
  string value;

  do {
    cin >> option;
    switch(option){
      case 'I':
        cin >> key;
        cin >> value;
        myHash.addToHash(key, value);
        break;
      case 'P':
        myHash.print();
        break;
      case 'R':
        cin >> key;
        myHash.removeFromHash(key);
        break;
      case 'B':
        cin >> key;
        myHash.search(key);
        break;
    }
  } while (option != 'S');

  return 0;
}