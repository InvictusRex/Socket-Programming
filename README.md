# Socket Programming in C

This repository contains various examples of socket programming in C, including TCP and UDP client-server models. The programs demonstrate how to establish communication between different processes over a network.

## Features
- TCP and UDP client-server communication
- Multi-threaded server implementation
- File transfer over sockets
- Basic chat application using sockets

## Prerequisites
- A C compiler (GCC recommended)
- A Linux-based operating system (or WSL for Windows users)
- Basic knowledge of networking concepts

## Installation
Clone the repository:
```sh
git clone https://github.com/InvictusRex/Socket-Programming.git
cd Socket-Programming
```

## File Descriptions
### TCP Files:
- **tcp_server.c** – Implements a basic TCP server that listens for client connections, receives messages, and sends responses.
- **tcp_client.c** – Implements a TCP client that connects to the server, sends messages, and receives responses.

### UDP Files:
- **udp_server.c** – Implements a UDP server that receives messages from clients and responds accordingly.
- **udp_client.c** – Implements a UDP client that sends messages to the server and waits for responses.

### Multi-threaded Server:
- **multi_thread_server.c** – Implements a TCP server that can handle multiple clients simultaneously using threads.
- **multi_thread_client.c** – A client program that interacts with the multi-threaded server.

### File Transfer:
- **file_server.c** – A TCP server capable of sending files to a connected client.
- **file_client.c** – A TCP client that can request and receive files from the server.

### Chat Application:
- **chat_server.c** – A simple chat server that can manage multiple clients.
- **chat_client.c** – A client program that enables real-time messaging between users.

## Compilation & Execution
### TCP Server & Client
1. Compile the server and client:
   ```sh
   gcc tcp_server.c -o server
   gcc tcp_client.c -o client
   ```
2. Run the server:
   ```sh
   ./server
   ```
3. In a separate terminal, run the client:
   ```sh
   ./client
   ```

### UDP Server & Client
1. Compile the server and client:
   ```sh
   gcc udp_server.c -o server
   gcc udp_client.c -o client
   ```
2. Run the server:
   ```sh
   ./server
   ```
3. In a separate terminal, run the client:
   ```sh
   ./client
   ```

## Contributing
Contributions are welcome! Feel free to submit a pull request if you find any improvements.

## License
This project is licensed under the MIT License.
