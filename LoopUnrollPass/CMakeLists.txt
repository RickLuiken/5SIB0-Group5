add_llvm_library( LoopUnrollPass MODULE
  Pass.cpp
  Utils.cpp

  PLUGIN_TOOL
  opt
)