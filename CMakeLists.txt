cmake_minimum_required(VERSION 3.0)
project(udpPlot)

add_executable(udpPlot wxf_gen/udpPlotBase.cpp main.cpp udpPlot.cpp udpPlotWindow.cpp udpData.cpp)
add_executable(testUdpPlot testUdpPlot.cpp)
find_package(wxWidgets REQUIRED core base)
find_package(jsoncpp)
target_link_libraries(udpPlot ${wxWidgets_LIBRARIES})
#target_link_libraries(udpPlot /usr/lib/codeblocks/wxContribItems/libwxmathplot.so)
target_link_libraries(udpPlot wxmathplot)
target_link_libraries(udpPlot jsoncpp)
include_directories(/usr/include/codeblocks/wxContribItems/wxMathPlot)
include(${wxWidgets_USE_FILE})

INSTALL(TARGETS udpPlot RUNTIME DESTINATION bin COMPONENT Applications)
install(FILES udpPlot.desktop DESTINATION share/applications)
SET(CPACK_PACKAGE_DESCRIPTION "udpPlot")
SET(CPACK_PACKAGE_CONTACT "Cedric Boudinet")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libwxmathplot")
include(CPack)
option(BUILD_UNIT_TEST ON)
if(BUILD_UNIT_TEST)
	ENABLE_TESTING()
	add_subdirectory(tests)
endif()
