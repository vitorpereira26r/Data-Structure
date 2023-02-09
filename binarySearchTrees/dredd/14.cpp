/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2019 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa pokemon na forma id/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>
using namespace std;

typedef unsigned tipoChave;


struct pokemon {
    unsigned id;
    string nome;
    string tipo;
    int nivel;
};

ostream& operator<<(ostream& saida, const pokemon& e) {
    saida << "(" << e.id << "," << e.nome << "," << e.tipo << "," << e.nivel << ")";
    return saida;
}

istream& operator>>(istream& entrada, pokemon& e) {
    entrada >> e.id >> e.nome >> e.tipo >> e.nivel;
    return entrada;
}

class noh {
    friend class avl;
    private:
        pokemon elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const pokemon& umPokemon):
            elemento(umPokemon),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento();
        void atualizarAltura();
        unsigned informarAltura();
};

int noh::fatorBalanceamento() {
  unsigned alturaArvoreEsq, alturaArvoreDir;
  if(esq){
    alturaArvoreEsq = esq->informarAltura();
  } else {
    alturaArvoreEsq = 0;
  }
  if(dir){
    alturaArvoreDir = dir->informarAltura();
  } else {
    alturaArvoreDir = 0;
  }
  return alturaArvoreEsq - alturaArvoreDir;
}

void noh::atualizarAltura(){
  unsigned alturaArvoreEsq, alturaArvoreDir;
  if(esq){
    alturaArvoreEsq = esq->informarAltura();
  } else {
    alturaArvoreEsq = 0;
  }
  if(dir){
    alturaArvoreDir = dir->informarAltura();
  } else {
    alturaArvoreDir = 0;
  }
  altura = 1 + max(alturaArvoreDir, alturaArvoreEsq);
}

unsigned noh::informarAltura(){
  return altura;
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        void percorreEmOrdemAux(noh* atual, int nivel);
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const pokemon& umPokemon);
        noh* removeAux(noh* umNoh, tipoChave id);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(tipoChave id);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        int levantamentoAux(noh* umNoh, string tipo, int nivel);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const pokemon& umPokemon);
        void remove(tipoChave id);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        pokemon busca(tipoChave id);
        // efetua levantamento de quantos pokemons existem de um dado tipo e nível
        int levantamento(string tipo, int nivel);
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
  if(umNoh == NULL){
    return;
  }
  destruirRecursivamente(umNoh->esq);
  destruirRecursivamente(umNoh->dir);
  delete umNoh;
}


void avl::insere(const pokemon& umPokemon) {
    raiz = insereAux(raiz, umPokemon);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const pokemon& umPokemon){
    if(umNoh == NULL){
    return new noh(umPokemon);
  }
  if(umPokemon.id < umNoh->elemento.id){
    umNoh->esq = insereAux(umNoh->esq, umPokemon);
  } else if(umPokemon.id > umNoh->elemento.id){
    umNoh->dir = insereAux(umNoh->dir, umPokemon);
  }
  umNoh->atualizarAltura();
  return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
  if(umNoh == NULL){ return umNoh; }
  int fatorBalanceamento = umNoh->fatorBalanceamento();
  if(fatorBalanceamento >= 1 && fatorBalanceamento <= -1){
    return umNoh;
  }
  if(fatorBalanceamento > 1 && umNoh->esq->fatorBalanceamento() >= 0){
    return rotacaoDireita(umNoh);
  }
  if(fatorBalanceamento > 1 && umNoh->esq->fatorBalanceamento() < 0){
    umNoh->esq = rotacaoEsquerda(umNoh->esq);
    return rotacaoDireita(umNoh);
  }
  if(fatorBalanceamento < -1 && umNoh->dir->fatorBalanceamento() <= 0){
    return rotacaoEsquerda(umNoh);
  }
  if(fatorBalanceamento < -1 && umNoh->dir->fatorBalanceamento() > 0){
    umNoh->dir = rotacaoDireita(umNoh->dir);
    return rotacaoEsquerda(umNoh);
  }
  return umNoh;
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
  noh* d = umNoh->dir;
  umNoh->dir = d->esq;
  d->esq = umNoh;
  umNoh->atualizarAltura();
  d->atualizarAltura();
  return d;
}


// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
  noh* e = umNoh->esq;
  umNoh->esq = e->dir;
  e->dir = umNoh;
  umNoh->atualizarAltura();
  e->atualizarAltura();
  return e;
}

int avl::levantamento(string tipo, int nivel){
  return levantamentoAux(raiz, tipo, nivel);
}

int avl::levantamentoAux(noh* umNoh, string tipo, int nivel){
  int cont=0;
  if (umNoh == NULL){
    return 0;
  }

  cont += levantamentoAux(umNoh->esq, tipo, nivel);
  cont += levantamentoAux(umNoh->dir, tipo, nivel);

  if(umNoh->elemento.tipo == tipo && umNoh->elemento.nivel == nivel){
    cont++;
  }
  //cont++;
  return cont;
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
  noh* atual = raiz;
  while (atual != nullptr) {
    if (chave == atual->elemento.id)
      return atual;
    else if (chave < atual->elemento.id)
      atual = atual->esq;
    else
      atual = atual->dir;
  }
  return nullptr;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
pokemon avl::busca(tipoChave id) {
    noh* resultado = buscaAux(id);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
  noh* atual = raizSub;
  while(atual->esq != nullptr){
    atual = atual->esq;
  }
  return atual;
}

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
  if(raizSub->esq == nullptr){
    return raizSub->dir;
  }
  raizSub->esq = removeMenor(raizSub->esq);
  return arrumaBalanceamento(raizSub);
}

// remoção recursiva
void avl::remove(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* umNoh, tipoChave chave) {
  if (umNoh == nullptr) {
      return nullptr;
    }
    if (chave < umNoh->elemento.id) {
      umNoh->esq = removeAux(umNoh->esq, chave);
    } else if (chave > umNoh->elemento.id) {
      umNoh->dir = removeAux(umNoh->dir, chave);
    } else {
      if (umNoh->esq == nullptr) {
        return umNoh->dir;
      } else if (umNoh->dir == nullptr) {
        return umNoh->esq;
      } else {
        noh *sucessor = encontraMenor(umNoh->dir);
        umNoh->elemento = sucessor->elemento;
        umNoh->dir = removeAux(umNoh->dir, sucessor->elemento.id);
      }
    }
    umNoh->atualizarAltura();
    return arrumaBalanceamento(umNoh);
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::percorreEmOrdemAux(noh* atual, int nivel) {
   if (atual != nullptr) {
    percorreEmOrdemAux(atual->esq, nivel + 1);
    cout << "Nó: " << atual->elemento.id << " Nível: " << nivel << endl;
    percorreEmOrdemAux(atual->dir, nivel + 1);
  }
}

ostream& operator<<(ostream& output, avl& arvore) {
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->esq , meuNoh->dir==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->esq, meuNoh->dir==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.id << "," << this->raiz->elemento.nome << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave id;
    pokemon umPokemon;
    string tipo;
    int nivel;
    int quantidade;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe id, nome, tipo e nível
                    cin >> umPokemon;
                    arvore.insere(umPokemon);
                    break;
                case 'r': // Remover recursivamente
                    cin >> id;
                    arvore.remove(id);
                    break;
                case 'b': // Buscar
                    cin >> id; // ler o id
                    umPokemon = arvore.busca(id); // escrever dados do pokemon
                    cout << "Elemento buscado: " << umPokemon << endl;
                    break;
                case 'l': // Levantamento por tipo e nível
                    cin >> tipo >> nivel;
                    quantidade = arvore.levantamento(tipo, nivel);
                    cout << "Levantamento de pokemons tipo " << tipo
                         << " e nível " << nivel << ": " << quantidade << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
                    break;
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}
