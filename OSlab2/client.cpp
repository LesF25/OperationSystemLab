#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

#define PORT 8080

int main() {
    struct sockaddr_in serverAddress;
    int sock = 0;
    string str;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("create error \n");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Converting address to the binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        printf("Error: Address not supported \n");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Connection failed \n");
        exit(EXIT_FAILURE);
    }
    
    while(true)
    {
    	cout << "Enter message: ";
    	cin >> str;
    	
    	send(sock, str.c_str(), sizeof(str), 0);
    	printf("Message sent \n");
    	
    	str = "";
    }
    close(sock);

    return 0;
}
