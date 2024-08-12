cmake_minimum_required(VERSION 3.22)
project(strumscoreSource VERSION 0.0.1)

juce_add_gui_app(strumscore
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "JamesFerrarelli"
    COMPANY_WEBSITE "https://github.com/jsatof"
    PRODUCT_NAME "strumscore")

juce_generate_juce_header(strumscore)

target_sources(strumscore
    PRIVATE
    	main.cpp
    	document.cpp
    	components/main_component.cpp
    	components/menu_bar.cpp
    	components/menu_bar_model.cpp
    	components/staff.cpp)

target_include_directories(strumscore
    PRIVATE
    	${JUCE_SOURCE_DIR}/modules
        .)

target_compile_definitions(strumscore
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:strumscore,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:strumscore,JUCE_VERSION>")

target_link_libraries(strumscore
    PRIVATE
    	juce::juce_audio_utils
        fmt::fmt
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

install(TARGETS strumscore DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
