//
// Created by thijslaptop on 19-03-21.
//
#ifndef LOOPUNROLLPASS_INSTRUCTION_H
#define LOOPUNROLLPASS_INSTRUCTION_H

#include "llvm/IR/Instruction.h"


float compute_critical_path_latency(llvm::BasicBlock &BB);
float get_instruction_latency(llvm::Instruction *I);

static const float INT_ADD = 0.2;
static const float INT_MULT = 1.4;    //actual 1.0, cannot chain with load and store. cannot chain with small operations either.
static const float IMULT = 6.0;       //actual 6.0, can chain with load and store, also small operations. not small and store/load together. not other large operations.
static const float INT_DIV = 7.0;    //actual 7.0, same with imult.
static const float IDIV = 34.0;      //actual 36.0, same with imult, but can chain with small and store together. not chain with other large operations.
static const float U_DIV = 6.0;
static const float UDIV = 34.0;
static const float FP_ADD = 4.0;    //not chain
static const float FP_MULT = 3.0;    //not chain
static const float FP_DIV = 10.0;    //not chain
static const float SI_TO_FP = 4.0;    //can chain
static const float FP_TO_SI = 1.0;
static const float SHIFT = 0.05;
static const float ALLOCA_LATENCY = 1.0;
static const float GEP_LATENCY = 0.0;
static const float CAST_LATENCY = 0.2;
static const float PHI_LATENCY = 1.5; //1.0
static const float ICMP_LATENCY = 0.15;
static const float FCMP_LATENCY = 4.0;
static const float SELECT_LATENCY = 0.05;
static const float CALL_LATENCY = 1.0;


#endif //LOOPUNROLLPASS_INSTRUCTION_H
