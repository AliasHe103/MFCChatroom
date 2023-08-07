#include <string>
#include <iostream>

#include <zmq.hpp>
int main()
{
	zmq::context_t context{ 1 };
	zmq::socket_t socket{ context, zmq::socket_type::req};//建立套接字
	std::cout << "Connecting to hello world server..." << std::endl;//连接服务器
	socket.connect("tcp://localhost:5555");
	while (1) {
		std::string send_str;
		std::cin >> send_str;
		socket.send(zmq::buffer(send_str), zmq::send_flags::none);
		zmq::message_t reply{};
		socket.recv(reply, zmq::recv_flags::none);
		std::cout << "Client Received: " << reply.to_string() << std::endl;
	}
	system("pause");
	return 0;
}
