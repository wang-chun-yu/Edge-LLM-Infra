//
//  Weather update client in C++
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode
//

#include <zmq.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  Socket to talk to server
    std::cout << "Collecting updates from weather server...\n" << std::endl;
    zmq::socket_t subscriber (context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5556");
    // Wait a bit to avoid slow joiner issue before receiving
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));

    //  Subscribe to zipcode, default is NYC, 10001
	// const char *filter = (argc > 1)? argv [1]: "10001 ";
    // subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    //  Process 100 updates
    int update_nbr;
    long total_temp = 0;
    // for (update_nbr = 0; update_nbr < 100; update_nbr++) {

    //     zmq::message_t update;
    //     int zipcode, temperature, relhumidity;

    //     subscriber.recv(update, zmq::recv_flags::none);

    //     std::istringstream iss(static_cast<char*>(update.data()));
	// 	iss >> zipcode >> temperature >> relhumidity ;

	// 	total_temp += temperature;
    // }
    // std::cout 	<< "Average temperature for zipcode '"<< filter
    // 			<<"' was "<<(int) (total_temp / update_nbr) <<"F"
    // 			<< std::endl;

    while (1) {
        zmq::message_t update;
        auto res = subscriber.recv(update, zmq::recv_flags::none);
        if (!res) {
            std::cout << "Receive failed" << std::endl;
            continue;
        }
        std::string data(static_cast<char*>(update.data()), update.size());
        std::cout << "Received(" << update.size() << "): " << data << std::endl;
    }
    return 0;
}
