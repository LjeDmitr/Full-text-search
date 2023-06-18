set(target_name fts-c)
set(JAVA_HOME $ENV{JAVA_HOME})

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
	${JAVA_HOME}/include
	if(WIN32)
    	${JAVA_HOME}/include/win32
	else()
    	${JAVA_HOME}/include/linux
	endif()
)

target_link_libraries(
	${target_name} 
	PUBLIC 
	  index
	  search
    rapidcsv
)