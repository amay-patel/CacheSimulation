/**
 * @author Amay Patel
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include <list>
#include <queue>

using namespace std;

/**
 * @brief This function will read in the file the user inputs and store the addresses into a vector
 * @param directory the file the user inputs
 * @param addresses the vector that will be populated with the addresses in the file
 */

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

/**
 * @brief This function will take in a hex address and convert it to a binary address
 * @param hexAddress the hex address that will be converted to binary
 * @return string binary address
 */

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

/**
 * @brief This function will calculate the hit rate for a fully associative cache
 * @param addresses the vector of addresses that will be used to calculate the hit rate
 * @param bytesPerBlock the amount of bytes per block in cache
 * @param cacheSize the size of the cache
 * @param replacementPolicy the replacement policy the user wants to use (FIFO or LRU)
 */

void fullyAssociative(vector<string>& addresses, int bytesPerBlock, int cacheSize, string& replacementPolicy) {
    int hits = 0;
    int misses = 0;
    map<string, string> treeMap;
    queue<string> tagQueue;
    list<string> tagList;
    for(int i = 0; i < addresses.size(); i++) {
        int numLines = cacheSize / bytesPerBlock;
        int offsetWidth = log2(bytesPerBlock);
        int tagWidth = addresses.at(i).length() - offsetWidth;
        string tag = addresses.at(i).substr(0, tagWidth);
        string offset = addresses.at(i).substr(tagWidth, offsetWidth);
        if(treeMap.find(tag) == treeMap.end()) {
            misses++;
            if(treeMap.size() < numLines) {
                treeMap.insert(make_pair(tag, offset));
                if(replacementPolicy == "FIFO") {
                    tagQueue.push(tag);
                }
                else if(replacementPolicy == "LRU") {
                    tagList.push_back(tag);
                }
            }
            else if(treeMap.size() == numLines) {
                if(replacementPolicy == "FIFO") {
                    treeMap.erase(tagQueue.front());
                    tagQueue.pop();
                    tagQueue.push(tag);
                }
                else if(replacementPolicy == "LRU") {
                    treeMap.erase(tagList.front());
                    tagList.pop_front();
                    tagList.push_back(tag);
                }
                treeMap.insert(make_pair(tag, offset));
            }
        }
        else {
            hits++;
            if(replacementPolicy == "LRU") {
                tagList.remove(tag);
                tagList.push_back(tag);
            }
        }
    }
    cout << "Hit Rate: " << (double)hits/(double)(hits + misses) << endl;
}

/**
 * @brief This function will calculate the hit rate for a direct mapped cache
 * @param addresses the vector of addresses that will be used to calculate the hit rate
 * @param bytesPerBlock the amount of bytes per block in cache
 * @param cacheSize the size of the cache
 */

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
        if(treeMap.find(line) == treeMap.end()) {
            misses++;
            treeMap.insert(make_pair(line, tag));
        }
        else {
            if(treeMap.at(line) == tag) {
                hits++;
            }
            else {
                misses++;
                treeMap.at(line) = tag;
            }
        }
    }
    cout << "Hit Rate: " << (double)hits/(double)(hits + misses) << endl;
}

/**
 * @brief This function will calculate the hit rate for a n-way set associative cache
 * @param addresses the vector of addresses that will be used to calculate the hit rate
 * @param bytesPerBlock the amount of bytes per block in cache
 * @param nSetWay the number of sets in the cache
 * @param cacheSize the size of the cache
 * @param replacementPolicy the replacement policy the user wants to use (FIFO or LRU)
 */

void setAssociative(vector<string>& addresses, int bytesPerBlock, int nSetWay, int cacheSize, string& replacementPolicy) {
    int hits = 0;
    int misses = 0;
    map<string, map<string, string>> treeMap;
    map<string, queue<string>> tagQueueMap;
    map<string, list<string>> tagListMap;
    for(int i = 0; i < addresses.size(); i++) {
        int numOfSets = (cacheSize / bytesPerBlock) / nSetWay;
        int setWidth = log2(numOfSets);
        int offsetWidth = log2(bytesPerBlock);
        int tagWidth = addresses.at(i).length() - setWidth - offsetWidth;
        string tag = addresses.at(i).substr(0, tagWidth);
        string set = addresses.at(i).substr(tagWidth, setWidth);
        string offset = addresses.at(i).substr(tagWidth + setWidth, offsetWidth);

        if(treeMap.find(set) == treeMap.end()) {
            misses++;
            map<string, string> tempMap;
            tempMap.insert(make_pair(tag, offset));
            treeMap.insert(make_pair(set, tempMap));

            if(replacementPolicy == "FIFO") {
                queue<string> q;
                q.push(tag);
                tagQueueMap.insert(make_pair(set, q));
            }

            else if(replacementPolicy == "LRU") {
                list<string> l;
                l.push_back(tag);
                tagListMap.insert(make_pair(set, l));
            }
        }

        else {

            if(treeMap.at(set).find(tag) == treeMap.at(set).end()) {
                misses++;

                if(treeMap.at(set).size() < nSetWay) {
                    treeMap.at(set).insert(make_pair(tag, offset));

                    if(replacementPolicy == "FIFO") {
                        tagQueueMap.at(set).push(tag);
                    }

                    else if(replacementPolicy == "LRU") {
                        tagListMap.at(set).push_back(tag);
                    }
                }

                else if(treeMap.at(set).size() == nSetWay) {
                    if(replacementPolicy == "FIFO") {
                        treeMap.at(set).erase(tagQueueMap.at(set).front());
                        tagQueueMap.at(set).pop();
                        tagQueueMap.at(set).push(tag);
                    }

                    else if(replacementPolicy == "LRU") {
                        treeMap.at(set).erase(tagListMap.at(set).front());
                        tagListMap.at(set).pop_front();
                        tagListMap.at(set).push_back(tag);
                    }
                    treeMap.at(set).insert(make_pair(tag, offset));
                }
            }

            else {
                hits++;

                if(replacementPolicy == "LRU") {
                    tagListMap.at(set).remove(tag);
                    tagListMap.at(set).push_back(tag);
                }
            }
        }
    }
    cout << "Hit Rate: " << (double)hits/(double)(hits + misses) << endl;
}

