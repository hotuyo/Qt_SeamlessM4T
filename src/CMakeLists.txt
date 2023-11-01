find_package(Qt6 REQUIRED COMPONENTS Qml Core Network Sql Widgets)
qt_add_library(TextAnalyse SHARED)
target_link_libraries(TextAnalyse PRIVATE Qt6::Qml Qt6::Core Qt6::Network Qt6::Sql Qt6::Widgets)
qt6_add_qml_module(
	TextAnalyse
	URI
		TextAnalyse
	SOURCES
		textanalyse.cpp
		textanalyse.h
		recorddatabase.h
		recorddatabase.cpp
		SOURCES
)