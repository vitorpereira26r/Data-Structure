#include <iostream>
using namespace std;

static const int ARRAY_SIZE = 101;
int Hash (int key);

class HashTable {
  private:
    int* hashArray;
    int size;
    int capacity;
  public:
    HashTable();
    int member (int key);
    void addElement (int key);
    void removeElement (int key);
    int hashTableSize ();
    void printHashTable ();
};

HashTable::HashTable(){
  hashArray = new int[ARRAY_SIZE];
  capacity = ARRAY_SIZE;
  size = 0;
  for (int i = 0; i < capacity; i++){
    hashArray[i] = -1;
  }
}

void HashTable::addElement (int key){
  int position = Hash(key);
  if (member(key) == -1){
    while(hashArray[position] != -1){
      position = (position + 1) % capacity;
    }
    size++;
    hashArray[position] = key;
  }
}

int HashTable::member (int key){
  int position = Hash(key);
  int finalPosition = position;
  do {
    int data = hashArray[position];
    if (data == -1){
      return -1;
    }
    if (data == key){
      return 1;
    }
    
  } while (position != finalPosition);
  return -1;
}

void HashTable::removeElement (int key){
  if (size > 0){
    int position = Hash(key);
    if (member(key) == 1){
      hashArray[position] = -1;
      size--;
    }
  }
}  

int HashTable::hashTableSize (){
  return size;
}

void HashTable::printHashTable (){
  if (size > 0){
    for (int i = 0; i < capacity; i++){
      if (hashArray[i] != -1){
        cout << hashArray[i] << " ";
      }
    }
    cout << endl;
  }
}

int main () {
  int aux;
  HashTable myHash;

  for (int i = 0; i < 10; i++){
    cin >> aux;
    myHash.addElement(aux);
  }

  for (int i = 0; i < 3; i++){
    cin >> aux;
    myHash.removeElement(aux);
  }

  int pert1, pert2;
  cin >> pert1 >> pert2;

  cout << myHash.member(pert1) << endl << myHash.member(pert2) << endl;

  myHash.printHashTable();

  for (int i = 0; i < 3; i++){
    cin >> aux;
    myHash.addElement(aux);
  }

  myHash.printHashTable();

  return 0;
}

int Hash (int key){
  return key % 101;
}