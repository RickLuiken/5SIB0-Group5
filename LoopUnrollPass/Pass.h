#ifndef LLVM_5SIB0_PASS_H
#define LLVM_5SIB0_PASS_H

#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"

class LoopUnrollPass : public llvm::PassInfoMixin<LoopUnrollPass> {
    void print_loop_trip_count(llvm::Loop *L, llvm::ScalarEvolution &SE);
    void print_loop_trip_count(llvm::LoopInfo &LI, llvm::ScalarEvolution &SE);
public:
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &AM);
};

#endif