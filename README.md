# Strumscore

## Building
Run the following to compile the project provided you need JUCE, GTest, a C++23 supported compiler (mainly g++ 14.1, 11.4), ninja, and cmake.
*ninja is optional, make is cmake's default*
```bash
mkdir build
cd build
cmake -GNinja ..    # optional: omit the -GNinja flag
ninja               # optional: enter `make` instead
```

If you want to run clang, with specific rules, run the overrides. Though not complete yet, so not recommended at all.
```
cmake -DCMAKE_USER_MAKE_RULES_OVERRIDE=$PWD/../cmake/clang_overrides.cmake -GNinja ..
```
