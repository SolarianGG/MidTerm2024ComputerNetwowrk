CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

add_executable(MidTermClient
	${CMAKE_CURRENT_SOURCE_DIR}/src/ConsoleApplication_ConsoleGame.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/KInput.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/KInput.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/MyUtil.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/MyUtil.h
)