/*
The worst-case Big-O of the insert() algorithm for the AVL tree is O(log n) because it has to traverse the tree from the root to the leaf node, and the height of the tree is limited by log n.

The worst-case Big-O of the printInOrder() algorithm for the AVL tree is also O(n) because it has to visit every node in the tree exactly once and print its data.

The worst-case Big-O of the findMax() algorithm for the AVL tree is O(log n) because it has to traverse the tree from the root to the rightmost node, and the height of the tree is limited by log n.
*/

#include <algorithm>
#include "AVLTree.h"

using namespace std;

void parseCSV(string filename, AVLTree<CancerData>& tree) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string country;
        double rate;
        getline(ss, country, ',');
        ss >> rate;
        CancerData data(country, rate);
        tree.insert(data);
    }
}

void printRank(const string& label, const int& rank, const CancerData& data) {
    cout << "<label: " << label << ". rank number: " << rank << ". country name: " << data.getCountry() 
         << ". rate: " << data.getRate() << ">" << endl;
}

void printTop50(const string& label, const AVLTree<CancerData>& tree) {
    cout << "Top 50 " << label << " cancer rates:" << endl;
    vector<CancerData> dataVec;
    tree.inOrder(dataVec);
    sort(dataVec.begin(), dataVec.end(), [](const CancerData& a, const CancerData& b) {
        return a.getRate() > b.getRate();
    });
    for (int i = 0; i < 50; i++) {
        printRank(label, i + 1, dataVec[i]);
    }
    cout << endl;
}

void printFirst(const string& label, const AVLTree<CancerData>& tree) {
    cout << "First ranked " << label << " cancer rate:" << endl;
    vector<CancerData> dataVec;
    tree.inOrder(dataVec);
    sort(dataVec.begin(), dataVec.end(), [](const CancerData& a, const CancerData& b) {
        return a.getRate() > b.getRate();
    });
    printRank(label, 1, dataVec[0]);
    cout << endl;
}

void printFiftieth(const string& label, const AVLTree<CancerData>& tree) {
    cout << "Fiftieth ranked " << label << " cancer rate:" << endl;
    vector<CancerData> dataVec;
    tree.inOrder(dataVec);
    sort(dataVec.begin(), dataVec.end(), [](const CancerData& a, const CancerData& b) {
        return a.getRate() > b.getRate();
    });
    printRank(label, 50, dataVec[49]);
    cout << endl;
}

int main() {
    AVLTree<CancerData> allTree;
    parseCSV("allcancerdata2018.csv", allTree);
    printTop50("all", allTree);
    printFirst("all", allTree);
    printFiftieth("all", allTree);

    AVLTree<CancerData> menTree;
    parseCSV("mencancerdata2018.csv", menTree);
    printTop50("men", menTree);
    printFirst("men", menTree);
    printFiftieth("men", menTree);

    AVLTree<CancerData> womenTree;
    parseCSV("womencancerdata2018.csv", womenTree);
    printTop50("women", womenTree);
    printFirst("women", womenTree);
    printFiftieth("women", womenTree);

    return 0;
}