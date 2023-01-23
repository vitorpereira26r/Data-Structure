#include <iostream>
using namespace std;

int ANY_PRIME = 23;
static const int SIZE = 23;
int hash (string key);

class Node {
  public:
    string key;
    string meaning;
    Node* next;

    Node (string key, string meaning){
      this->key = key;
      this->meaning = meaning;
      next = NULL;
    }
};

class hashTable{
  private:
    Node* dataMap[SIZE];
  public:
    //void printTable();
    void set (string key, string meaning);
    string get (string key);
};

int main (){
  int numberOfWords;
  string word;
  char meaning[255];
  //char space [1];
  hashTable* myHashTable = new hashTable();

  cin >> numberOfWords;

  for (int i = 0; i < numberOfWords; i++){
    cin >> word;
    //cin >> space [0];
    cin.getline(meaning, 255);
    myHashTable -> set(word, meaning);
  }

  string choice;
  do {
    cin >> choice;
    if (choice != "-1"){
      string aux = myHashTable -> get(choice);
      if (aux == "0"){
        cout << "[" << choice << "] => " << "NULL" << endl;
      } else {
        cout << "[" << choice << "] =>" << aux << endl;
      }
    }
  } while (choice != "-1");

  //myHashTable -> printTable();

  return 0;
}

int Hash (string key) {
  int hash = 0;
  hash = key.length() % SIZE;
  return hash;
}
/*
void hashTable::printTable (){
  for (int i = 0; i < SIZE; i++){
    if (dataMap[i]){
      Node* temp = dataMap[i];
      while(temp){
        cout << "    {" << temp -> key << ", " << temp -> meaning << "}";
        temp = temp -> next;
        cout << endl;
      }
    }
  }
}*/

void hashTable::set (string key, string meaning){
  int index = Hash(key);
  Node* newNode = new Node(key, meaning);
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

string hashTable::get (string key){
  int index = Hash(key);
  Node* temp = dataMap[index];
  while (temp != NULL){
    if (temp -> key == key) return temp -> meaning;
    temp = temp -> next;
  }
  return "0";
}