/**
 * @brief this function was used to calculate the hit rates for the three different cache designs
 * @param addresses - the vector of addresses that will be used to calculate the hit rate
 * @attention commented in main() method. Results from method call were saved into a Excel file to create line graph
 */

void simulateValues(vector<string>& addresses) {
    int start = pow(2, 9);
    int end = pow(2, 16);

    string fifo = "FIFO";
    string lru = "LRU";

    cout << "Fully Associative (FIFO)" << endl;
    for(int i = start; i <= end; i *= 2) {
        fullyAssociative(addresses, 64, i, fifo);
    }
    cout << endl;

    cout << "Fully Associative (LRU)" << endl;
    for(int i = start; i <= end; i *= 2) {
        fullyAssociative(addresses, 64, i, lru);
    }
    cout << endl;

    cout << "Direct Mapped" << endl;
    for(int i = start; i <= end; i *= 2) {
        directMap(addresses, 64, i);
    }
    cout << endl;

    for(int i = 2; i <= 8; i *= 2) {
        cout << "Set Associative " << i << "-way (FIFO)";
        cout << endl;
        for(int j = start; j <= end; j *= 2) {
            setAssociative(addresses, 64, i, j, fifo);
        }
    }

    for(int i = 2; i <= 8; i *= 2) {
        cout << "Set Associative " << i << "-way (LRU)";
        cout << endl;
        for(int j = start; j <= end; j *= 2) {
            setAssociative(addresses, 64, i, j, lru);
        }
    }
}

int main() {
    string filename;
    cout << "Enter filename: " << endl;
    cin >> filename;

    string currDirectory = "Trace files/" + filename + ".trace";
    vector<string> addresses;
    readFile(currDirectory, addresses);
    for(string& address : addresses) {
        address = convertToBin(address);
    }
//    simulateValues(addresses);
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
            int cacheSize = 0;

            while(true) {

                cout << "Enter bytes per block: " << endl;
                cin >> bytesPerBlock;

                if(bytesPerBlock >= 4 && (bytesPerBlock & bytesPerBlock - 1) == 0) {
                    break;
                }

                else {
                    cout << "Invalid number of bytes in a block" << endl;
                    cout << endl;
                }
            }

            while(true) {

                cout << "Enter the cache size: " << endl;
                cin >> cacheSize;

                if(cacheSize <= 0 && (cacheSize & cacheSize - 1) == 0) {
                    cout << "Cache size must be a power of 2" << endl;
                    cout << endl;
                }

                else {
                    break;
                }
            }
            fullyAssociative(addresses, bytesPerBlock, cacheSize, replaceStrat);
        }
        else {
            cout << "Invalid replacement strategy" << endl;
        }
    }

    else if(cacheType == "Direct Mapped") {
        int bytesPerBlock = 0;
        int cacheSize = 0;

        while(true) {

            cout << "Enter bytes per block: " << endl;
            cin >> bytesPerBlock;

            if(bytesPerBlock >= 4 && (bytesPerBlock & bytesPerBlock - 1) == 0) {
                break;
            }

            else {
                cout << "Invalid number of bytes in a block" << endl;
                cout << endl;
            }
        }
        while(true) {

            cout << "Enter the cache size: " << endl;
            cin >> cacheSize;

            if (cacheSize <= 0 && (cacheSize & cacheSize - 1) == 0) {
                cout << "Cache size must be a power of 2" << endl;
                cout << endl;
            } else {
                break;
            }
        }
        directMap(addresses, bytesPerBlock, cacheSize);
    }

    else if(cacheType == "Set Associative") {
        string replaceStrat;
        cout << "Enter replacement strategy: " << endl;
        cin >> replaceStrat;

        if(replaceStrat == "FIFO" || replaceStrat == "LRU") {
            int bytesPerBlock = 0;
            int cacheSize = 0;
            int nSetWay = 0;

            while(true) {

                cout << "Enter bytes per block: " << endl;
                cin >> bytesPerBlock;

                if(bytesPerBlock >= 4 && (bytesPerBlock & bytesPerBlock - 1) == 0) {
                    break;
                }

                else {
                    cout << "Invalid number of bytes in a block" << endl;
                    cout << endl;
                }
            }

            while(true) {

                cout << "Enter the cache size: " << endl;
                cin >> cacheSize;

                if(cacheSize <= 0 && (cacheSize & cacheSize - 1) == 0) {
                    cout << "Cache size must be a power of 2" << endl;
                    cout << endl;
                }

                else {
                    break;
                }
            }

            cout << "Enter number in to represent n-set way: " << endl;
            cin >> nSetWay;

            setAssociative(addresses, bytesPerBlock, nSetWay, cacheSize, replaceStrat);
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