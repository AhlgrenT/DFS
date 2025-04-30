#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MASTER_IP "127.0.0.1"
#define MASTER_PORT 9000

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char* hello = "SLAVE";
    char buffer[1024] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(MASTER_PORT);

    if (inet_pton(AF_INET, MASTER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        return 1;
    }

    // Connect to master
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }

    send(sock, hello, strlen(hello), 0);
    std::cout << "[SLAVE] Sent: " << hello << std::endl;

    int valread = read(sock, buffer, 1024);
    if (valread > 0)
        std::cout << "[SLAVE] Received: " << buffer << std::endl;

    close(sock);
    return 0;
}
