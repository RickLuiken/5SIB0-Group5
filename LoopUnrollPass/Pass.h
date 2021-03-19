#ifndef LLVM_5SIB0_PASS_H
#define LLVM_5SIB0_PASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"


struct loop_unroll_info {
    int trip_count;
    std::vector<int> unroll_options;
    int unroll_factor;
    llvm::Loop *loop;
    std::vector<std::unique_ptr<loop_unroll_info>> sub_loops;
};


class LoopUnrollPass : public llvm::PassInfoMixin<LoopUnrollPass> {
    std::vector<std::unique_ptr<loop_unroll_info>> loops;


    /**
     * Find the unroll factors for the loops with the least amount of latency
     */
    void find_unroll_factors();


    /**
     * Find the trip count of loops and fill the loop unroll info structs
     * Returns a unique pointer to the newly created struct
     */
    std::unique_ptr<loop_unroll_info> set_loop_unroll_info(llvm::Loop *L, llvm::ScalarEvolution &SE);

    /**
     * Create a vector of pointers to loop unroll info structs
     */
    void set_loop_unroll_info(llvm::LoopInfo &LI, llvm::ScalarEvolution &SE);
public:

    /**
     * Entry point of the pass.
     */
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &AM);
};

#endif