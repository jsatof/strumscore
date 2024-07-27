cmake_minimum_required(VERSION 3.22)
project(strumscore VERSION 0.0.1)

juce_add_plugin(strumscore
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
    	main_component.cpp)

target_include_directories(strumscore
    PRIVATE
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
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
