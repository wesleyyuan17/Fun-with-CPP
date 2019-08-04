#pragma once

#include<string>

using namespace std;

class Product {
	private:
		double price;
		string id;
		int quantity;
		
	public:
		Product(double price, string id, int quantity);

		double getPrice();
		string getID();
		int getQuantity();
		void setQuantity(int newQuantity);
};