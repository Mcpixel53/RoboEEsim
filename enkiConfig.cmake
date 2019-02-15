# - Config file for the enki package
# It defines the following variables
# enki_INCLUDE_DIR - include directories for enki
# enki_LIBRARY - core library to link against
# enki_VIEWER_LIBRARIES - viewer library to link against, if available

include(FindPackageHandleStandardArgs)

# core
find_path(enki_INCLUDE_DIR enki/PhysicalEngine.h /media/Cousas/git/robosim CMAKE_FIND_ROOT_PATH_BOTH)
find_library(enki_LIBRARY enki /media/Cousas/git/robosim/enki CMAKE_FIND_ROOT_PATH_BOTH)
find_package_handle_standard_args(enki DEFAULT_MSG enki_INCLUDE_DIR enki_LIBRARY)

# viewer
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
if (Qt5Widgets_FOUND AND Qt5OpenGL_FOUND)
	if (CMAKE_HOST_UNIX)
		add_definitions("-fPIC")
	endif (CMAKE_HOST_UNIX)

	find_library(enki_VIEWER_LIBRARY enkiviewer /media/Cousas/git/robosim/viewer CMAKE_FIND_ROOT_PATH_BOTH)
	set(enki_VIEWER_LIBRARIES ${enki_VIEWER_LIBRARY} Qt5::OpenGL Qt5::Widgets CACHE STRING "All libraries necessary to link Enki viewer")
	find_package_handle_standard_args(enki_VIEWER DEFAULT_MSG enki_VIEWER_LIBRARIES)
endif ()
