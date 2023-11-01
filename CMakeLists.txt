cmake_minimum_required(VERSION 3.14)

project(translator LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets Qml Sql Gui Core NetWork Widgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
qt_standard_project_setup()

qt_add_executable(translator
  main.cpp
)

qt_add_qml_module(
	${CMAKE_PROJECT_NAME}
	URI "Main"
	QML_FILES
		main.qml
		MainWindow.qml
		HistoryMessageDialog.qml
)

add_subdirectory(src)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
		TextAnalyse# SHARED
		#TextAnalyseplugin # STATIC LIBS
)
target_link_libraries(translator PRIVATE
											Qt6::Core
											Qt6::Qml
											Qt6::Widgets
											Qt6::Network
											Qt6::Sql
											Qt6::Gui
											Qt6::Widgets)

set_target_properties(translator PROPERTIES
		MACOSX_BUNDLE TRUE
		WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS translator
								BUNDLE DESTINATION .
								LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
								RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)