#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MYPORT 9434    /* numar port va fi completat corespunzator */
#define BACKLOG 10     /* numar de conexiuni  concurente*/
#define CLIENT_1_PORT 9435
#define CLIENT_2_PORT 9436

void send_to_client(int network_socket, int port, char* ip_address);
char* read_keyboard_message();

int main(int argc, char* argv[]) {

  int network_socket = socket(AF_INET, SOCK_DGRAM, 0);

  //Specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(MYPORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Set the socket to non-blocking mode
  int flags = fcntl(network_socket, F_GETFL, 0);
  fcntl(network_socket, F_SETFL, flags | O_NONBLOCK);

  //bind the socket
  if(bind(network_socket, (struct sockaddr *) &server_address, sizeof(server_address))){
    printf("Error binding socket: %s\n", strerror(errno));
    return 1;
  }

  send_to_client(network_socket, CLIENT_1_PORT, "127.0.0.2");

  return 0;
}

void send_to_client(int network_socket, int port, char* ip_address) {
  //Accept the connection
  struct sockaddr_in client_address;
  
  //Set client ip and port to client_address
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(port);
  client_address.sin_addr.s_addr = inet_addr(ip_address);
  socklen_t client_address_len = sizeof(client_address);

  //Send the message
  char *server_message;
  while(server_message = read_keyboard_message(), strcmp(server_message, "exit\n") != 0) {
    if(strcmp(server_message, "broadcast\n") == 0) {
      for(int i = 1; i <= 100; i++) {
        sprintf(server_message, "%d\n", i);
        sendto(network_socket, server_message, sizeof(server_message), 0, (struct sockaddr *) &client_address, client_address_len);
      }
    } else {
      sendto(network_socket, server_message, strlen(server_message), 0, (struct sockaddr *) &client_address, client_address_len);
    }

    free(server_message);
  }
}

char* read_keyboard_message() {
  char* message = (char*) malloc(512);
  printf("broadcast> ");
  fgets(message, 512, stdin);
  return message;
}
