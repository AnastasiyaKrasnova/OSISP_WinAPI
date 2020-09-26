#pragma once
#include "Source.h"
class Creator
{
public:
	virtual ~Creator() {};
	virtual Figure* FactoryMethod();
};

class EllipsCreator : public Creator {
	
public:
	Figure* FactoryMethod() override {
		return new Ellips();
	}
};

class PolilineCreator : public Creator {
public:
	Figure* FactoryMethod() override {
		return new Poliline();
	}
};
