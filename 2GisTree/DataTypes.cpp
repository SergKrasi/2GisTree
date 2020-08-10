#include "stdafx.h"
#include "DataTypes.h"
#include "Patterns.h"

Element::~Element() {

}

void StrElement::accept(Visitor& iVisitor) {
	iVisitor.VisitStr(*this);
}

void StrElement::setValue(string Source) {
	this->s = Source;
}

string StrElement::getValue() {
	return this->s;
}

string StrElement::getStr() {
	return this->s;
}

StrElement::~StrElement() {

}

void IntElement::accept(Visitor& iVisitor) {
	iVisitor.VisitInt(*this);
}

void IntElement::setValue(int Source) {
	this->i = Source;
}

int IntElement::getValue() {
	return this->i;
}

string IntElement::getStr() {
	return to_string(this->i);
}

IntElement::~IntElement() {

}

void DoubleElement::accept(Visitor& iVisitor) {
	iVisitor.VisitDouble(*this);
}

void DoubleElement::setValue(double Source) {
	this->d = Source;
}

double DoubleElement::getValue() {
	return this->d;
}

string DoubleElement::getStr() {
	return to_string(this->d);
}

DoubleElement::~DoubleElement() {

}

Tree::Tree(Element* Elem, vector<Tree*> Directions) : Elem(Elem), Sons(Directions) {}

Tree::Tree() : Elem(NULL), Sons() {}

Tree::~Tree() {
	delete Elem;
	for (size_t i = 0; i < this->Sons.size(); i++) {
		delete this->Sons[i];
	}
}