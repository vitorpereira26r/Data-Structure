/*
    manipulaArquivo.cpp - aplicação para manipulação de arquivo binário

    GCC216 - Estrutura de Dados, 2022

    Desenvolvido por: Grupo 26
    Patrícia Souza Couto
    Vitor Moreira dos Santos
    Vitor Pereira Resende
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class dadoAtleta{
    public:
        dadoAtleta();
        dadoAtleta(unsigned& i, string& n, string& c, string& s, string& e, string& noc);
        void exibe();
        void trocaValores(dadoAtleta& a2, dadoAtleta& aux); // manter privado depois
        void transforma(dadoAtleta& a); // privar tbm
    private:
        unsigned id;
        char name[50];
        char city[15];
        char sport[50];
        char event[50];
        char mNoc[4]; // 3 caracteres (o 4o é para o caractere nulo \0)
};

dadoAtleta::dadoAtleta(){
    id = 0;
    strcpy(name, "--");
    strcpy(city, "--");
    strcpy(sport, "--");
    strcpy(event, "--");
    strcpy(mNoc, "--");
}

dadoAtleta::dadoAtleta(unsigned& i, string& n, string& c, string& s, string& e, string& noc){
    // inicializa um novo elemento com os dados inseridos pelo usuário
    // e pelo id caluclado pelo programa, visto que é sequencial, começando em 0
    id = i;
    strcpy(name, n.c_str());
    strcpy(city, c.c_str());
    strcpy(sport, s.c_str());
    strcpy(event, e.c_str());
    strcpy(mNoc, noc.c_str());
}

void dadoAtleta::exibe(){
    // imprime os atributos de um registro
    printf("Id: %d\nNome: %s\nCidade: %s\nEsporte: %s\nEvento: %s\nComitê Olímpico: %s\n", id, name, city, sport, event, mNoc);
}

void dadoAtleta::trocaValores(dadoAtleta& a2, dadoAtleta& aux){
    // troca os atributos entre dois registros, exceto o atributo id, que é sequencial e indica a posição
    // copia os dados de atleta1 para auxiliar
    // em seguida, copia de atleta2 para atleta1
    // e de auxiliar para atleta2
    strcpy(aux.name, name);
    strcpy(aux.city, city);
    strcpy(aux.sport, sport);
    strcpy(aux.event, event);
    strcpy(aux.mNoc, mNoc);

    strcpy(name, a2.name);
    strcpy(city, a2.city);
    strcpy(sport, a2.sport);
    strcpy(event, a2.event);
    strcpy(mNoc, a2.mNoc);

    strcpy(a2.name, aux.name);
    strcpy(a2.city, aux.city);
    strcpy(a2.sport,aux.sport);
    strcpy(a2.event,aux.event);
    strcpy(a2.mNoc, aux.mNoc);
}

void dadoAtleta::transforma(dadoAtleta& a){
    // copia os atributos de um registro para o proximo
    // o próximo registro, que recebe a cópia, tem id = id anterior + 1
    // para manter a sequência ordenada de id no arquivo
    id = a.id + 1;
    strcpy(name, a.name);
    strcpy(city, a.city);
    strcpy(sport, a.sport);
    strcpy(event, a.event);
    strcpy(mNoc, a.mNoc);
}

int main(){
    // ------- MENU -------- //
    cout<<"Selecione a função que deseja executar:\n\n";
    cout<<"1 - Adicionar um novo elemento ao final do arquivo\n";
    cout<<"2 - Adicionar um novo elemento na posição desejada\n";
    cout<<"3 - Alterar os dados de um registro\n";
    cout<<"4 - Trocar a posição de dois registros\n";
    cout<<"5 - Visualizar os registros entre duas posições\n";
    cout<<"6 - Visualizar todos os registros\n";
    cout<<"7 - Sair da aplicação\n\n";

    char escolha, continua;
    cin >> escolha;

    unsigned id;
    string name, city, sport, event, noc;
    unsigned numRegistros, posRelativa, posAbsoluta1, posAbsoluta2, contador=0;
    dadoAtleta* novoAtleta;
    dadoAtleta atleta1, atleta2, auxiliar;

    fstream BASEDADOS("teste.dat");

    do {
        switch (escolha) { 
        case '1': // adiciona um novo elemento ao final do arquivo
            cout<<"Insira os dados do novo registro: \n";
            cout<<"Nome: "; cin>>name;
            cout<<"Cidade: "; cin>>city;
            cout<<"Esporte: "; cin>>sport;
            cout<<"Evento: "; cin>>event;
            cout<<"Comitê Olímpico: "; cin>>noc;
            cout<<endl;

            // cria novo registro
            // numRegistros é a quantidade de atletas registrados
            // id é sequencial e começa em zero, então numRegistros atual = id+1
            // um novo registro será adicionado na posição id+1
            // então novo registro receberá id = numRegistros atual 
            BASEDADOS.seekp(0, BASEDADOS.end);
            numRegistros = BASEDADOS.tellp() / sizeof(dadoAtleta);
            novoAtleta = new dadoAtleta(numRegistros, name, city, sport, event, noc);

            // grava novo registro no arquivo
            // e desaloca a memória ocupada pelo objeto novoAtleta
            BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));
            delete novoAtleta;

            break;

        case '2': // adiciona um novo elemento na posição relativa desejada
            // estabele a posição onde será adicionado um novo registro (posAbsoluta1)
            // estabele posição do último registro, de onde vai começar a alteração (posAbsoluta2)
            // cria um registro "vazio" no final do arquivo
            cout<<"Insira a posição onde deseja inserir o novo registro: "; cin>>posRelativa;
            posAbsoluta1 = (posRelativa-1) * sizeof(dadoAtleta);

            BASEDADOS.seekp(0, BASEDADOS.end);
            posAbsoluta2 = BASEDADOS.tellp();
            posAbsoluta2 -= sizeof(dadoAtleta);

            novoAtleta = new dadoAtleta;
            BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));
            delete novoAtleta;

            // copia os atributos de posAboluta2 para (posAbsoluta2 + 1 registro)
            // incrementando id para manter a sequência ordenada de id
            // enquanto a posição onde será inserido o novo registro for menor ou igual do que posição onde ocorre a cópia
            // continua copiando os dados de um registro para o próximo e incrementando id
            
            while ((posAbsoluta2 > 0) and (posAbsoluta1 <= posAbsoluta2)){
                BASEDADOS.seekg(posAbsoluta2); // posiciona cabeça de leitura
                BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));

                posAbsoluta2 += sizeof(dadoAtleta); 
                BASEDADOS.seekp(posAbsoluta2); // posiciona cabeça de escrita
                atleta2.transforma(atleta1); // copia os dados de atleta1 para a proxima posição (atleta2)
                BASEDADOS.write((char*) &atleta2, sizeof(dadoAtleta));

                // altera o valor de posAbsoluta2 para posicionar a cabeça de leitura novamente
                // função sizeof() não pode conter valores negativos, então
                // se posAbsoluta2 for do tamanho de apenas um registro (id = 0)
                // finaliza a decrementação do tamanho de 2 registros
                // e atribui valor zero, primeira posição do arquivo
                if (posAbsoluta2 != sizeof(dadoAtleta))    
                    posAbsoluta2 -= (2*sizeof(dadoAtleta));
                else
                    posAbsoluta2 = 0;
            }

            // recebe os novos dados e atribui a um registro naquela posição
            // sem alterar o id (posRelativa - 1)
            cout<<"Insira os dados do novo registro: \n";
            id = posRelativa - 1;
            cout<<"NOVO ID: "<<id<<endl;
            cout<<"Nome: "; cin>>name;
            cout<<"Cidade: "; cin>>city;
            cout<<"Esporte: "; cin>>sport;
            cout<<"Evento: "; cin>>event;
            cout<<"Comitê Olímpico: "; cin>>noc;
            cout<<endl;

            novoAtleta = new dadoAtleta(id, name, city, sport, event, noc);  
            
            // se posAbsoluta2 == 0, a posição da cabeça de escrita já está certa
            // se não, é preciso mover a posição um registro a frente
            if (posAbsoluta2 != 0){
                posAbsoluta2 += (1*sizeof(dadoAtleta));
            }
            
            BASEDADOS.seekp(posAbsoluta2);
            BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));

            break;

        case '3': // altera os dados do registro de uma posição
            // posiciona o arquivo na posição desejada (id)
            // faz a leitura e impressão dos dados atuais do registro 
            // (para o usuário conferir os dados que serão alterados)
            // e altera esses dados com os novos dados inseridos
            cout<<"Insira a chave ID do registro que deseja alterar: ";
            
            BASEDADOS.seekg(0,BASEDADOS.end);
            numRegistros = BASEDADOS.tellg() / sizeof(dadoAtleta);
            id = numRegistros; // inicializado com esse valor apenas para entrar dentro do laço de repetição
            
            // usuário deve inserir um id válido (ou seja, id < número de registros)
            // laço se repete até que ele insira um valor válido
            while (id >= numRegistros){   
                cin>>id; 

                // condição satisfeita apenas se o id for válido
                if (id < numRegistros){
                    cout<<endl;
                    novoAtleta = new dadoAtleta;
                    posAbsoluta1 = sizeof(dadoAtleta) * id;
                    BASEDADOS.seekg(posAbsoluta1);
                    BASEDADOS.read((char*) novoAtleta, sizeof(dadoAtleta));
                    novoAtleta->exibe(); // imprime os dados do registro
                    delete novoAtleta;

                    cout<<"\nTem certeza de que deseja alterar os dados desse registro? [S/n] "; cin>>continua;

                    if (continua == 'S'){
                        cout<<"Insira os novos dados do registro:\n";
                        cout<<"Nome: "; cin>>name;
                        cout<<"Cidade: "; cin>>city;
                        cout<<"Esporte: "; cin>>sport;
                        cout<<"Evento: "; cin>>event;
                        cout<<"Comitê Olímpico: "; cin>>noc;
                        cout<<endl;

                        novoAtleta = new dadoAtleta(id, name, city, sport, event, noc);
                        BASEDADOS.seekp(posAbsoluta1);
                        BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));

                        delete novoAtleta;
                    }
                }
                else {
                    cout<<"Insira uma chave válida: ";
                }
            }
            
            break;

        case '4': // troca dois registros de posição
            // posRelativa recebe as posições desejadas
            // imprime os dados do registro de cada posição (para verificação do usuário)
            // troca os valores entre os dois registros, com exceção de id
            // e grava as alterações no arquivo
            cout<<"Insira as duas posições que deseja trocar:\n"; 
            cout<<"Primeira posição: "; cin>>posRelativa;

            posAbsoluta1 = (posRelativa-1)*sizeof(dadoAtleta);
            BASEDADOS.seekg(posAbsoluta1);
            BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));
            atleta1.exibe();
            cout<<endl;

            cout<<"Segunda posição: "; cin>>posRelativa;
            posAbsoluta2 = (posRelativa-1)*sizeof(dadoAtleta);
            BASEDADOS.seekg(posAbsoluta2);
            BASEDADOS.read((char*) &atleta2, sizeof(dadoAtleta));
            atleta2.exibe();
            cout<<endl;

            // troca os valores entre os registros atleta1 e atelta2
            atleta1.trocaValores(atleta2, auxiliar);

            BASEDADOS.seekp(posAbsoluta1);
            BASEDADOS.write((char*) &atleta1, sizeof(dadoAtleta));
            BASEDADOS.seekp(posAbsoluta2);
            BASEDADOS.write((char*) &atleta2, sizeof(dadoAtleta));

            cout<<"Troca realizada!\n\n";

            break;

        case '5': // visualiza os registros entre duas posições
            // calcula o número de registros entre as duas posições
            // inicia a impressão dos dados a partir da primeira posição
            // até que o número de registros calculado seja impresso
            cout<<"Insira as duas posições desejadas: \n"; 
            cout<<"Primeira posição: "; cin>>posRelativa;
            posAbsoluta1 = (posRelativa-1)*sizeof(dadoAtleta);

            cout<<"Segunda posição: "; cin>>posRelativa;
            cout<<endl;
            posAbsoluta2 = (posRelativa-1)*sizeof(dadoAtleta);

            numRegistros = (posAbsoluta2 - posAbsoluta1) / sizeof(dadoAtleta);
            BASEDADOS.seekg(posAbsoluta1);
            contador = 0;

            while (contador <= numRegistros){
                BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));
                atleta1.exibe();
                cout<<endl;
                contador++;
            }

            break;

        case '6': // imprime todos os registros
            // calcula o total de registros no arquivo
            // inicia a impressão dos dados a partir da primeira posição do arquivo
            // até que o número de registros totais seja impresso
            BASEDADOS.seekg(0, BASEDADOS.end);
            numRegistros = BASEDADOS.tellg() / sizeof(dadoAtleta);
            BASEDADOS.seekg(0, BASEDADOS.beg);

            contador = 0;
            while (contador < numRegistros){
                BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));
                atleta1.exibe();
                cout<<endl;
                contador++;
            }

            break;

        case '7': // encerra a aplicação 
            break;
        
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
    cout<<"Selecione a função que deseja executar: "; cin>>escolha;

    } while (escolha != '7');

    return 0;
}