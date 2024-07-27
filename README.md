# Strumscore

## Building
Run the following to compile the project provided you have a C++23 supported compiler (I use gnu14.1), ninja, and cmake.
```bash
mkdir build
cd build
cmake -GNinja ..
```

If you want to run clang, with specific rules, run the overrides. Though not complete yet, so not recommended at all.
```
cmake -DCMAKE_USER_MAKE_RULES_OVERRIDE=$PWD/../cmake/clang_overrides.cmake -GNinja ..
```
