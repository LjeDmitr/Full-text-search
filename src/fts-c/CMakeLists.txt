set(target_name fts-c)

add_library(${target_name} SHARED
  Fts.cpp
  ${CMAKE_SOURCE_DIR}/include/fts-c/Fts.h
)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
  	${CMAKE_SOURCE_DIR}/include
	/opt/jdk1.8.0_331/include
	/opt/jdk1.8.0_331/include/linux
)

target_link_libraries(
	${target_name} 
	PUBLIC 
	  index
	  search
    rapidcsv
)