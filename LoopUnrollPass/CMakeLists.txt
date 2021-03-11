add_llvm_library( LoopUnrollPass MODULE
  Pass.cpp

  PLUGIN_TOOL
  opt
)