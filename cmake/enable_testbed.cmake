###############################################
###          enable_testbed                 ###
###############################################
###
### Load instructions from a testing.cmake file
### This can be used, to create build targets
### for testing purposes
###

function( enable_testbed )
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/testbed.cmake")
		include("${CMAKE_CURRENT_SOURCE_DIR}/testbed.cmake")
	endif()
endfunction()