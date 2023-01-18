#include <iostream>
using namespace std;

int arraySize;

int Hash(int key)
{
  return key % arraySize;
}

class Node{
  friend class HashTable;
  private:
    string *arrayValue;
    int *arrayKey;
    int position; 
  public:
    Node(){
      arrayValue = new string[4];
      arrayKey = new int[4];
      position = 0;
      for (int i = 0; i < 4; i++){
        arrayKey[i] = -1;
        arrayValue[i] = "";
      }
    }
    void addToArray(string value, int key){
      bool aloc = false;
      for(int i = 0; i < 4; i++){
        if (key == arrayKey[i]){
          cout << "ITEM JÁ ESTÁ NA TABELA" << endl;
          aloc = true;
        }
        if (arrayKey[i] == -1 and aloc == false){
          arrayKey[i] = key;
          arrayValue[i] = value;
          aloc = true;
        }
      }
      if (aloc == false){
        cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!" << endl;
      }
    }
    string search(int key){
      for (int i = 0; i < 4; i++){
        if (arrayKey[i] == key){
          return arrayValue[i];
        }
      }
      return "NÃO ENCONTRADO!";
    }
    void printFourArray(){
      for (int i = 0; i < 4; i++){
        cout << "[" << arrayKey[i] << "/" << arrayValue[i] << "]";
      }
    }
};

class HashTable
{
private:
  Node *arrayHash;
  int capacity;

public:
  HashTable();
  void printHash();
  void addToHash (int key, string value);
  string searshHash (int key);
};

HashTable::HashTable()
{
  arrayHash = new Node[arraySize];
  capacity = arraySize;
}

void HashTable::printHash()
{
  for (int i = 0; i < capacity; i++)
  {
    Node aux = arrayHash[i];
    cout << i << ":";
    aux.printFourArray();
    cout << endl;
  }
}

void HashTable::addToHash (int key, string value){
  int position = Hash(key);
  Node aux = arrayHash[position];
  aux.addToArray(value, key);
}

string HashTable::searshHash(int key){
  int position = Hash(key);
  Node aux = arrayHash[position];
  return aux.search(key);
}

int main()
{
  int dataQuantity, key;
  string value;
  cin >> arraySize;
  cin >> dataQuantity;
  HashTable myHash;

  for (int i = 0; i < dataQuantity; i++){
    cin >> key;  
    cin >> value;
    myHash.addToHash(key, value);
  }

  for (int i = 0; i < 4; i++){
    cin >> key;
    cout << myHash.searshHash(key) << endl;
  }

  myHash.printHash();

  return 0;
}
