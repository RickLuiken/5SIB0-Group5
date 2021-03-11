# Loop unroll pass

Find the loop unroll factors for HLS C programs. Based on [**COMBA**](https://github.com/zjru/COMBA).

## Requirements
- LLVM 10.0 or higher
- CMake 2.8 or higher

## Building
The following can be used to build a shared library (`.so`) plugin for the LLVM opt tool:
- Create a new folder `build`:
```bash
mkdir build
cd build
```

- Create the build system and build the plugin (Make is used):
```bash
cmake .. -DLLVM_ROOT=/mnt/h/llvm/build
make
```

## Testing
Testing can be done (from the build folder) using:
```bash
opt -load-pass-plugin ./lib/LoopUnrollPass.so -passes=loopunroll -disable-output ../test/test.ll
```

