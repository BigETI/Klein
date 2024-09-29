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
	GIT_TAG "5.0"
)

FetchContent_MakeAvailable (raylib)
