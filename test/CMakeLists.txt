cmake_minimum_required(VERSION 3.22)
project(strumscoreTest)
enable_testing()

add_executable(${PROJECT_NAME}
    src/audio_processor_test.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${GTEST_SOURCE_DIR}/googletest/include
        ${PROJECT_SOURCE_DIR}/../plugin/include
        ${JUCE_SOURCE_DIR}/modules)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        strumscore
        GTest::gtest_main)
