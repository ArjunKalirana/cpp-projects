#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>


using namespace std;

map<string,pair<string,string>> passwordDB;

void showMenu(){
    cout << "\n===== Password Manager =====\n";
    cout << "1️⃣  Add new password\n";
    cout << "2️⃣  View all passwords\n";
    cout << "3️⃣  Exit\n";
    cout << "Enter your choice: ";
}


void viewPasswords(){
    if(passwordDB.empty()){
        cout<< "No passwords saved yet.\n";
        return ;
    }

    cout << "\nSaved Passwords:\n";
    for(auto &entry:passwordDB){
        cout<< "Service: " << entry.first
            << ", Username: " <<entry.second.first
            << ", Password: " << entry.second.second <<endl;
    }
}

const string FILENAME = "password.txt";
string masterKey = "mySecretKey";

string xorEncryptDecrypt(const string &input,const string &key){
    string output=input;
    for(size_t i=0;i<input.size();++i){
        output[i]=input[i] ^ key[i%key.size()];
    }
    return output;
}

void saveToFile(){
    ofstream file(FILENAME);
    for(const auto &entry :passwordDB){
        string line = entry.first +"," +entry.second.first + ","+entry.second.second;
        file << xorEncryptDecrypt(line,masterKey) <<endl;
    }
    file.close();
}

void addPassword(){
    string service, username,password;
    cout<< "Enter service name: ";
    cin >> service;
    cout<< "Enter username: ";
    cin>> username;
    cout << "Enter password: ";
    cin >> password;

    passwordDB[service] =make_pair(username,password);
    saveToFile();
    cout<< "Password added for service:" << service <<endl;
}

void loadFromFile(){
    ifstream file(FILENAME);
    if(!file.is_open())return ;

    string line;
    while(getline(file,line)){
        string decrypted = xorEncryptDecrypt(line,masterKey);
        size_t pos1 = decrypted.find(',');
        size_t pos2 =decrypted.find(',',pos1+1);

        if(pos1==string::npos || pos2 == string::npos) continue;
        string service =decrypted.substr(0,pos1);
        string username = decrypted.substr(pos1+1,pos2-pos1-1);
        string password = decrypted.substr(pos2+1);

        passwordDB[service] = make_pair(username,password);
    }
    file.close();
}

const string Master_File = "master.hash";

string getMasterPassword(){
    string input;
    cout<<"Enter master password: ";
    cin>> input;
    return input;
}

 int simpleHash(const string &str){
    int hash=0;
    for(char c:str) hash+=c*31;
    return hash;
 }

 bool verifyMasterPassword(const string& entered) {
    ifstream file(Master_File);
    int storeHash;
    if (file >> storeHash) {
        file.close();
        return simpleHash(entered) == storeHash;
    } else {
        file.close();
        cout << "No master password set. Creating one now...\n";
        ofstream out(Master_File);
        out << simpleHash(entered);
        out.close();
        masterKey = entered;
        cout << "Master password set!\n";
        return true;
    }
}

int main(){
    string enteredMaster = getMasterPassword();
    if (!verifyMasterPassword(enteredMaster)) {
        cout << "Incorrect master password!\n";
        return 1;
    }

    masterKey = enteredMaster;


    loadFromFile();
    
    SetConsoleOutputCP(CP_UTF8);
    int choice;
    while(true){
        showMenu();
        cin >> choice;

        switch(choice){
            case 1:
                addPassword();
                break;
            case 2:
                viewPasswords();
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";

        }
    }
    
}