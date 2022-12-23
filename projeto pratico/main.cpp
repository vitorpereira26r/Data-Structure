#include <iostream>
#include <string>
#include <fstream>
//#include <stdio.h>

using namespace std;

//--------------------

class dadoAtleta
{
public:
  unsigned id;
  char name[50];
  char city[30];
  char sport[50];
  char time[50];
  char event[50];
  char noc[3];
  void guardaTxt();
};

void dadoAtleta::guardaTxt()
{
}

void addDadosPosicao(ifstream leitura)
{
}

int main()
{
  //dadoAtleta dado;
  int cont = 0;
  string header, aux;

  ifstream leitura("data_athlete_event.csv");
  ofstream binario("result.dat", ios::binary);
  fstream teste("test.txt");

  while (leitura)
  {
    if (cont == 0)
    {
      cont++;
      getline(leitura, header, '\n');
    }
    else
    {
      getline(leitura, aux, ',');
      teste << aux << endl;
    }
  }

  cout << "DONE!" << endl;

  leitura.close();
  binario.close();
  teste.close();
  return 0;
}
