cmake_minimum_required(VERSION 2.8)


file(GLOB ai2_SRC
	"src/*.h"
	"src/*.cpp"
)

add_executable(ai2 ${ai2_SRC})

if (WIN32)
	LINK_DIRECTORIES(C:/lib/SDL2/lib/x86)
	INCLUDE_DIRECTORIES(C:/lib/SDL2/include)
endif(WIN32)

target_link_libraries(ai2 SDL2 SDL2main)
