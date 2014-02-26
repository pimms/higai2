cmake_minimum_required(VERSION 2.8)


file(GLOB ai2_SRC
	"src/*.h"
	"src/*.cpp"
)

# This may not work for VS. Fuck the police.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (WIN32)
	LINK_DIRECTORIES(C:/lib/SDL2/lib/x86)
	INCLUDE_DIRECTORIES(C:/lib/SDL2/include)
endif(WIN32)

add_executable(ai2 ${ai2_SRC})
target_link_libraries(ai2 SDL2)
