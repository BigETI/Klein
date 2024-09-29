#####################
#                   #
#  Neo Game Engine  #
#                   #
#####################

add_subdirectory ("deps")

#################################
#                               #
#  Statically linkable library  #
#                               #
#################################

add_library (NGEStatic STATIC
	"src/Engine.cpp"
	"src/EventSystem/ObserverID.cpp"
	"src/InputSystem/InputEvent.cpp"	
	"src/InputSystem/Raylib/RaylibGamepadInputEvents.cpp"
	"src/InputSystem/Raylib/RaylibInputHandler.cpp"
	"src/Rendering/Raylib/RaylibWindowRenderer.cpp"
	"src/Rendering/RenderingContext.cpp"
	"src/Rendering/RenderingContextElement.cpp"
	"src/ResourceManagement/FileSystem.cpp"
	"src/ResourceManagement/Raylib/RaylibTexture2DResourceManager.cpp"
	"src/SceneManagement/Node.cpp"
	"src/Scripting/Rendering/CameraScript.cpp"
	"src/Scripting/Rendering/SpriteRendererScript.cpp"
	"src/Scripting/Script.cpp"
)

set_property (TARGET NGEStatic
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_compile_features (NGEStatic
	PRIVATE cxx_std_23
)

target_compile_definitions (NGEStatic
	PUBLIC IS_NGE_STATIC
)

target_include_directories (NGEStatic
	PUBLIC "include"
)

target_link_libraries (NGEStatic
	PUBLIC raylib
)

##################################
#                                #
#  Dynamically linkable library  #
#                                #
##################################

add_library (NGE SHARED
	"src/Engine.cpp"
	"src/EventSystem/ObserverID.cpp"
	"src/InputSystem/InputEvent.cpp"	
	"src/InputSystem/Raylib/RaylibGamepadInputEvents.cpp"
	"src/InputSystem/Raylib/RaylibInputHandler.cpp"
	"src/Rendering/Raylib/RaylibWindowRenderer.cpp"
	"src/Rendering/RenderingContext.cpp"
	"src/Rendering/RenderingContextElement.cpp"
	"src/ResourceManagement/FileSystem.cpp"
	"src/ResourceManagement/Raylib/RaylibTexture2DResourceManager.cpp"
	"src/SceneManagement/Node.cpp"
	"src/Scripting/Rendering/CameraScript.cpp"
	"src/Scripting/Rendering/SpriteRendererScript.cpp"
	"src/Scripting/Script.cpp"
)

target_compile_features (NGE
	PRIVATE cxx_std_23
)

set_property (TARGET NGE
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_link_libraries (NGE
#	PUBLIC magic_enum
	PUBLIC raylib
)

target_compile_definitions (NGE
	PUBLIC IS_NGE_EXPORTING
)

include_directories (NGE
	PUBLIC "include"
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options (NGE
		PRIVATE -fPIC
	)
	add_compile_options (-fPIC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
endif ()
