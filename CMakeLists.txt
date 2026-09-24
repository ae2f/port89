cmake_minimum_required(VERSION 3.10)

project(port89 LANGUAGES C)

# Set this source directory as the tree root for project.
set(ae2f_ProjRoot ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Tree root for project")
set(ae2f_BinRoot ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "Tree root for project")
set(ae2f_submod  .submod CACHE STRING "Relative path to submodule (subdirectory)")
set(ae2f_CoreScript_Wh ${ae2f_ProjRoot}/${ae2f_submod}/ae2f/CoreScript)
set(ae2f_host "http://talkischeap.work.gd/" CACHE STRING "Default git host for fetching.")

# Execute git to fetch CoreScript when repository does not exist
if(NOT EXISTS ${ae2f_CoreScript_Wh})
	execute_process(
		COMMAND git clone ${ae2f_host}/ae2f/CoreScript
		${ae2f_CoreScript_Wh}
		)
endif()

# add subdirectory
if(NOT TARGET ae2f::CoreScript)
	add_subdirectory(${ae2f_CoreScript_Wh} ${ae2f_BinRoot}/${ae2f_submod}/ae2f/CoreScript)
endif()

ae2f_CoreLibFetch(ae2f Core main)

file(GLOB_RECURSE port89_src app/*)
add_executable(port89 ${port89_src})
target_link_libraries(port89 PRIVATE ae2f::Core)


ae2f_UltraErrWERROR(port89 PRIVATE)
