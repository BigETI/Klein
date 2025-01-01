###########
#         #
#  Klein  #
#         #
###########

add_subdirectory ("deps")

#################################
#                               #
#  Statically linkable library  #
#                               #
#################################

add_library (KleinStatic STATIC
	"src/Engine.cpp"
	"src/EventSystem/ObserverID.cpp"
	"src/InputSystem/InputEvent.cpp"
	"src/InputSystem/Raylib/RaylibGamepadInputEvents.cpp"
	"src/InputSystem/Raylib/RaylibInputHandler.cpp"
	"src/Raylib/RaylibEngine.cpp"
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

set_property (TARGET KleinStatic
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_compile_features (KleinStatic
	PRIVATE cxx_std_23
)

target_compile_definitions (KleinStatic
	PUBLIC IS_KLEIN_STATIC
)

target_include_directories (KleinStatic
	PUBLIC "include"
)

target_link_libraries (KleinStatic
	PUBLIC raylib
)

##################################
#                                #
#  Dynamically linkable library  #
#                                #
##################################

add_library (Klein SHARED
	"src/Engine.cpp"
	"src/EventSystem/ObserverID.cpp"
	"src/InputSystem/InputEvent.cpp"
	"src/InputSystem/Raylib/RaylibGamepadInputEvents.cpp"
	"src/InputSystem/Raylib/RaylibInputHandler.cpp"
	"src/Raylib/RaylibEngine.cpp"
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

target_compile_features (Klein
	PRIVATE cxx_std_23
)

set_property (TARGET Klein
	PROPERTY COMPILE_WARNING_AS_ERROR ON
)

target_link_libraries (Klein
	PUBLIC raylib
)

target_compile_definitions (Klein
	PUBLIC IS_KLEIN_EXPORTING
)

include_directories (Klein
	PUBLIC "include"
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options (Klein
		PRIVATE -fPIC
	)
	add_compile_options (-fPIC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
endif ()
