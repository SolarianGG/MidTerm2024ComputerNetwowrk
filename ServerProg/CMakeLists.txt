CMAKE_MINIMUM_REQUIRED(VERSION 3.16)


add_executable(MidTermServer
	${CMAKE_CURRENT_SOURCE_DIR}/src/stdafx.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/stdafx.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/targetver.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/tcpserver.cpp
)