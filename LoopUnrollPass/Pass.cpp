#include "Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;


void LoopUnrollPass::print_loop_trip_count(Loop *L, ScalarEvolution &SE) {
    unsigned int trip_count = SE.getSmallConstantTripCount(L);
    errs() << "Loop at depth " << L->getLoopDepth();
    if (trip_count == 0) {
        // loop trip count cannot be analyzed
        errs() << " does not have a constant trip count\n";
    } else {
        errs() << " has trip count " << SE.getSmallConstantTripCount(L) << "\n";
    }
    for (Loop *SL : L->getSubLoops()) {
        // recursively find subloops and print the trip count
        print_loop_trip_count(SL, SE);
    }
}


void LoopUnrollPass::print_loop_trip_count(LoopInfo &LI, ScalarEvolution &SE) {
    for (Loop *L : LI) {
        print_loop_trip_count(L, SE);
    }
}

/**
 * Entry point of the pass.
 */
PreservedAnalyses LoopUnrollPass::run(Function &F, FunctionAnalysisManager &AM) {
    // get the loop analysis and trip count information
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
    print_loop_trip_count(LI, SE);
    return PreservedAnalyses::all();
}


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