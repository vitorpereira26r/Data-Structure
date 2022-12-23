#include <iostream>
using namespace std;

int main (){
	int vetor [8];
	int aux;
	int n;
	
	for (int i = 0; i < 8; i++){
		cin >> n;
		if (i == 0){
			vetor[0] = n;
		}else {
			for (int j = i; j>0; j--){
				if (n < vetor[j-1]){
					aux = vetor[j-1];
					vetor[j-1] = n;
					vetor[j] = aux; 
				}
				else {
					vetor[j] = n;
					break;
				}
			}
		}
		for (int j = 0; j <= i; j++){
			cout << vetor[j] << " ";
		}
		cout << endl;
	}
	
	return 0;
}

//7 3 4 6 2 9 0 1
