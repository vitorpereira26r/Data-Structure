#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh(Dado d);
        ~Noh();
        unsigned NroDeFolhas() const;
    private:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
};

Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

Noh::~Noh() {
  if(dir != NULL){
    delete dir;
  }
  if(esq != NULL){
    delete esq;
  }
}

unsigned Noh::NroDeFolhas() const {
    // implemente
}

class ABB {
    public:
        ABB();
        ~ABB();
        // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
        // Pode ser Ãºtil para depurar o programa.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na Ã¡rvore.
        void Inserir(Dado d);
        // Retorna o nro de folhas na Ã¡rvore.
        unsigned NroDeFolhas() const;
        void deletaArvore (Noh *no);
    private:
        Noh* raiz;
};

void ABB::deletaArvore(Noh *no){
  if(! no) return;
  deletaArvore(no->esq);
  deletaArvore(no->dir);
  delete no;
}

ABB::~ABB(){
  deletaArvore(raiz);
}

ABB::ABB(){
    raiz = NULL;
}

void ABB::Inserir(Dado d) {
    Noh* atual = raiz;
    Noh* pai = NULL;
    
    while(atual){
      pai = atual;
      if (d < atual->valor){
        atual = atual->esq;
      } else {
        atual = atual->dir;
      }
    }

    Noh* novo = new Noh(d);
    novo->pai = pai;
    if(! pai){
      raiz = novo;
    } else if(d < pai->valor){
      pai->esq = novo;
    } else {
      pai->dir = novo;
    }
}

unsigned ABB::NroDeFolhas() const {
  unsigned cont = 0;
  queue<Noh*>q;
  Noh* aux = raiz;

  if(raiz == NULL)return 0;
  if(raiz->esq == NULL && raiz->dir == NULL)return 1;
  q.push(raiz);
  while(!q.empty()){
    aux = q.front();
    q.pop();
    if(!aux->esq && !aux->dir) cont++;
    if(aux->esq) q.push(aux->esq);
    if(aux->dir) q.push(aux->dir);
  }
  return cont;
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh aux = Dado();
    Noh* fimDeNivel = &aux; // marcador especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (! filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (! filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esq);
                filhos.push(ptNoh->dir);
            }
            saida << ']';
        }
    }
}

int main() {
    unsigned qtde;
    cin >> qtde;
    ABB arvore;
    Dado valor;
    for (unsigned i = 0; i < qtde; ++i) {
        cin >> valor;
        arvore.Inserir(valor);
    }
    cout << arvore.NroDeFolhas() << endl;
    //arvore.EscreverNivelANivel();
    return 0;
}