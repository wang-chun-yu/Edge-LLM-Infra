//
//  Weather update server in C++
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates
//
#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

#if (defined (WIN32))
#include <zhelpers.hpp>
#endif

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main () {

    //  Prepare our context and publisher
    zmq::context_t context (1);
    zmq::socket_t publisher (context, zmq::socket_type::pub);
    publisher.bind("tcp://*:5556");
    publisher.bind("ipc://weather.ipc");				// Not usable on Windows.

    // Give subscribers time to connect (PUB/SUB slow joiner)
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    // while (1) {

    //     int zipcode, temperature, relhumidity;

    //     //  Get values that will fool the boss
    //     zipcode     = within (100000);
    //     temperature = within (215) - 80;
    //     relhumidity = within (50) + 10;

    //     //  Send message to all subscribers
    //     zmq::message_t message(20);
    //     snprintf ((char *) message.data(), 20 ,
    //     	"%05d %d %d", zipcode, temperature, relhumidity);
    //     publisher.send(message, zmq::send_flags::none);

    // }
    for (int i = 0; i < 10000; i++) {
        std::string s = std::to_string(i);
        zmq::message_t msg(s.data(), s.size());
        publisher.send(msg, zmq::send_flags::none);
        // Slight delay to avoid flooding and to help observation
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}
