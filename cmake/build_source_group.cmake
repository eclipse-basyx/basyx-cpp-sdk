###############################################
###          build_source_group             ###
###############################################
###
### Builds a source group from a set of files
### for nicer display in IDEs
###


function( build_source_group target_name)
	get_target_property("sources" ${target_name} "SOURCES")

	set(local_files)
	foreach(_file ${sources})
		string(FIND ${_file} "${CMAKE_CURRENT_SOURCE_DIR}" found)
		if(NOT found EQUAL -1)
			list(APPEND local_files ${_file})
		endif()
	endforeach()

	set(include_files)
	foreach(_file ${sources})
		string(FIND ${_file} "${BASYX_INCLUDE_DIR}" found)
		if(NOT found EQUAL -1)
			list(APPEND include_files ${_file})
		endif()
	endforeach()

	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "[src]" FILES ${local_files})
	source_group(TREE "${BASYX_INCLUDE_DIR}/BaSyx" PREFIX "[include]" FILES ${include_files})
endfunction()