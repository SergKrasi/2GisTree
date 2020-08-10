#include "stdafx.h"
#include "Handlers.h"

using namespace std;
char* PossibleParameters = "i:o:";

int main(int argc, char** argv) {
	Tree* tree = new Tree;
	// -i input -o output
	char* Temp = PossibleParameters;
	for (int i = 1; i < argc; i++) {		
		while (*Temp) {
			if (argv[i][1] == *Temp) {
				switch (argv[i][1]) {
				case 'i':
					if (*(++Temp) == ':') {
						string input = argv[i + 1];
						Temp++;
						i++;
						TreeDeserializer TDserializer(tree, input);
						TDserializer.TreeDeserialize(tree);
						TreePrinter TPrint(tree);
						TPrint.Print();
					}
					else {
						
					}
					break;
				case 'o':
					if (*(++Temp) == ':') {
						string output = argv[i + 1];
						TreeSerializer TSerializer(tree, output);
						TSerializer.TreeSerialize(tree);
						i++;
					}
					else {

					}
					break;
				}
				break;
			}
		}
	}
	delete tree;
	system("pause");
	return 0;
}

