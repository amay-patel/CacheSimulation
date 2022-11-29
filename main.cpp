#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void readFile(string filename, vector<string>& addresses) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string currAddress;
        std::getline(iss, currAddress, ' ');
        std::getline(iss, currAddress, ' ');
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

void directMap(const string& filename, int blockSize, int cacheSize) {

}

void setAssociative(const string& filename, int blockSize, int cacheSize, string& replaceStrat) {

}
void fullyAssociative(const string& filename, int blockSize, int cacheSize, string& replaceStrat) {

}

int main() {
    string cacheType = "";
    string filename = "gcc.trace";
    vector<string> addresses;
    readFile(filename, addresses);
    for(int i = 0; i < addresses.size(); i++) {
        convertToBin(addresses.at(i));
    }
    cout << "Enter cache type: " << endl;
    getline(cin, cacheType);

    if(cacheType == "Fully Associative") {
        string replaceStrat = "";
        cout << "Enter replacement strategy: " << endl;
        getline(cin, replaceStrat);

        if(replaceStrat == "LRU") {
            int blockSize = 0;
            cout << "Enter block size: " << endl;
            cin >> blockSize;

            int cacheSize = 0;
            cout << "Enter cache size: " << endl;
            cin >> cacheSize;

            fullyAssociative(filename, blockSize, cacheSize, replaceStrat);
        }
        else if(replaceStrat == "FIFO") {
            int blockSize = 0;
            cout << "Enter block size: " << endl;
            cin >> blockSize;

            int cacheSize = 0;
            cout << "Enter cache size: " << endl;
            cin >> cacheSize;

            fullyAssociative(filename, blockSize, cacheSize, replaceStrat);
        }
        else {
            cout << "Invalid replacement strategy" << endl;
        }
    }
    else if(cacheType == "Direct Mapped") {
        int blockSize = 0;
        cout << "Enter block size: " << endl;
        cin >> blockSize;

        int cacheSize = 0;
        cout << "Enter cache size: " << endl;
        cin >> cacheSize;
    }
    else if(cacheType == "Set Associative") {
        string replaceStrat = "";
        cout << "Enter replacement strategy: " << endl;
        getline(cin, replaceStrat);

        if(replaceStrat == "LRU") {
            int blockSize = 0;
            cout << "Enter block size: " << endl;
            cin >> blockSize;

            int cacheSize = 0;
            cout << "Enter cache size: " << endl;
            cin >> cacheSize;

            setAssociative(filename, blockSize, cacheSize, replaceStrat);
        }
        else if(replaceStrat == "FIFO") {
            int blockSize = 0;
            cout << "Enter block size: " << endl;
            cin >> blockSize;

            int cacheSize = 0;
            cout << "Enter cache size: " << endl;
            cin >> cacheSize;

            setAssociative(filename, blockSize, cacheSize, replaceStrat);
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