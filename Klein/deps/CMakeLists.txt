##################
#                #
#  Dependencies  #
#                #
##################

include (FetchContent)

set (FETCHCONTENT_QUIET FALSE)

############
#          #
#  raylib  #
#          #
############

FetchContent_Declare (raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG "5.5"
	GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable (raylib)

if (KLEIN_USE_CXX_STD_17)

	##########
	#        #
	#  span  #
	#        #
	##########

	FetchContent_Declare (span
		GIT_REPOSITORY https://github.com/tcbrindle/span.git
		GIT_TAG "master"
		GIT_SHALLOW TRUE
	)

	FetchContent_MakeAvailable (span)
endif ()
