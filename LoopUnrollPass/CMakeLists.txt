add_llvm_library( LoopUnrollPass MODULE
  Pass.cpp
  Utils.cpp
  Latency.cpp

  PLUGIN_TOOL
  opt
)