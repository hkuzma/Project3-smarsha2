#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "SplayTree.h"
#include <fstream>
#include <Top_Songs.h>
#include <random>
#include <vector>
using namespace std;

int main() {
    // Example of writing out to a file
    int depth = 0;
    int i,j;

    std::vector<Top_Songs> songs;
    std::string fn = "../Top_Songs.csv";
    loadFromFile(fn, songs);

    BinarySearchTree<int> bst1;
    AVLTree<int> avl1;
    SplayTree<int> spt1;

    ofstream outFile;
    outFile.open("../data/NumbersInOrder.txt");

    for(i = 1; i <= 100;i++) {
        bst1.add(i);
        avl1.add(i);
        spt1.add(i);
    }
    //Searching for 0
    bst1.find(0,depth);
    outFile << depth << endl;
    //Searching for 101
    depth = 0;
    bst1.find(101,depth);
    outFile << depth << endl;
    //Searching for 102
    depth = 0;
    bst1.find(102,depth);
    outFile << depth << endl;

    bst1.timber();
    avl1.timber();
    spt1.timber();

    outFile.close();

    outFile.open("../data/RandomOrderNumbers.txt");
    std::vector<int> numbers;
    for(i = 1; i <= 100;i++){
        numbers.push_back(i);
    }

    shuffle(numbers.begin(), numbers.end(), random_device());

    for(i = 0; i <= numbers.size()-1;i++) {
        bst1.add(numbers[i]);
        avl1.add(numbers[i]);
        spt1.add(numbers[i]);
    }

    outFile << "*** Searching for random Numbers in bst1 ***" << endl;

    //Searching for all integers in numbers
    for(i = 0; i<=100;i++) {
        depth = 0;
        bst1.find(i, depth);
        outFile << depth << endl;
    }
    outFile << "*** Searching for random Numbers in avl1 ***" << endl;

    //Searching for all integers in numbers
    for(i = 0; i<=100;i++) {
        depth = 0;
        avl1.find(i, depth);
        outFile << depth << endl;
    }
    outFile << "*** Searching for random Numbers in spt1 ***" << endl;

    //Searching for all integers in numbers
    for(i = 0; i<=100;i++) {
        depth = 0;
        spt1.find(i, depth);
        outFile << depth << endl;
    }

    outFile.close();
    //Making Trees Using Top_Songs
    outFile.open("../data/TopSongsDepths.txt");

    BinarySearchTree<Top_Songs> bstSongs;
    AVLTree<Top_Songs> avlSongs;
    SplayTree<Top_Songs> sptSongs;


    for(i = 0; i < songs.size();i++) {
        bstSongs.add(songs[i]);
        avlSongs.add(songs[i]);
        sptSongs.add(songs[i]);
    }
    outFile << "*** Searching for Songs in bst ***" << endl;
    //Searching for all integers in numbers
    for(i = 0; i<songs.size();i++) {
        depth = 0;
        bstSongs.find(songs[i], depth);
        outFile << depth << endl;
    }
    outFile << "*** Searching for Songs in avl ***" << endl;

    //Searching for all integers in numbers
    for(i = 0; i<songs.size();i++) {
        depth = 0;
        avlSongs.find(songs[i], depth);
        outFile << depth << endl;
    }
    outFile << "*** Searching for Songs in Splay Tree ***" << endl;

    //Searching for all integers in numbers
    for(i = 0; i<songs.size();i++) {
        depth = 0;
        sptSongs.find(songs[i], depth);
        outFile << depth << endl;
    }

    outFile.close();
    //Making Trees Using Top_Songs
    outFile.open("../data/SongsSplayTreeDepth.txt");
    SplayTree<Top_Songs> sptSongs2;

    for(i = 0; i < songs.size();i++) {
        sptSongs2.add(songs[i]);
    }

    for(i = 0; i<songs.size();i++) {

        for(j = 0; j<5;j++) {
            depth = 0;
            sptSongs2.find(songs[i], depth);
            outFile << depth << endl;
        }
    }


    return 0;
}