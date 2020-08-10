#pragma once

#include "DataTypes.h"
#include "Patterns.h"
#include <fstream>

class Serializer {
public:

};

class TreeSerializer : public Serializer, public Visitor {
public:
	ofstream fout;
	Tree* tree;
	TreeSerializer(Tree* tree, string filename) : tree(tree), fout(filename) {}
	~TreeSerializer();
	void VisitStr(StrElement& SElem);
	void VisitInt(IntElement& IElem);
	void VisitDouble(DoubleElement& DElem);
	void TreeSerialize(Tree* tree);
};

class Deserializer {
public:

};

class TreeDeserializer : public Deserializer, public Visitor {
public:
	ifstream fin;
	Tree* tree;
	TreeDeserializer(Tree* tree, string filename) : tree(tree), fin(filename) {}
	~TreeDeserializer();
	void VisitStr(StrElement& SElem);
	void VisitInt(IntElement& IElem);
	void VisitDouble(DoubleElement& DElem);
	void TreeDeserialize(Tree* tree);	
private:

};


class Printer {

};

class TreePrinter : public Printer, public Visitor {
public:
	Tree* tree;
	TreePrinter(Tree* tree) : tree(tree) {}
	void Print();
	void VisitStr(StrElement& SElem);
	void VisitInt(IntElement& IElem);
	void VisitDouble(DoubleElement& DElem);
	~TreePrinter();
private:
	size_t FillPrintMatrix(Tree* tree, size_t& Max, size_t level = 0, size_t width = 0);
	size_t HowDeepTheTreeIs(Tree* tree, size_t level = 1);
	size_t HowWideTheTreeIs(Tree* tree, size_t width = 0);
	size_t TreeWidth = 0;
	size_t TreeDepth = 0;
	vector <string> PrintMatrix;
	string s;
	size_t MaxElement = 0;
};
