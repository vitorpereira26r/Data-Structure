#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

class Info {
    friend class Noh;
    friend class ABB;
    friend ostream& operator<< (ostream& saida, const Info& info);
    public:
        bool operator == (const Info& i) { return chave == i.chave; }
        bool operator < (const Info& i) { return chave < i.chave; }
    public:
        int chave;
        std::string valor;
};

class Noh {
    friend class ABB;
    public:
      Noh(Info info){
        this->info = info;
        pai = NULL;
        esq = NULL;
        dir = NULL;
      }
      ~Noh(){
        delete esq;
        delete dir;
      }
    private:
      Noh* pai;
      Noh* esq;
      Noh* dir;
      Info info;
};

class ABB {
    public:
      ABB(){ raiz = nullptr; }
      ~ABB() { delete raiz; }
      void inserir(Info info);
      string busca (Info info);
    private:
      Noh* raiz;
};

void ABB::inserir(Info info){
  Noh* atual = raiz;
  Noh* pai = NULL;
    
  while(atual){
    pai = atual;
    if (info.chave < atual->info.chave){
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }
  }

  Noh* novo = new Noh(info);
  novo->pai = pai;
  if(! pai){
    raiz = novo;
  } else if(info.chave < pai->info.chave){
    pai->esq = novo;
  } else {
    pai->dir = novo;
  }
}

string ABB::busca(Info info) {
    Noh* atual = raiz;

    while(atual != NULL){
        if(atual->info.chave == info.chave){
            return atual->info.valor;
        } else if(atual->info.chave < info.chave){
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return "INEXISTENTE";
}

using namespace std;

ostream& operator << (ostream& saida, const Info& info) {
    saida << '(' << info.chave << ',' << info.valor << ')';
    return saida;
}

int main() {
    ABB arvore;
    Info info;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> info.chave >> info.valor;
                arvore.inserir(info);
                break;
            case 'b': // Buscar
                 cin >> info.chave; // ler a chave
                 info.valor = arvore.busca(info);
                 cout << info.valor << endl;
                break;
            case 'e': // Escrever tudo
                break;
            case 'f': // Finalizar execução
                break;
            default:
                cerr << "Comando invalido!\n";
        }
    } while (operacao != 'f');
    return 0;
}
