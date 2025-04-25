#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>


using namespace std;

map<string,pair<string,string>> passwordDB;

string generatePassword(int length);
void copyToClipboard(const string &text);

void showMenu(){
    cout << "\n===== Password Manager =====\n";
    cout << "1️⃣  Add new password\n";
    cout << "2️⃣  View all passwords\n";
    cout << "3️⃣  Search password by service\n";
    cout << "4️⃣  Delete a password\n";
    cout << "5️⃣  Export decrypted passwords\n";
    cout << "6️⃣  Exit\n";
    cout << "7️⃣  Generate strong password\n";
    cout << "8️⃣  Search password by username\n";



    cout << "Enter your choice: ";
}


void viewPasswords(){
    if(passwordDB.empty()){
        cout<< "⚠️ No passwords saved yet.\n";
        return ;
    }
    char choice;
    cout<<"Show passwords in plain text?(y/n): ";
    cin >> choice;
    bool show = (choice =='y'||choice=='Y');

    cout << "\n 🟢 Saved Passwords:\n";
    for(auto &entry:passwordDB){
        cout<< " Service: " << entry.first
            << ", Username: " <<entry.second.first;
            if(show)
                cout<<", Password: " << entry.second.second ;
            else
                cout<<", Password: ********";
            cout << endl;
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
    

    char choice;
    cout << "Generate strong password automatically? (y/n): ";
    cin >> choice;

    if(choice == 'y'|| choice == 'Y'){
        int length;
        cout<< "Enter desired password length: ";
        cin >> length;
        password = generatePassword(length);
        cout<< " Generated password: "<<password << "\n";

        char cpy;
        cout <<"Copy password to clipboard?(y/n): ";
        cin>>cpy;
        if(cpy=='y'|| cpy=='Y'){
            copyToClipboard(password);
        }

    }
    else{
        cout << "Enter password: ";
        cin >> password;
    }

    

    passwordDB[service] =make_pair(username,password);
    saveToFile();
    cout<< "✅ Password added for service:" << service <<endl;
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

void searchPassword(){
    string service;
    cout << "Enter service name to search: ";
    cin >> service;
    auto it =passwordDB.find(service);
    if(it!=passwordDB.end()){
        cout << "✅ Found!\n";
        cout << "Username: " <<it->second.first << "\n Password: " << it->second.second <<endl;

    }
    else{
        cout <<"⚠️ No entry found for service: " <<service <<endl;
    }
}

void deletePassword(){
    string service;
    cout << "Enter service name to delete: ";
    cin>> service;

    auto it = passwordDB.find(service);
    if(it !=passwordDB.end()){
        char confirm;
        cout << "⚠️ Are you sure you want to delete the entry for " << service << "? (y/n): ";
        cin >>confirm;
        if(confirm=='y'|| confirm=='Y'){
            passwordDB.erase(it);
        saveToFile();
        cout<< "🗑️ Password entry for " << service << " deleted.\n";}
        else{
            cout << "❌ Deletion cancelled.\n";
        }
    }
    else{
        cout << "❌ No such service found.\n";
    }
}
void exportDecryptedPasswords(){
    ofstream out("decrypted_passwords.txt");
    for(const auto &entry : passwordDB){
        out << "Service: " << entry.first
            << ", Username: " << entry.second.first
            << ", Password: " << entry.second.second << "\n";
    }
    out.close();
    cout << "✅ Decrypted passwords exported to 'decrpted_passwords.txt'\n";
}

string generatePassword(int length){
    const string chars=
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%^&*()_+-=[]{}|;:,.<>?";

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0,chars.size()-1);

        string password = "";
        for(int i=0;i<length;++i){
            password+=chars[dist(gen)];
        }
        return password;
}

void copyToClipboard(const string &text){
    const size_t len =text.length() + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE,len);
    memcpy(GlobalLock(hMem),text.c_str(),len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT,hMem);
    CloseClipboard();
    cout<< "📋 Password copied to clipboard!\n";
}

void searchByUsername(){
    string username;
    cout << "Enter username to search: ";
    cin >> username;
    bool found= false;

    for(const auto &entry : passwordDB){
        if(entry.second.first == username){
            cout << "✅ Found entry:\n";
            cout << "Service: " << entry.first
                 << ", Username: " << entry.second.first
                 << ", Password: " << entry.second.second << "\n";
            found = true;
        }
    }
    if(!found){
        cout<<"⚠️ No entries found for username: "<<username << "\n";
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
                searchPassword();
                break;
            case 4:
                deletePassword();
                break;
            case 5:
                exportDecryptedPasswords();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            case 7: {
                int len;
                cout << "Enter desired password length: ";
                cin >> len;
                string p = generatePassword(len);
                cout << "🔐 Generated Password: " << p << "\n";
                

                char cpy;
                cout <<"Copy password to clipboard? (y/n): ";
                cin>>cpy;
                if(cpy=='y'||cpy=='Y'){
                    copyToClipboard(p);
                }
                break;
            }
            case 8:
                searchByUsername();
                break;


            default:
                cout << "Invalid choice! Try again.\n";

        }
    }
    
}
