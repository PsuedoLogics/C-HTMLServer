using namespace std;
#include <iostream>

#include "Server.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    bool stop = false;
    Server newServer(8081);

    newServer.StartServer();
    newServer.bindPort();
    newServer.listenOnPort();

    while (!stop) {
        newServer.getClientConnections();
        cout << "type stop to stop: " << endl;

    }
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.