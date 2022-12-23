/* Classe pilha dupla, duas pilhas usando um armazenamento 
 * compartilhado em um vetor com 50 posições
 *
 * by Joukim, 2019, Estruturas de Dados
 *
 */

#include <iostream>

using namespace std;

// pilha dupla em vetor de 50 elementos
// não é permitido alterar a estrutura da classe
// inserindo ou retirando métodos
// classe não precisa de destrutor, já que não 
// aloca dados dinamicamente
class pilhaDupla {
private:
    int topo1;
    int topo2;
    int tamanho1;
    int tamanho2;
    int *dados;
public:
    pilhaDupla();
    // escolha é um inteiro para indicar qual pilha sendo usada:
    // 1 -> pilha 1 (início do arranjo)
    // 2 -> pilha 2 (final do arranjo)
    void empilha(int escolha, int valor); // empilha valor na pilha escolhida
    int desempilha(int escolha); // retorna o topo da pilha escolhida
    bool vazia(int escolha); // verifica se pilha escolhida é vazia
    int tamanhoTotal ();
};


pilhaDupla::pilhaDupla() {
	dados = new int[50];
    tamanho1 = 0;
    topo1 = -1;
    tamanho2 = 0;
    topo2 = 50; 
}

void pilhaDupla::empilha(int escolha, int valor) {
	if (escolha == 1){
		topo1++;
		dados[topo1] = valor;
		tamanho1++;
	}else if (escolha == 2){
		topo2--;
		dados[topo2] = valor;
		tamanho2++;
	}
}



int pilhaDupla::desempilha(int escolha) {
	int aux;
	if (escolha == 1) {
		aux = dados[topo1];
		topo1--;
		tamanho1--;
	}
	else if (escolha == 2) {
		aux = dados[topo2];
		topo2++;
		tamanho2--;
	}
	return aux;
}


bool pilhaDupla::vazia(int escolha) {
    if (escolha == 1) 
        return (tamanho1 == 0);
    else if (escolha == 2)
        return (tamanho2 == 0);
    return true;
}

int pilhaDupla::tamanhoTotal () {
	return tamanho1 + tamanho2;
}


int main() {
    pilhaDupla PP;
    char opcao;
    int escolha;
    int valor;
    
    do {
        cin >> opcao;
        switch (opcao) {
        case 'E': 
			if (PP.tamanhoTotal() > 50) {
				cout << "INVALIDO" << endl;
			} else {
				cin >> escolha >> valor;
				PP.empilha(escolha,valor);  
			}
            break;      
        case 'D':
            cin >> escolha;
            if ( PP.vazia(escolha) ) cout << "VAZIA" << endl;
            else cout << PP.desempilha(escolha) << " ";  
            break;      
        }
    } while (opcao != 'T');

    return 0;
}
