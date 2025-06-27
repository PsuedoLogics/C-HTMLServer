//
// Created by Michael Mathews on 6/18/25.
//

#ifndef SERVER_H
#define SERVER_H



class Server {
private:
    int m_port;

public:
    Server(int port);
    void StartServer();
    void SetPort(int port);
    int GetPort();
    void bindPort();
    void listenOnPort();
    void getClientConnections();

};



#endif //SERVER_H
