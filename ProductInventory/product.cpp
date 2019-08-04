#include "product.h"

Product::Product(double price, string id, int quantity) : price(price), id(id), quantity(quantity) {}

double Product::getPrice() {
	return price;
}

string Product::getID() {
	return id;
}

int Product::getQuantity() {
	return quantity;
}

void Product::setQuantity(int newQuantity) {
	quantity = newQuantity;
}