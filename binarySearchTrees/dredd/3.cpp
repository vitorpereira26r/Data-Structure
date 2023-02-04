#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

typedef string Dado;

class Noh {
  friend class ABB;
  private:
    Dado palavra;
    queue<int>posicoes;
    Noh* esq;
    Noh* dir;
    Noh* pai;
  public:
    Noh(Dado d, int posicao) {
      palavra = d;
      posicoes.push(posicao);
      esq = NULL;
      dir = NULL;
      pai = NULL;
    }
    ~Noh(){
      if(esq != NULL){
        delete esq;
      }
      if(dir != NULL){
        delete dir;
      }
    }
    void inserePosicao(int posicao){
      posicoes.push(posicao);
    }
    void imprimePosicoes(){
      int valor;
      queue<int>aux;
      while(!posicoes.empty()){
        valor = posicoes.front();
        posicoes.pop();
        cout << valor << " ";
        aux.push(valor);
      } 
      posicoes.swap(aux);
      cout << endl;
    }
};

class ABB{
  private:
    Noh* raiz;
  public:
    ABB();
    ~ABB();
    void inserir(Dado palavra, int posicao);
    Noh* busca(Dado d);
    void posicoes(Dado palavra);
};

ABB::ABB(){
  raiz = nullptr;
}

ABB::~ABB(){
  delete raiz;
}

void ABB::inserir(Dado palavra, int posicao){
  Noh* aux = busca(palavra);
  if(aux != NULL){
    aux->inserePosicao(posicao);
  } else {
    Noh* atual = raiz;
    Noh* pai = NULL;
        
    while(atual){
      pai = atual;
      if (palavra < atual->palavra){
        atual = atual->esq;
      } else {
        atual = atual->dir;
      }
    }

    Noh* novo = new Noh(palavra, posicao);
    novo->pai = pai;
    if(! pai){
      raiz = novo;
    } else if(palavra < pai->palavra){
      pai->esq = novo;
    } else {
      pai->dir = novo;
    }
  }
}

Noh* ABB::busca(Dado d) {
    Noh* atual = raiz;

    while(atual != NULL){
        if(atual->palavra == d){
            return atual;
        } else if(atual->palavra < d){
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return NULL;
}

void ABB::posicoes(Dado palavra){
  Noh* aux = busca(palavra);
  if(aux != NULL){
    aux->imprimePosicoes();
  } else {
    cout << -1 << endl;
  }
}

int main (){
  ABB arvore;
  ifstream arquivo("entrada.txt");
  string aux;
  int contPosicao = 1;
  
  while(arquivo){
    string palavra;
    arquivo >> palavra;
    arvore.inserir(palavra, contPosicao);
    contPosicao++;
  }
  cin >> aux;
  arvore.posicoes(aux);

  arquivo.close();
}
