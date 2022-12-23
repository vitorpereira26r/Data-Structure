#include <iostream>
using namespace std;

int primo (int n){
	int div = 0;
	for(int aux = 1; aux <= n; aux++){
		if (n % aux == 0){
			div++;
		}
	}
	if (div <= 2){
		return true;
	} else {
		return false;
	}
}

int main (){
	int * vet = new int [9];
	bool p = false;
	
	for (int i = 0; i < 9; i++){
		cin >> vet[i];
	}
	for (int i = 0; i < 9; i++){
		p = primo(vet[i]);
		if (p){
			cout << vet[i] << " " << i << endl;
		}
	}
}
// 1 2 3 4 5 6 7 8 9
