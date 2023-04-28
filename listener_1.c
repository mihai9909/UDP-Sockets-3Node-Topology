#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define MYPORT 9435    /* numar port va fi completat corespunzator */
#define BACKLOG 10     /* numar de conexiuni  concurente*/

void print_message(char* message);

int main(int argc, char* argv[]) {
  int network_socket = socket(AF_INET, SOCK_DGRAM, 0);

  //Specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(MYPORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  //Bind the socket to the address and port
  bind(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  //Accept the connection
  struct sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);

  printf("Waiting for message...\n");
  while(1) {
    char *client_message = (char*) malloc(256 * sizeof(char));
    recvfrom(network_socket, client_message, 256, 0, (struct sockaddr *) &client_address, &client_address_len);
    print_message(client_message);
    free(client_message);
  }
  return 0;
}

void print_message(char* message) {
  char msg_aux[256];

  int i;
  for(i = 0; i < strlen(message); i++) {
    msg_aux[i] = message[i];

    if(message[i] == '\n')
      break;
  }
  msg_aux[i] = '\0';

  printf("Server says: %s\n", msg_aux);
}
