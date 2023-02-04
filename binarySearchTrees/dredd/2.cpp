#include <iostream>
#include <queue>

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh (Dado d);
        ~Noh();
        // Verifica se um nÃ³ Ã© filho da direita do pai.
        bool FilhoDaDireita();
        // Retorna a menor chave de uma sub-Ã¡rvore.
        Dado MenorRecursivo();
        // Verifica se existe sucessor e retorna o valor sucessor, se existir.
        bool Sucessor(Dado* ptResultado);
    private:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
};

class ABB {
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        // Retorna um ponteiro para o nÃ³ de uma chave, ou NULL.
        Noh* Busca(Dado d);
        // Escreve uma Ã¡rvore nÃ­vel a nÃ­vel.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na Ã¡rvore.
        void Inserir(Dado d);
        // Verifica se um dado tem sucessor e o retorna.
        bool Sucessor(Dado d, Dado* ptResultado);
    private:
        Noh* raiz;
};

using namespace std;
// === Classe Noh ==============================================================
Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

Noh::~Noh() {
    if(esq != NULL){
        delete esq;
    }
    if(dir != NULL){
        delete dir;
    }
}

bool Noh::FilhoDaDireita() {
    if (dir == NULL){
        return false;
    } else {
        return true;
    }
}

Dado Noh::MenorRecursivo() {
    if(esq == NULL){
        return valor;
    } else {
        return esq->MenorRecursivo();
    }
}

bool Noh::Sucessor(Dado* ptResultado) {
    if(dir != NULL){
        Noh* aux = dir;
        while(aux->esq != NULL){
            aux = aux->esq;
        }
        *ptResultado = aux->valor;
        return true;
    }
    Noh* aux = this;
    Noh* paiAux = aux->pai;
    while(paiAux != NULL && aux == paiAux->dir){
        aux = paiAux;
        paiAux = aux->pai;
    }
    if(paiAux == NULL){
        return false;
    }
    *ptResultado = paiAux->valor;
    return true;
}

// === Classe ABB ==============================================================
ABB::~ABB(){
    delete raiz;
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

bool ABB::Sucessor(Dado d, Dado* ptResultado) {
    Noh* aux = Busca(d);
    bool sent = aux->Sucessor(ptResultado);
    if(sent){
        return true;
    } else {
        return false;
    }
}

Noh* ABB::Busca(Dado d) {
    Noh* atual = raiz;

    while(atual != NULL){
        if(atual->valor == d){
            return atual;
        } else if(atual->valor < d){
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return NULL;
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh noh = Dado();
    Noh* fimDeNivel = &noh; // noh especial para fim de nivel
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

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.Inserir(chave);
                break;
            case 'e': // Escrever
                arvore.EscreverNivelANivel(cout);
                break;
            case 's': { // Sucessor
                cin >> chave;
                Dado sucessor;
                while (arvore.Sucessor(chave, &sucessor)) {
                    cout << sucessor << ' ';
                    chave = sucessor;
                }
                cout << endl;
                break;
            }
        }
    } while (operacao != 'f');
    return 0;
}