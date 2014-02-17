cmake_minimum_required(VERSION 2.8)

file(GLOB ai2_SRC
	"src/*.h"
	"src/*.cpp"
)

add_executable(ai2 ${ai2_SRC})
