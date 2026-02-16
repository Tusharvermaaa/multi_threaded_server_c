# Multi Threaded TCP Client Server in C and C++

A high performance concurrent TCP Client–Server system implemented using POSIX socket programming and pthread based multi-threading in C++.

This project demonstrates how to build a scalable server capable of handling multiple client connections simultaneously using thread based concurrency while ensuring safe TCP stream communication.

---

## 🚀 Features

* Multi-client support using pthreads
* Concurrent request handling
* Safe TCP communication (handles partial send/recv)
* Connection oriented communication
* SIGPIPE protection
* Memory safe thread argument passing
* Optimized socket usage
* Clean modular implementation

---

## 🛠️ Tech Stack

* C++
* POSIX Socket Programming
* Pthreads
* TCP/IP Networking
* Linux System Calls

---

## 📂 Project Structure

```
├── client.cpp
├── server.cpp
└── README.md
```

---

## ⚙️ How it Works

1. Server initializes TCP socket.
2. Server binds to port 8080.
3. Server listens for incoming client connections.
4. Each client connection is handled by a separate thread.
5. Server receives request from client.
6. Server processes request and sends response.
7. Communication continues until client disconnects.

---

## 🧑‍💻 Compilation

### Compile Server

```
g++ server.cpp -o server -lpthread
or
g++ server.cpp -o server -pthread
```

### Compile Client

```
g++ client.cpp -o client
```

---

## ▶️ Execution

### Run Server

```
./server
```

### Run Client

```
./client <server-ip>
```

Example:

```
./client 127.0.0.1

note: 127.0.0.1 is the localhost/(ip of server machine is required) , in our case i am running in same system so localhost(127.0.0.1) is used
```

---

## 📡 Communication Flow

```
Client ---- Request ----> Server
Client <--- Response ---- Server
```

Multiple clients can connect to the server concurrently.

---

## 📈 Scalability

The threaded model allows:

* Parallel request handling
* Reduced waiting time
* Better CPU utilization
* Improved throughput

---

## 🔒 Error Handling

* Connection failure detection
* Safe socket closure
* Partial data transmission handling
* Invalid input handling

---

## 📌 Future Improvements

* Thread Pool Implementation
* Non-blocking Sockets
* epoll based I/O Multiplexing
* Load Balancing
* Logging System
* Graceful Shutdown Support

---

## 📜 License

This project is open source and available under the MIT License.

---

## 🤝 Contribution

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

---
