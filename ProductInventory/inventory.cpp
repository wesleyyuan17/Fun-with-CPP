#include<iostream>
#include<string>
#include<map>

#include "inventory.h"
#include "product.h"

using namespace std;

Inventory::Inventory() {
	Inventory::Products = map<string, Product*>(); // initialize map object
}

void Inventory::listProducts() {
	map<string, Product*>::iterator it; // create iterator object

	for (it = Products.begin(); it != Products.end(); it++) {
		cout << it->second->getID() << endl;
	}
	cout << endl;
}

double Inventory::inventoryValue() {
	double totalVal = 0;

	map<string, Product*>::iterator it; // create iterator object

	for (it = Products.begin(); it != Products.end(); it++) {
		double prodP = it->second->getPrice();
		int prodQ = it->second->getQuantity();
		totalVal += prodP * prodQ;
	}

	return totalVal;
}

void Inventory::addProduct(double price, string id, int quantity) {
	map<string, Product*>::iterator it = Products.find(id);

	if (it == Products.end()) {
		Products.insert(make_pair(id, new Product(price, id, quantity)));
	}
	else {
		int prevQ = it->second->getQuantity();
		it->second->setQuantity(prevQ + quantity);
	}
}

void Inventory::removeProduct(string id, int quantity) {
	map<string, Product*>::iterator it = Products.find(id);

	if (it != Products.end()) {
		int prevQ = it->second->getQuantity();
		if (quantity > prevQ) {
			cout << "not enough " << id << " in inventory" << endl;
		}
		else if (quantity == prevQ) {
			Products.erase(it);
		}
		else {
			it->second->setQuantity(prevQ - quantity);
		}
	}
}