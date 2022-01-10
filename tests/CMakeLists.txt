add_executable(udpDataTest udpDataTest.cpp ../udpData.cpp)
target_link_libraries(udpDataTest CppUTest)
add_test(udpDataTest udpDataTest)
