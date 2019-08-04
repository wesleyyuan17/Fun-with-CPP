#pragma once

#include "product.h"
#include<string>
#include<map>

using namespace std;

class Inventory {
	private:
		map<string, Product*> Products;

	public:
		Inventory();

		void listProducts();
		double inventoryValue();
		void addProduct(double price, string id, int quantity);
		void removeProduct(string id, int quantity);
};