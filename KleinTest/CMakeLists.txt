#################
#               #
#  Klein Tests  #
#               #
#################

# TODO: Add tests properly

add_executable (KleinTest
	"src/main.cpp"
	"src/Tests/Collections/GridTests.cpp"
	"src/Tests/Math/Vector2Tests.cpp"
)

set_property (TARGET KleinTest
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_compile_features (KleinTest
	PRIVATE cxx_std_23
)

target_include_directories (KleinTest
	PRIVATE "deps/lest/include"
	PRIVATE "include"
)

target_link_libraries (KleinTest
	PRIVATE KleinStatic
)
