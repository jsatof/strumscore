cmake_minimum_required(VERSION 3.22)
project(strumscoreTest)
enable_testing()

# static library of sources
add_library(strumscoreStatic
	STATIC
		../src/components/main_component.cpp
		../src/components/menu_bar.cpp
		../src/components/menu_bar_model.cpp
		../src/document.cpp)

target_include_directories(strumscoreStatic
    PRIVATE
    	${PROJECT_SOURCE_DIR}/../src
    	${PROJECT_SOURCE_DIR}/src
        ${JUCE_SOURCE_DIR}/modules)

target_compile_definitions(strumscoreStatic
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:strumscoreStatic,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:strumscoreStatic,JUCE_VERSION>")

target_link_libraries(strumscoreStatic
    PRIVATE
        fmt::fmt
        GTest::gtest_main
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

install(TARGETS strumscoreStatic DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# test runner
add_executable(strumscoreTest
    src/audio_processor_test.cpp
    src/main_component_test.cpp)

target_include_directories(strumscoreTest
    PRIVATE
    	${PROJECT_SOURCE_DIR}/../src
    	${PROJECT_SOURCE_DIR}/src
        ${JUCE_SOURCE_DIR}/modules)

target_compile_definitions(strumscoreTest
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:strumscoreTest,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:strumscoreTest,JUCE_VERSION>")

target_link_libraries(strumscoreTest
    PRIVATE
        fmt::fmt
        GTest::gtest_main
        juce::juce_audio_utils
        strumscoreStatic
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

install(TARGETS strumscoreTest DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_target(test COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/strumscoreTest)
