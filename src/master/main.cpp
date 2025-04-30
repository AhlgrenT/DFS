#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>

#define PORT 9000

void handle_client(int client_socket) {
    sleep(1);

    int32_t connection_id;
    ssize_t bytesRead = read(client_socket, &connection_id, sizeof(connection_id));  // Read 4 bytes

    if (bytesRead != sizeof(connection_id)) {
        std::cerr << "Error: incomplete read\n";
        close(client_socket);
        return;
    }

    std::cout << "Slave connected with ID: " << connection_id << std::endl;

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to reuse port and address
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Bind to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "[MASTER] Listening on port " << PORT << "...\n";

    // Accept and handle clients
    while (true) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[128] = {0};

        ssize_t bytes_received = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            std::cerr << "Failed to read client type\n";
            close(new_socket);
            return 0;
        }
        
        std::string node_type(buffer, bytes_received);

        if (node_type.find("SLAVE") != std::string::npos) {
            std::cout << "Server connection\n";
            close(new_socket);
            //handle_server(new_socket); TODO
        } else if (node_type.find("CLIENT") != std::string::npos) {
            std::cout << "Client connection\n";
            close(new_socket);
            //handle_client(new_socket); TODO
        } else {
            const char* err = "Unknown client type\n";
            send(new_socket, err, strlen(err), 0);
            close(new_socket);
            std::cerr << "Unknown node type\n";
        }
    }

    return 0;
}