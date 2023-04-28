# UDP Server-Client
This is an program that broadcasts messages using the UDP protocol.

## Prerequisites
 - C compiler (e.g. GCC)
 - Linux or Unix-based OS (e.g. Ubuntu, macOS)

## Building
To build the broadcaster, simply run the following command:
    
    gcc broadcaster.c -o broadcaster

To build the client listener programs, run the following commands:
    
    gcc listener_1.c -o listener_1
    gcc listener_2.c -o listener_2

## Running
To run the broadcaster server, simply execute the broadcaster binary:
    
    ./broadcaster

To run the client listener, simply execute the listener_1 and listener_2 binaries:

    ./listener_1
    ./listener_2

The listeners will listen for messages on port 9435 and port 9436, respectively.

If you wish to send a message to the clients, simply type the message into the console and press enter. The message will be broadcasted to all clients.

### Other broadcaster commands:

    # sends numbers from 1 to 100 to all clients
    broadcaster> broadcast
