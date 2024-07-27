```bash
mkdir build
cd build
cmake -DCMAKE_USER_MAKE_RULES_OVERRIDE=$PWD/../cmake/clang_overrides.cmake -GNinja ..
```
