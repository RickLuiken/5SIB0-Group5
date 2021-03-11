#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
class LoopUnrollPass : public PassInfoMixin<LoopUnrollPass> {
public:
    /**
     * Entry point of the pass.
     */
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
        errs() << "Hello from: "<< F.getName() << "\n";
        return PreservedAnalyses::all();
    }
};
} // end of namespace


//-----------------------------------------------------------------------------
// Pass Mananger registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getLoopUnrollPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "LoopUnroll", "v0.1",
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "loopunroll") {
                    FPM.addPass(LoopUnrollPass());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLoopUnrollPluginInfo();
}