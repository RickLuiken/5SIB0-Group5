#include "Pass.h"
#include "Utils.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

float computeCriticalPath() {

}

float LoopUnrollPass::get_estimated_latencies(loop_unroll_info &L) {
    float inner_impact = 0.0;
	float outer_unroll_factor = L.unroll_factor;
    // TODO: CHANGE THIS TO A FUNCTION CALL
	float outer_critical_path_latency = 10.0;

	errs() << outer_unroll_factor << ", ";

	for (auto &SL : L.sub_loops) {
		float inner_latency = get_estimated_latencies(innerLoop);

		inner_impact += inner_latency * (SL.trip_count / SL.unroll_factor);	
	}
    errs() << std::endl;

	return inner_impact * outer_unroll_factor + outer_critical_path_latency;
}


bool LoopUnrollPass::find_unroll_factors(loop_unroll_info &L, loop_unroll_info &top_loop) {
    for (auto unroll_factor : L.unroll_options) {
        L.unroll_factor = unroll_factor;
        
        for (auto &SL : L.sub_loops) {
            find_unroll_factors(SL, top_loop);
        }

        errs() << "UF: ";

        float latency = estimateLoopLatency(top_loop);

        errs() << "LL: " << latency << std::endl;
    }
}


void LoopUnrollPass::find_unroll_factors() {
    for (auto &L : loops) {
        find_unroll_factors(*L, *L);
    }
}


std::unique_ptr<loop_unroll_info> LoopUnrollPass::set_loop_unroll_info(Loop *L, ScalarEvolution &SE) {
    // find the trip count
    unsigned int trip_count = SE.getSmallConstantTripCount(L);

    // create a smart pointer to the loop unroll info struct
    std::unique_ptr<loop_unroll_info> loop_info(new loop_unroll_info {
            trip_count,
            getPowerVector(trip_count, 2),
            L,
            std::vector<std::unique_ptr<loop_unroll_info>>{}
        }
    );
    for (Loop *SL : L->getSubLoops()) {
        // recursively find subloops
        loop_info->sub_loops.push_back(set_loop_unroll_info(SL, SE));
    }
    return loop_info;
}


void LoopUnrollPass::set_loop_unroll_info(LoopInfo &LI, ScalarEvolution &SE) {
    for (Loop *L : LI) {
        loops.push_back(set_loop_unroll_info(L, SE));
    }
}


PreservedAnalyses LoopUnrollPass::run(Function &F, FunctionAnalysisManager &AM) {
    // get the loop analysis and trip count information
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);

    // set the vector of loop unroll info structs
    set_loop_unroll_info(LI, SE);


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