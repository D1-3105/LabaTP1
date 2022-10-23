#include "Keeper.h"

int main() {
	Keeper k;
	while (1) {
		try {
			k.Menu();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			system("pause");
		}
		
	}
	
}