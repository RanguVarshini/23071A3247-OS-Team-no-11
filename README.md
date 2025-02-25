# Distributed Chat Application using Sockets
This project demonstrates a distributed chat application using UNIX domain sockets for local communication and Internet domain sockets for network communication. It includes a multi-threaded server that can handle multiple clients simultaneously, making it suitable for learning distributed systems, IPC (Inter-Process Communication), and socket programming.

## Features
- *UNIX Domain Sockets*: Efficient local communication between processes on the same machine.
- *Internet Domain Sockets*: Network communication over TCP/IP for distributed systems.
- *Multi-Threaded Server*: Supports concurrent handling of multiple clients using threads.
- *Real-Time Messaging*: Facilitates real-time communication between clients and the server.
- *Scalability*: Supports up to 4 clients (configurable).

## Project Structure
The project includes separate implementations for UNIX domain communication and Internet domain communication:

### UNIX Domain Server and Client:
- *Server*: unix_server.c
- *Client*: unix_client.c

### Internet Domain Server and Client:
- *Server*: internet_server.c
- *Client*: internet_client.c

## Compilation

To compile the source code files, use the following commands:

### UNIX Domain:
```bash
gcc unix_server.c -o unix_server -lpthread
gcc unix_client.c -o unix_client
