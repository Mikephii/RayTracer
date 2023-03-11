1. To install packages using conan 2.0 run 
```conan install . --output-folder=build --build=missing``` from the root directory

2. to build the program: 
```cd build```
```cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release```

```cmake --build . ```

3. to Run the program and see rendered output:
    ```./tinyraytracer```