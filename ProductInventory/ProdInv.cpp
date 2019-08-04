#include<iostream>
#include<stdio.h>

#include "product.h"
#include "inventory.h"

int main() {

	// test product class
	Product testProd = Product(5, "coffee", 2); // new Product(___) returns pointer to new object
	cout << testProd.getPrice() << endl << testProd.getID() << endl << testProd.getQuantity() << endl;

	testProd.setQuantity(20);
	cout << testProd.getQuantity() << endl;

	// test inventory class
	Inventory testInv = Inventory();
	cout << "Add 2 coffees" << endl;
	testInv.addProduct(5.50, "coffee", 2); // sorted alphabetically at insertion
	cout << endl;

	cout << "Add 5 donuts" << endl;
	testInv.addProduct(2.30, "donut", 5);
	cout << endl;

	cout << "Add 5 croissants" << endl;
	testInv.addProduct(3.70, "croissant", 5);
	cout << endl;

	cout << "Add 2 more coffees" << endl;
	testInv.addProduct(5.50, "coffee", 2);
	cout << endl;

	cout << "Remove 3 donuts" << endl;
	testInv.removeProduct("donut", 3);
	cout << endl;

	cout << "Remove 7 croissants" << endl;
	testInv.removeProduct("croissant", 7);
	cout << endl;

	cout << "Remove 4 coffees" << endl;
	testInv.removeProduct("coffee", 4);
	cout << endl;

	cout << "List products left, total value of inventory" << endl;
	testInv.listProducts();
	double totalVal = testInv.inventoryValue();	
	cout << "$" << totalVal << endl;

	// requires stdio.h, printf
	printf("$%.2f \n", totalVal);
}