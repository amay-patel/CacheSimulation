#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include <set>

using namespace std;

void readFile(string& directory, vector<string>& addresses) {
    ifstream file(directory);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string currAddress;
        getline(iss, currAddress, ' ');
        getline(iss, currAddress, ' ');
        addresses.push_back(currAddress);
    }
}

string convertToBin(const string& hexAddress) {
    string binAddress;
    for(int i = 2; i < hexAddress.length(); i++) {
        if(hexAddress.at(i) == '0') {
            binAddress += "0000";
        }
        else if(hexAddress.at(i) == '1') {
            binAddress += "0001";
        }
        else if(hexAddress.at(i) == '2') {
            binAddress += "0010";
        }
        else if(hexAddress.at(i) == '3') {
            binAddress += "0011";
        }
        else if(hexAddress.at(i) == '4') {
            binAddress += "0100";
        }
        else if(hexAddress.at(i) == '5') {
            binAddress += "0101";
        }
        else if(hexAddress.at(i) == '6') {
            binAddress += "0110";
        }
        else if(hexAddress.at(i) == '7') {
            binAddress += "0111";
        }
        else if(hexAddress.at(i) == '8') {
            binAddress += "1000";
        }
        else if(hexAddress.at(i) == '9') {
            binAddress += "1001";
        }
        else if(hexAddress.at(i) == 'A' || hexAddress.at(i) == 'a') {
            binAddress += "1010";
        }
        else if(hexAddress.at(i) == 'B' || hexAddress.at(i) == 'b') {
            binAddress += "1011";
        }
        else if(hexAddress.at(i) == 'C' || hexAddress.at(i) == 'c') {
            binAddress += "1100";
        }
        else if(hexAddress.at(i) == 'D' || hexAddress.at(i) == 'd') {
            binAddress += "1101";
        }
        else if(hexAddress.at(i) == 'E' || hexAddress.at(i) == 'e') {
            binAddress += "1110";
        }
        else if(hexAddress.at(i) == 'F' || hexAddress.at(i) == 'f') {
            binAddress += "1111";
        }
    }
    while(binAddress.length() < 32) {
        binAddress = "0" + binAddress;
    }
    return binAddress;
}

void fullyAssociative(vector<string>& addresses, int bytesPerBlock, int numBlocks, int cacheSize) {

}

void directMap(vector<string>& addresses, int bytesPerBlock, int cacheSize) {
    int hits = 0;
    int misses = 0;
    map<string, string> treeMap;
    for(int i = 0; i < addresses.size(); i++) {
        int numLines = cacheSize/bytesPerBlock;
        int lineWidth = log2(numLines);
        int offsetWidth = log2(bytesPerBlock);
        int tagWidth = addresses.at(i).length() - lineWidth - offsetWidth;
        string tag = addresses.at(i).substr(0, tagWidth);
        string line = addresses.at(i).substr(tagWidth, lineWidth);
        if(treeMap.find(line) != treeMap.end()) {
            if(treeMap.at(line) == tag) {
                hits++;
            }
            else {
                misses++;
                treeMap.at(line) = tag;
            }
        }
        else {
            misses++;
            treeMap.insert(make_pair(line, tag));
        }
    }
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Hit Rate: " << 100 * (double)hits/(double)(hits + misses) << "%" << endl;
}

void setAssociative(vector<string>& addresses, int bytesPerBlock, int numBlocks, int numSets, int cacheSize) {

}


int main() {
    string filename;
    cout << "Enter filename: " << endl;
    cin >> filename;

    string currDirectory = "Trace files/" + filename + ".trace";
    vector<string> addresses;
    readFile(currDirectory, addresses);
    for(int i = 0; i < addresses.size(); i++) {
        addresses.at(i) = convertToBin(addresses.at(i));
    }

    string cacheType;
    cout << "Enter cache type: " << endl;
    cin >> ws;
    getline(cin, cacheType);

    if(cacheType == "Fully Associative") {
        string replaceStrat;
        cout << "Enter replacement strategy: " << endl;
        cin >> replaceStrat;

        if(replaceStrat == "FIFO" || replaceStrat == "LRU") {
            int bytesPerBlock = 0;
            int numBlocks = 0;
            int cacheSize = 0;

            cout << "Enter how many bytes per block: " << endl;
            cin >> bytesPerBlock;

            cout << "Enter how many blocks: " << endl;
            cin >> numBlocks;

            cout << "Enter the cache size: " << endl;
            cin >> cacheSize;

            fullyAssociative(addresses, bytesPerBlock, numBlocks, cacheSize);
        }
        else {
            cout << "Invalid replacement strategy" << endl;
        }
    }
    else if(cacheType == "Direct Mapped") {
        int bytesPerBlock = 0;
        int cacheSize = 0;

        cout << "Enter how many bytes per block: " << endl;
        cin >> bytesPerBlock;

        cout << "Enter the cache size: " << endl;
        cin >> cacheSize;

        directMap(addresses, bytesPerBlock, cacheSize);
    }
    else if(cacheType == "Set Associative") {
        string replaceStrat;
        cout << "Enter replacement strategy: " << endl;
        cin >> replaceStrat;
        if(replaceStrat == "FIFO" || replaceStrat == "LRU") {
            int bytesPerBlock = 0;
            int numBlocks = 0;
            int numSets = 0;
            int cacheSize = 0;

            cout << "Enter how many bytes per block: " << endl;
            cin >> bytesPerBlock;

            cout << "Enter how many blocks: " << endl;
            cin >> numBlocks;

            cout << "Enter how many sets: " << endl;
            cin >> numSets;

            cout << "Enter the cache size: " << endl;
            cin >> cacheSize;

            setAssociative(addresses, bytesPerBlock, numBlocks, numSets, cacheSize);
        }
        else {
            cout << "Invalid replacement strategy" << endl;
        }
    }
    else {
        cout << "Invalid cache type" << endl;
    }
    return 0;
}