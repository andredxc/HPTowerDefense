#include <iostream>

int function(int num1, int num2){

	return num1 + num2;
}


int main(){

	int (*func)(int par1, int par2);
	
	func = function;
	
	std::cout << func(1, 2) << std::endl;
	

	return 0;
}
