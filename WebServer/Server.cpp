#include <fstream>
//
// Created by Michael Mathews on 6/18/25.
//
using namespace std;

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Server.h"
#include <iostream>
#include <unistd.h>

int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in serverAddress;

struct sockaddr_in clientAddress;

Server::Server(int port) : m_port(port) {


}


void Server::StartServer() {

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(m_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;




}

void Server::SetPort(int newPort) {
    m_port = newPort;
}

int Server::GetPort() {
    return m_port;
}

void Server::bindPort() {
    if (::bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind");
        exit(1);
    }
}

void Server::listenOnPort() {
    if (listen(serverSocket, 5) < 0) { perror("listen"); exit(1); }
    cout << "Server listening on port " << m_port;
}

void sendAll(int socket, const char* data, size_t length) {
    size_t totalSent = 0;
    while (totalSent < length) {
        ssize_t sent = send(socket, data + totalSent, length - totalSent, 0);
        if (sent < 0) {
            perror("send");
            break;
        }
        totalSent += sent;
    }
}

string readHTMLFromFile() {
    ifstream htmlFile("homePage.txt");

    if (!htmlFile.is_open()) {
        perror("Couldn't open homePage.txt");
    }
    string output = "";
    string line;
    while (getline(htmlFile, line)) {
        output += line + "\n";
    }
    return output;
}

void Server::getClientConnections() {

    socklen_t clientAddressLength = sizeof(clientAddress);

    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

    cout <<" Client connected from " << inet_ntoa(clientAddress.sin_addr) << endl;


    string body = readHTMLFromFile();

    string httpResponse =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + to_string(body.length()) + "\r\n"
         "Connection: close\r\n"
         "\r\n" + body;


    sendAll(clientSocket, httpResponse.c_str(), strlen(httpResponse.c_str()));

    usleep(10000);
    close(clientSocket);
}
