#include <iostream>
using namespace std;

class Node {
  public:
    int value;
    Node* left;
    Node* right;
    Node (int value){
      this->value = value;
      left = nullptr;
      right = nullptr;
    }
};

class BinarySearchTree {
  public:
    Node* root;
  public:
    BinarySearchTree();
    BinarySearchTree(int value);
    bool insery (int value);
};

BinarySearchTree::BinarySearchTree(){
  root = nullptr;
}

BinarySearchTree::BinarySearchTree(int value){
  Node* newNode = new Node(value);
  root = newNode;
}

bool BinarySearchTree::insery(int value){
  Node* newNode = new Node(value);
  if(root == nullptr){
    root = newNode;
    return true;
  } else {
    Node* temp = root;
    while(true){
      if (newNode->value == temp->value) return false;
      if (newNode->value < temp->value){
        if(temp->left == nullptr){
          temp->left = newNode;
          return true;
        }
        temp = temp -> left;
      } else {
        if (temp->right == nullptr){
          temp->right = newNode;
          return true;
        }
        temp = temp->right;
      }
    }
  }
}

int main () {
  BinarySearchTree* myBST = new BinarySearchTree();

  myBST->insery(47);
  myBST->insery(21);
  myBST->insery(76);
  myBST->insery(18);
  myBST->insery(52);
  myBST->insery(82);

  myBST->insery(27);

  cout << myBST->root->left->right->value << endl;

  return 0;
}