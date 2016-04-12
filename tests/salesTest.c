#include <stdio.h>

#include "../src/sales.h"
#include "salesTest.h"

#define REVENUE_NUM 5

static int test_revenue();

int test_sales() {
	int res, passed_tests = 0;
	
	res = test_revenue();
	passed_tests += res;
	printf("REVENUE: %d/%d\n", res, REVENUE_NUM);

	return passed_tests;
}

static int test_revenue() {

	int passed_tests = 0;

	REVENUE r = initRevenue();

	if (getBilled(r, 3, 1, MODE_N) == 0 && getQuantity(r, 8, 1, MODE_P) == 0) 
		passed_tests++;
	else
		return passed_tests;

	r = updateRevenue(r, 2, 0, MODE_P, 24.5, 3);
	r = updateRevenue(r, 2, 0, MODE_N, 14.23, 10);
	r = updateRevenue(r, 2, 0, MODE_P, 10, 2);

	if (getBilled(r, 2, 0, MODE_P) == 14.5 && getQuantity(r, 2, 0, MODE_P) == 5) 
		passed_tests++;
	else
		return passed_tests;

	r = addBilled(r, 2, 0, MODE_N, 14.20);
	
	if (getBilled(r, 2, 0, MODE_N) == 28.43 && getQuantity(r, 2, 0, MODE_N) == 10) 
		passed_tests++;
	else
		return passed_tests;

	r = addQuantity(r, 11, 0, MODE_P, 100);
	r = addBilled(r, 0, 0, MODE_N, 30.1242);

	if (getBilled(r, 11, 0, MODE_P) == 0 && getQuantity(r, 11, 0, MODE_P) == 100) 
		passed_tests++;
	else
		return passed_tests;

	if (getBilled(r, 0, 0, MODE_N) == 30.1242 && getQuantity(r, 0, 0, MODE_N) == 0) 
		passed_tests++;
	else
		return passed_tests;


	return passed_tests;
}
