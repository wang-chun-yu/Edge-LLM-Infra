cmake_minimum_required(VERSION 3.10)
project(zmq_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include_directories("../hybrid-comm/include/libzmq")

function(add_zmq_example target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} zmq)
endfunction()

add_zmq_example(hwclient hwclient.cpp)
add_zmq_example(hwserver hwserver.cpp)
add_zmq_example(wuclient wuclient.cpp)
add_zmq_example(wuserver wuserver.cpp)
add_zmq_example(taskvent taskvent.cpp)
add_zmq_example(taskwork taskwork.cpp)
add_zmq_example(tasksink tasksink.cpp)