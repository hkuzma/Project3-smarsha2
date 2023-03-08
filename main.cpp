#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "SplayTree.h"
#include <fstream>
using namespace std;

int main() {
    // Example of writing out to a file
    ofstream outFile;
    outFile.open("../data/example-output.csv");
    for (int i = 999; i >= 0; --i) {
        outFile << i << endl;
    }
    outFile.close();

    BinarySearchTree<int> bst1;
    bst1.add(8);
    bst1.timber();

    return 0;
}