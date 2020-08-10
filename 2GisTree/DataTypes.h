#pragma once


#include <string>
#include <vector>
#include "CsDeclares.h"


using namespace std;

class Element {
public:
	virtual void accept(Visitor& iVisitor) = 0;
	virtual string getStr() = 0;
	virtual ~Element();
};




class StrElement : public Element {
public:
	string getStr();
	string getValue();
	void accept(Visitor& iVisitor);
	void setValue(string s);
	~StrElement();
	std::string s;
private:

};

class IntElement : public Element {
public:
	string getStr();
	int getValue();
	void accept(Visitor& iVisitor);
	void setValue(int s);
	~IntElement();
	int i;
private:
	
};

class DoubleElement : public Element {
public:
	string getStr();
	double getValue();
	void accept(Visitor& iVisitor);
	void setValue(double s);
	~DoubleElement();
	double d;
private:

};


class Tree {
public:
	Element* Elem;
	vector <Tree*> Sons;
	Tree(Element* Elem, vector<Tree*> Directions);
	Tree();
	~Tree();	
private:
	size_t TreeDeep = 0;
};



