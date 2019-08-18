CXX = g++
#CXXFLAGS = -Wall -g

ProdInv: ProdInv.o product.o inventory.o
	$(CXX) -o ProdInv ProdInv.o product.o inventory.o

ProdInv.o: ProdInv.cpp product.h inventory.h
	$(CXX) -c ProdInv.cpp

product.o: product.h

inventory.o: product.h inventory.h