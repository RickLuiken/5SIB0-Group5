//
// Created by thijslaptop on 19-03-21.
//

#include "Latency.h"


using namespace llvm;


int get_latency(const Instruction *I) {
    if (!I) return 0;

    switch (I->getOpcode()) {
        case Instruction::Ret:
            return 0;
        case Instruction::Br:
            return 0;
        case Instruction::Switch:
            return 0;
        case Instruction::IndirectBr:
            return 0;
        case Instruction::Invoke:
            return 0;
        case Instruction::Resume:
            return 0;
        case Instruction::Unreachable:
            return 0;
        case Instruction::Add:
        case Instruction::Sub:
            return INT_ADD;
        case Instruction::FAdd:
        case Instruction::FSub:
            return FP_ADD;
        case Instruction::Mul:
            return 0;
        case Instruction::FMul:
            return FP_MULT;
        case Instruction::SDiv:
            return 0;
        case Instruction::SRem:
            return 0;
        case Instruction::UDiv:
            return 0;
        case Instruction::URem:
            return 0;
        case Instruction::FDiv:
            return 0;
        case Instruction::FRem:
            return 0;
        case Instruction::Shl:
        case Instruction::LShr:
        case Instruction::AShr:
            return SHIFT;
        case Instruction::And:
        case Instruction::Or:
        case Instruction::Xor:
            return INT_ADD;
        case Instruction::Alloca:
            return 0;
        case Instruction::Load:
            return 0;
        case Instruction::Store:
            return 0;
        case Instruction::GetElementPtr:
            return 0;
        case Instruction::Fence:
            return 0;
        case Instruction::AtomicCmpXchg:
            return 0;
        case Instruction::AtomicRMW:
            return 0;
        case Instruction::Trunc:
            return 0;
        case Instruction::ZExt:
            return 0;
        case Instruction::SExt:
            return 0;
        case Instruction::FPTrunc:
            return 0;
        case Instruction::FPExt:
            return 0;
        case Instruction::PtrToInt:
        case Instruction::IntToPtr:
        case Instruction::BitCast:
            return CAST_LATENCY;
        case Instruction::FPToUI:
        case Instruction::FPToSI:
            return FP_TO_SI;
        case Instruction::UIToFP:
        case Instruction::SIToFP:
            return SI_TO_FP;
        case Instruction::ICmp:
            return ICMP_LATENCY;
        case Instruction::FCmp:
            return FCMP_LATENCY;
        case Instruction::PHI:
            return 0;
        case Instruction::Call:
            return 0;
        case Instruction::Select:
            return 0;
        case Instruction::UserOp1:
            return 0;
        case Instruction::UserOp2:
            return 0;
        case Instruction::VAArg:
            return 0;
        case Instruction::ExtractElement:
            return 0;
        case Instruction::InsertElement:
            return 0;
        case Instruction::ShuffleVector:
            return 0;
        case Instruction::ExtractValue:
            return 0;
        case Instruction::InsertValue:
            return 0;
        case Instruction::LandingPad:
            return 0;
    }
}