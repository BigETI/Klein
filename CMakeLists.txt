cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
	cmake_policy (SET CMP0141 NEW)
	set (CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

#####################
#                   #
#  Neo Game Engine  #
#                   #
#####################

project (NGE
	VERSION "0.0.0"
	DESCRIPTION "Neo Game Engine"
)

add_subdirectory ("NGE")

if (NOT NGE_DISABLE_TESTS)

	#########################
	#                       #
	#  Neo Game Unit Tests  #
	#                       #
	#########################

	project (NGETest
		VERSION 1.0.0
		DESCRIPTION "Unit tests for Neo Game Engine"
	)

	add_subdirectory ("NGETest")

endif ()
