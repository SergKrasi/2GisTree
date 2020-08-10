#include "stdafx.h"
#include "Handlers.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

void TreeSerializer::VisitStr(StrElement& SElem) {
	fout << "Str" << endl << SElem.getValue() << endl;
}

void TreeSerializer::VisitInt(IntElement& IElem) {
	fout << "Int" << endl << IElem.getValue() << endl;
}

void TreeSerializer::VisitDouble(DoubleElement& DElem) {
	fout << "Double" << endl << DElem.getValue() << endl;
}

void TreeSerializer::TreeSerialize(Tree* tree) {
	tree->Elem->accept(*this);
	fout << "Sons" << endl << tree->Sons.size() << endl;
	size_t Temp = tree->Sons.size();
	if (!Temp) {
		return;
	}
	else {
		for (size_t i = 0; i < tree->Sons.size(); i++) {
			TreeSerialize(tree->Sons[i]);
		}
	}
}

TreeSerializer::~TreeSerializer() {
	fout.close();
}

void TreeDeserializer::VisitStr(StrElement& SElem) {
	string s;
	fin >> s;
	SElem.setValue(s);
}

void TreeDeserializer::VisitInt(IntElement& IElem) {
	string s;
	fin >> s;
	IElem.setValue(atoi(s.c_str()));
}

void TreeDeserializer::VisitDouble(DoubleElement& DElem) {
	string s;
	fin >> s;
	DElem.setValue(atof(s.c_str()));
}

void TreeDeserializer::TreeDeserialize(Tree* tree) {
	string s;
	fin >> s;
	switch (s[0]) {
	case 'I':
		tree->Elem = new IntElement;
		break;
	case 'D':
		tree->Elem = new DoubleElement;
		break;
	case 'S':
		tree->Elem = new StrElement;
		break;
	}
	tree->Elem->accept(*this);
	fin >> s;
	fin >> s;
	if (s == "0") {
		return;
	}
	else {
		size_t vector_size = atoi(s.c_str());
		tree->Sons.reserve(vector_size);
		//tree->Sons.reserve(d);//(atoi(s.c_str()));
		for (unsigned int i = 0; i < vector_size; i++) {
			Tree* Temp = new Tree;
			tree->Sons.push_back(Temp);
			TreeDeserialize(tree->Sons[i]);
		}
	}
}

TreeDeserializer::~TreeDeserializer(){
	fin.close();
}

void TreePrinter::VisitStr(StrElement& SElem) {
	this->s = "\"" + SElem.s + "\"";
}

void TreePrinter::VisitInt(IntElement& IElem) {
	this->s = to_string(IElem.i);
}

void TreePrinter::VisitDouble(DoubleElement& DElem) {
	this->s = to_string(DElem.d);
}

size_t TreePrinter::HowDeepTheTreeIs(Tree* tree, size_t level) {
	if (tree->Sons.size()) {
		level++;
		if (level > TreeDepth) {
			TreeDepth = level;
		}
		for (size_t i = 0; i < tree->Sons.size(); i++) {
			size_t Temp = HowDeepTheTreeIs(tree->Sons[i], level);
			//size_t Temp = tree->Sons[i]->Deep(level);
			TreeDepth = (TreeDepth < Temp ? Temp : TreeDepth);
		}
	}
	return TreeDepth;
}

size_t TreePrinter::HowWideTheTreeIs(Tree* tree, size_t TreeWidth) {
	if (tree->Sons.size()) {
		for (size_t i = 0; i < tree->Sons.size(); i++) {
			TreeWidth = HowWideTheTreeIs(tree->Sons[i], TreeWidth);
		}
	}
	else if (tree->Sons.size() == 0) {
		TreeWidth++;
	}
	return TreeWidth;
}

size_t TreePrinter::FillPrintMatrix(Tree* tree, size_t& Max, size_t level, size_t width) {
	tree->Elem->accept(*this);
	MaxElement = MaxElement < this->s.size() ? this->s.size() : Max;
	PrintMatrix[width * TreeDepth + level] = this->s;
	if (tree->Sons.size() == 0) {
		width++;
	}
	level++;
	for (size_t i = 0; i < tree->Sons.size(); i++) {
		width = FillPrintMatrix(tree->Sons[i], MaxElement, level, width);
	}	
	return width;
}

void TreePrinter::Print() {
	TreeDepth = HowDeepTheTreeIs(this->tree);
	TreeWidth = HowWideTheTreeIs(this->tree);
	PrintMatrix.resize(TreeDepth * TreeWidth);
	for (size_t i = 0; i < TreeWidth; i++) {
		for (size_t j = 0; j < TreeDepth; j++) {
			size_t Temp = i * TreeDepth + j;
			PrintMatrix[i * TreeDepth + j] = " ";
		}
	} 
	FillPrintMatrix(tree, MaxElement);
	for (size_t i = 0; i < TreeWidth; i++) {
		for (size_t j = 0; j < TreeDepth; j++) {
			cout << setw(MaxElement + 2) << PrintMatrix[i * TreeDepth + j];
		}
		cout << endl << endl;
	}
}

TreePrinter::~TreePrinter() {	
	PrintMatrix.clear();
}
