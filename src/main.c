#include <stdio.h>
#include <time.h>

#include "datacheck.h"
#include "fatglobal.h"
#include "clients.h"
#include "products.h"

#define SALES_PATH "Vendas_1M.txt"
#define CLIENTS_PATH "Clientes.txt"
#define PRODUCTS_PATH "Produtos.txt"

int main() {
	FILE *clients, *products, *sales;
	FATGLOBAL fat;
	CLIENTCAT clientCat;
	PRODUCTCAT productCat;
	int suc, fail;

	double time;
	clock_t end, begin;

	clients = fopen(CLIENTS_PATH, "r");
	products = fopen(PRODUCTS_PATH, "r");
	sales = fopen(SALES_PATH, "r");

	if (!(clients && products && sales)){
		fprintf(stderr,"Ficheiros de entrada não encontrados");
		return -1;
	}	
	clientCat = initClientCat();
	productCat = initProductCat();

	begin = clock();
	clientCat = writeCCat(clients, clientCat, &suc);
	end = clock();
	time = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Clientes analisados: %d (%lfs)\n", suc, time);


	putchar('\n');

	begin = clock();
	productCat = writePCat(products, productCat, &suc);
	end = clock();
	time = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Produtos analisados: %d (%lfs)\n", suc, time);

	putchar('\n');
	
	begin = clock();
	fat = fillFat(productCat);
	end = clock();
	time = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("FillFat (%lfs)\n", time);

	putchar('\n');


	begin = clock();
	checkSales(sales, fat, productCat, clientCat, &suc, &fail);
	end = clock();
	time = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Vendas analisadas: %d (%lfs)\n", suc+fail, time);
	printf("Vendas corretas: %d\n", suc);
	printf("Vendas incorretas: %d\n", fail);

	putchar('\n');


	freeClientCat(clientCat);
	freeProductCat(productCat);

	fclose(clients);
	fclose(products);
	fclose(sales);

	return 0;
}
