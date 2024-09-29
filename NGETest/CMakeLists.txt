################################
#                              #
#  Neo Game Engine Unit Tests  #
#                              #
################################

# TODO: Add tests properly

add_executable (NGETest
	"src/main.cpp"
	"src/Tests/Math/Vector2Tests.cpp"
)

target_compile_features (NGETest
	PRIVATE cxx_std_20
)

set_property (TARGET NGETest
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_include_directories (NGETest
	PRIVATE "deps/lest/include"
	PRIVATE "include"
)

target_link_libraries (NGETest
	PRIVATE NGEStatic
)
