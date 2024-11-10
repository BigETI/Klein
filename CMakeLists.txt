cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
	cmake_policy (SET CMP0141 NEW)
	set (CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

###########
#         #
#  Klein  #
#         #
###########

project (Klein
	VERSION "0.0.0"
	DESCRIPTION "Klein"
)

add_subdirectory ("Klein")

if (NOT KLEIN_DISABLE_TESTS)

	################
	#              #
	#  Klein Test  #
	#              #
	################

	project (KleinTest
		VERSION 1.0.0
		DESCRIPTION "Tests for Klein"
	)

	add_subdirectory ("KleinTest")

endif ()
