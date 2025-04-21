#include <bits/stdc++.h>
#include <winsock2.h>
#include <process.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

ofstream logFile("client_log.txt", ios::app);

string currentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

unsigned __stdcall receiveMessages(void* socketDesc) {
    SOCKET clientSocket = *(SOCKET*)socketDesc;
    char buffer[4096];
    while (true) {
        ZeroMemory(buffer, 4096);
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            string msg = string(buffer,0,bytesReceived);
            string timeStr = "["+ currentTime()+"] Server:";
            cout << "\n👤 " << timeStr << msg << endl;
            logFile << timeStr << msg << endl;
            cout << "🧑 You: ";
        }
    }
    return 0;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);

    WSADATA wsData;
    WORD ver =MAKEWORD(2,2);
    if(WSAStartup(ver,&wsData)!=0){
        cerr << "WSAStartup failed.\n";
        return -1;
    }

    SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket== INVALID_SOCKET){
        cerr << "Can't create socket\n";
        WSACleanup();
        return -1;
    }

    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(54000);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    int connResult = connect(clientSocket,(sockaddr*)&server,sizeof(server));
    if(connResult==SOCKET_ERROR){
        cerr<<"Can't connect to server\n";
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    cout << "✅ Connected to server!\n";

    _beginthreadex(0, 0, receiveMessages, (void*)&clientSocket, 0, 0);
    

    string userInput;
    while(true){
        cout << "🧑 You: ";
        getline(cin, userInput);

        if (userInput == "exit") {
            break;
        }

        string logEntry = "[" + currentTime() + "] You: " + userInput;
        logFile << logEntry << endl;
        send(clientSocket, userInput.c_str(), userInput.size(), 0);
    }

    logFile.close();
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}