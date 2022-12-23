#include <iostream>
#include <string>

using namespace std;

class elemento{
  friend class lista;
  private:
    int chave;
    elemento *proximo;
    elemento *anterior;
  public:
    elemento (int c){
      chave = c;
      proximo = NULL;
      anterior = NULL;
    }
};

class lista{
  private:
    elemento *inicio;
    elemento *fim;
    int tamanho;
  public:
    lista();
    ~lista();        
    void insereInicio(int c);
    void insereFim (int c);
    int removeRepetidos();//retorna a quantidade de elementos restantes na lista
    bool vazia(){
      return (inicio == NULL);
    }
    void imprimeLista();
};
    
lista::lista(){
  inicio = NULL;
  fim = NULL;
  tamanho = 0;
}
        
lista::~lista(){
  elemento* aux = inicio;
  elemento* temp;

  while (aux != NULL){
    temp = aux;
    aux = aux -> proximo;
    delete temp;
  }

  inicio = NULL;
  fim = NULL;
}  

void lista::insereInicio (int c){
  elemento* novo = new elemento(c);

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
        
void lista::insereFim (int c){
  elemento* novo = new elemento(c);

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
        
int lista::removeRepetidos(){
  elemento* aux1 = inicio;
  while(aux1 -> proximo != NULL) {
    elemento* aux2 = aux1 -> proximo;
    while (aux2 -> proximo != NULL){
      if (aux2 -> chave == aux1 -> chave){
        elemento* anterior = aux2 -> anterior;
        elemento* prox = aux2 -> proximo;
        if (anterior != NULL){
          anterior -> proximo = prox;
        } else {
          inicio = aux2 -> proximo;
        }
        if (prox != NULL){
          prox -> anterior = anterior;
        } else {
          fim = aux2 -> anterior; 
        }
        delete aux2;
        aux2 = prox;
        tamanho--;
        //cout << tamanho << endl;
      } else {
        aux2 = aux2 -> proximo;
      }
    }
    aux1 = aux1 -> proximo;
  }
  return tamanho;
}
        
void lista::imprimeLista(){
  if (inicio != NULL){
    elemento *auxiliar = inicio;
    while (auxiliar->proximo != NULL){
      cout<<"("<<auxiliar->chave<<") ";
      auxiliar =  auxiliar->proximo;
    }
    cout<<"("<<auxiliar->chave<<")"<<endl;
  } else {
    cout<<"VAZIA";
  }
}       
    
int main(){
  lista listaD;
    
  int chave;
  string dado;
    
  cin>>chave;
    
  while (chave != -1){
    listaD.insereFim(chave);        
    cin>>chave;  
  }
  cout<<listaD.removeRepetidos()<<endl;
  //listaD.~lista();
  listaD.imprimeLista();
    
    
  return 0;
}