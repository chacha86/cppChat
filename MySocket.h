#ifndef MY_SOCKET
#define MY_SOCKET
#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <vector>
#define MAX_BUFF_SIZE 100
namespace MySocket {

	typedef struct SocketData {
		SOCKET target_sock; // 辑滚 家南
		sockaddr_in target_addr; // 辑滚 林家(IP)
	} SocketData;

	class Socket {
	protected:
		SocketData curr_socket_data;
		WSADATA wsaData;
		char buffer_out[MAX_BUFF_SIZE];
		char buffer_in[MAX_BUFF_SIZE];

		void set_addr(sockaddr_in& addr, int port, ULONG ip);
		SOCKET make_socket();
	public:
		Socket(int port);
		Socket(const char* ip, int port);
		char* recv_data();
		void send_data(const char* msg);
		void print_data();
		void set_socket(SocketData socket);
		SocketData get_socket();
	};

	class ServerSocket : public Socket {
	private:
		int skt_size;
		SocketData skt_list[10];
		SOCKET serv_sock;
		sockaddr_in serv_addr;
	public:
		ServerSocket(int port);
		SocketData MyAccept();
	};
}
#endif
