#include <string>
#include <chrono>
#include <thread>
#include <iostream>

#include <zmq.hpp>
int main()
{
	using namespace std::chrono_literals;
	zmq::context_t context{ 1 };
	zmq::socket_t socket{ context,zmq::socket_type::rep };
	zmq::message_t request;
	socket.bind("tcp://*:5555");	//°ó¶¨¶Ë¿Ú
	std::cout << "Server:localhost ip 5555 port" << std::endl << "Connecting" << std::endl;
	while (true) {
		socket.recv(request, zmq::recv_flags::none);
		std::cout << "Servce Received: " << request.to_string() << std::endl;
		socket.send(zmq::buffer("RECV"), zmq::send_flags::none);
	}
	system("pause");
	return 0;
}

