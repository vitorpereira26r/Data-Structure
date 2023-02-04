/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2020 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2020:
 * -> tratamento de exceção
 * -> usa dado na forma chave/valor '
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>

using namespace std;
#include <stdexcept>

struct dado {
    unsigned chave;
    string nomeAnimal;
    string especie;
    string raca;
};

ostream& operator<<(ostream& saida, const dado& e) {
    saida << "(" << e.chave << "," << e.nomeAnimal << "," << e.especie << "," << e.raca << ")";
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.chave >> e.nomeAnimal >> e.especie >> e.raca;
    return entrada;
}

typedef unsigned tipoChave; // tipo da chave usada na comparação

class noh {
    friend class avl;
    private:
        dado elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const dado& umDado):
            elemento(umDado),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento();
        void atualizarAltura();
};

int noh::fatorBalanceamento() {
  return (esq->altura - dir->altura);
}

void noh::atualizarAltura(){
  int alturaEsq = (esq == nullptr) ? -1 : esq->altura;
  int alturaDir = (dir == nullptr) ? -1 : dir->altura;
  altura = 1 + max(alturaDir, alturaEsq);
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
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, tipoChave chave);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);
        noh* rotacaoDireita(noh* umNoh);
        noh* arrumaBalanceamento(noh* umNoh);
        // busca, método iterativo
        noh* buscaAux(tipoChave chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        int levantamentoAux(noh* umNoh, string especie, string  raca);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void remove(tipoChave chave);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(tipoChave chave);
        // efetua levantamento de quantos animais de uma espécie e raça
        int levantamento(string especie, string raca);
};

int avl::levantamento(string especie, string raca){
  return levantamentoAux(raiz, especie, raca);
}

int avl::levantamentoAux(noh* umNoh, string especie, string  raca){
  int cont = 1;
  if (umNoh == NULL){
    return 0;
  }

  cont = levantamentoAux(umNoh->esq, especie, raca);
  cont = levantamentoAux(umNoh->dir, especie, raca);

  if(umNoh->elemento.especie == especie && umNoh->elemento.raca == raca){
    cont++;
  }
  return cont;
}

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

void avl::insere(const dado& umDado) {
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const dado& umDado) {
  if(umNoh == NULL){
    return new noh(umDado);
  }
  if(umDado.chave < umNoh->elemento.chave){
    umNoh->esq = insereAux(umNoh->esq, umDado);
  } else if(umDado.chave > umNoh->elemento.chave){
    umNoh->dir = insereAux(umNoh->dir, umDado);
  } else {
    return umNoh;
  }
  umNoh->atualizarAltura();
  return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
  int fator = umNoh->fatorBalanceamento();
  if(fator > 1 && umNoh->elemento.chave < umNoh->esq->elemento.chave){
    return rotacaoDireita(umNoh);
  }
  if(fator < -1 && umNoh->elemento.chave > umNoh->dir->elemento.chave){
    return rotacaoEsquerda(umNoh);
  }
  if(fator > 1 && umNoh->elemento.chave > umNoh->esq->elemento.chave){
    umNoh->esq = rotacaoEsquerda(umNoh->esq);
    return rotacaoDireita(umNoh);
  }
  if(fator < -1 && umNoh->elemento.chave < umNoh->dir->elemento.chave){
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


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
  noh* atual = raiz;
  while (atual != nullptr) {
    if (chave == atual->elemento.chave)
      return atual;
    else if (chave < atual->elemento.chave)
      atual = atual->esq;
    else
      atual = atual->dir;
  }
  return nullptr;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
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
    if (chave < umNoh->elemento.chave) {
      umNoh->esq = removeAux(umNoh->esq, chave);
    } else if (chave > umNoh->elemento.chave) {
      umNoh->dir = removeAux(umNoh->dir, chave);
    } else {
      if (umNoh->esq == nullptr) {
        return umNoh->dir;
      } else if (umNoh->dir == nullptr) {
        return umNoh->esq;
      } else {
        noh *sucessor = encontraMenor(umNoh->dir);
        umNoh->elemento.chave = sucessor->elemento.chave;
        umNoh->dir = removeAux(umNoh->dir, sucessor->elemento.chave);
      }
    }
    return arrumaBalanceamento(umNoh);
}


// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::percorreEmOrdemAux(noh* atual, int nivel) {
  if (atual != nullptr) {
    percorreEmOrdemAux(atual->esq, nivel + 1);
    cout << "Nó: " << atual->elemento.chave << " Nível: " << nivel << endl;
    percorreEmOrdemAux(atual->dir, nivel + 1);
  }
}

ostream& operator<<(ostream& output, avl& arvore) {
    // arvore.percorreEmOrdemAux(arvore.raiz,0);
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
                  << "(" << meuNoh->elemento.chave << "," << meuNoh->elemento.nomeAnimal << ")"
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

        std::cout << "(" << meuNoh->elemento.chave << "," << meuNoh->elemento.nomeAnimal << ")"
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
        std::cout << "(" << this->raiz->elemento.chave << "," << this->raiz->elemento.nomeAnimal << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
  avl arvore;
  tipoChave chave;
  dado umDado;
  string especie;
  string raca;
  int quantidade;

  char operacao;

  do {
    cin >> operacao;
      switch (operacao) {
        case 'i':
          cin >> umDado;
          arvore.insere(umDado);
          break;
        case 'r': // Remover recursivamente
          cin >> chave;
          arvore.remove(chave);
          break;
        case 'b': // Buscar
          cin >> chave; // ler a chave
          umDado = arvore.busca(chave); // escrever os dados do animal
          cout << "Elemento buscado: " << umDado << endl;
          break;
        case 'l': // Levantamento por espécie e raça
          cin >> especie >> raca; // ler os dados para levantamento
          quantidade = arvore.levantamento(especie, raca);
          cout << "Levantamento de animais: " << quantidade << endl;
          break;
        case 'e': // Escrever tudo (em ordem)
          cout << arvore;
          break;
        case 'f': // Finalizar execução
          break;
        default:
          cout << "Comando invalido!\n";
      }
  } while (operacao != 'f');

  return 0;
}
