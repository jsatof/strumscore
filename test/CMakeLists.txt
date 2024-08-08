cmake_minimum_required(VERSION 3.22)
project(strumscoreTest)
enable_testing()

add_executable(strumscoreTest
    	src/audio_processor_test.cpp)

target_include_directories(strumscoreTest
    PRIVATE
        ${GTEST_SOURCE_DIR}/googletest/include
        ${JUCE_INCLUDE_DIRS})

target_compile_definitions(strumscore
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:strumscore,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:strumscore,JUCE_VERSION>")

target_link_libraries(strumscoreTest
    PRIVATE
        GTest::gtest_main)

target_link_libraries(strumscore
    PRIVATE
        juce::juce_audio_utils
        fmt::fmt
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

install(TARGETS strumscoreTest DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_target(test COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/strumscoreTest)
