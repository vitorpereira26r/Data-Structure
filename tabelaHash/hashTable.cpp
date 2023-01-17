#include <iostream>
using namespace std;

int ANY_PRIME = 23;
static const int SIZE = 7;
int hash (string key);

class Node {
  public:
    string key;
    int value;
    Node* next;

    Node (string key, int value){
      this->key = key;
      this->value = value;
      next = NULL;
    }
};

class hashTable{
  private:
    Node* dataMap[SIZE];
  public:
    void printTable();
    void set (string key, int value);
    int get (string key);
};

int main (){
  hashTable* myHashTable = new hashTable();

  myHashTable->set("nails", 100);
  myHashTable->set("tile", 50);
  myHashTable->set("lumber", 80);

  myHashTable->printTable();
/*
  cout << "Lumber: " << myHashTable -> get("lumber") << endl;
  cout << "Tile: " << myHashTable -> get("tile") << endl;
  cout << "Bolts: " << myHashTable -> get("bolts") << endl;
*/
  return 0;
}

int Hash (string key) {
  int hash = 0;
  for (int i = 0; i < key.length(); i++){
    int asciiValue = int (key[i]);
    hash = (hash + asciiValue * ANY_PRIME) % SIZE;
  }
  return hash;
}

void hashTable::printTable (){
  for (int i = 0; i < SIZE; i++){
    cout << i << ":" << endl;
    if (dataMap[i]){
      Node* temp = dataMap[i];
      while(temp){
        cout << "    {" << temp -> key << ", " << temp -> value << "}";
        temp = temp -> next;
        cout << endl;
      }
    }
  }
}

void hashTable::set (string key, int value){
  int index = Hash(key);
  Node* newNode = new Node(key, value);
  if (dataMap[index] == NULL){
    dataMap[index] = newNode;
  } else {
    Node* temp = dataMap[index];
    while (temp -> next != NULL){
      temp = temp -> next;
    }
    temp -> next = newNode;
  }
}

int hashTable::get (string key){
  int index = Hash(key);
  Node* temp = dataMap[index];
  while (temp != NULL){
    if (temp -> key == key) return temp -> value;
    temp = temp -> next;
  }
  return 0;
}
