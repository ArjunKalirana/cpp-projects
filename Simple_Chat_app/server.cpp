#include <bits/stdc++.h>
#include <winsock2.h>
#include <ctime>
#include<fstream>
#pragma  comment(lib,"ws2_32.lib")
using namespace std;

string currentTime(){
    time_t now =time(0);
    tm* ltm =localtime(&now);
    char buffer[80];
    strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}
int main(){
    SetConsoleOutputCP(CP_UTF8);

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);

    SOCKET serverSocket = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in serverAddr;
    serverAddr.sin_family =AF_INET;
    serverAddr.sin_port = htons(54000);
    serverAddr.sin_addr.s_addr=INADDR_ANY;

    bind(serverSocket,(sockaddr*)&serverAddr,sizeof(serverAddr));

    listen(serverSocket,SOMAXCONN);
    cout <<"🟢 server listening on port 54000 ... \n";

    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket =accept(serverSocket,(sockaddr*)& client,&clientSize);
    cout << " ✅ Client connected!\n\n";

    char buffer[4096];
    ofstream logFile("server_logs.txt",ios::app);
    while(true){
        ZeroMemory(buffer,4096);

        int bytesReceived =recv(clientSocket,buffer,4096,0);
        if(bytesReceived <= 0){
            cout << "❌ Connection lost.\n";
            break;
        }
        string timestr=currentTime();
        string msg=string(buffer,0,bytesReceived);
        string finalMsg = "[" +timestr + "] Client: "+msg;
        cout <<finalMsg<<endl;
        logFile<<finalMsg<<endl;
        
        send(clientSocket,buffer,bytesReceived,0);
    }
    logFile.close();
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}