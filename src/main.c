#include <stdio.h>
#include <time.h>

#include "interpreter.h"
#include "dataloader.h"
#include "clients.h"
#include "products.h"

int main() {
	FATGLOBAL fat;
	BRANCHSALES branchSales[3];
	CLIENTCAT clientCat;
	PRODUCTCAT productCat;
	int i, running = 3;

	while(running != KILL) {

		if (running != CONT) {
			fat = initFat();
			clientCat = initClientCat();
			productCat = initProductCat();
			for(i=0; i < 3; i++)
				 branchSales[i] = initBranchSales();
	
			if(running == LOAD) loader(branchSales, fat, productCat, clientCat);
		}
		
		running = interpreter(branchSales, fat, productCat, clientCat);

		if (running != CONT) { 
			freeFat(fat);
			for (i=0; i < 3; i++)
				freeBranchSales(branchSales[i]);
			freeProductCat(productCat);
			freeClientCat(clientCat);
		}
	}

	return 0;
}
