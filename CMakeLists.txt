cmake_minimum_required(VERSION 3.10) 	

project(TRAVELLING_C_AG VERSION 0.0.1) 	

set(CMake_C_FLAGS "-std=c99") 			


add_library(							
		temp_lib						
		header.h
		library.c

	)

add_executable(travelling_c_ag main.c) 		


target_link_libraries(travelling_c_ag PRIVATE temp_lib)		
										







