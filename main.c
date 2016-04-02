#include <stdio.h>
#include "datacheck.h"

#include "datacheck.h"

#define SALES_PATH "Vendas_1M.txt"
#define CLIENTS_PATH "Clientes.txt"
#define PRODUCTS_PATH "Produtos.txt"

#define CLIENT_NUM 20000
#define PRODUCT_NUM 200000

typedef char bool;

int main() {
	FILE *clients, *products, *sales;
	CATALOG clientCat, productCat;
	int suc, fail;

	clients = fopen(CLIENTS_PATH, "r");
	products = fopen(PRODUCTS_PATH, "r");
	sales = fopen(SALES_PATH, "r");

	clientCat = initCatalog();
	productCat = initCatalog();

	writeCatalog(clients, clientCat, M_CLIENTS, &suc, &fail);
	printf("Clientes analisados: %d\n", suc+fail);
	printf("Clientes corretos: %d\n", suc);
	printf("Clientes incorretos: %d\n", fail);

	putchar('\n');

	writeCatalog(products, productCat, M_PRODUCTS, &suc, &fail);
	printf("Produtos analisados: %d\n", suc+fail);
	printf("Produtos corretos: %d\n", suc);
	printf("Produtos incorretos: %d\n", fail);

	putchar('\n');

	checkSales(sales, productCat, clientCat, &suc, &fail);
	printf("Vendas analisadas: %d\n", suc+fail);
	printf("Vendas corretas: %d\n", suc);
	printf("Vendas incorretas: %d\n", fail);

	putchar('\n');

	testsValidSales();

	freeCatalog(clientCat);
	freeCatalog(productCat);

	fclose(clients);
	fclose(products);
	fclose(sales);

	return 0;
}
