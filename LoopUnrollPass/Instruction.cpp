//
// Created by thijslaptop on 19-03-21.
//

#include "Instruction.h"

Instruction(Type type) {
    this.type = type;
}

int getLatency() {
    switch (this.type) {
        case Ret:
            return 0;
        case Br:
            return 0;
        case Switch:
            return 0;
        case IndirectBr:
            return 0;
        case Invoke:
            return 0;
        case Resume:
            return 0;
        case Unreachable:
            return 0;
        case Add:
        case Sub:
            return this.INT_ADD;
        case FAdd:
        case FSub:
            return this.FP_ADD;
        case Mul:
            return 0;
        case FMul:
            return this.FP_MULT;
        case SDiv:
            return 0;
        case SRem:
            return 0;
        case UDiv:
            return 0;
        case URem:
            return 0;
        case FDiv:
            return 0;
        case FRem:
            return 0;
        case Shl:
        case LShr:
        case AShr:
            return this.SHIFT;
        case And:
        case Or:
        case Xor:
            return this.INT_ADD;
        case Alloca:
            return 0;
        case Load:
            return 0;
        case Store:
            return 0;
        case GetElementPtr:
            return 0;
        case Fence:
            return 0;
        case AtomicCmpXchg:
            return 0;
        case AtomicRMW:
            return 0;
        case Trunc:
            return 0;
        case ZExt:
            return 0;
        case SExt:
            return 0;
        case FPTrunc:
            return 0;
        case FPExt:
            return 0;
        case PtrToInt:
        case IntToPtr:
        case BitCast:
            return this.CAST_LATENCY;
        case FPToUI:
        case FPToSI:
            return this.FP_TO_SI;
        case UIToFP:
        case SIToFP:
            return this.SI_TO_FP;
        case ICmp:
            return this.ICMP_LATENCY;
        case FCmp:
            return this.FCMP_LATENCY;
        case PHI:
            return 0;
        case Call:
            return 0;
        case Select:
            return 0;
        case UserOp1:
            return 0;
        case UserOp2:
            return 0;
        case VAArg:
            return 0;
        case ExtractElement:
            return 0;
        case InsertElement:
            return 0;
        case ShuffleVector:
            return 0;
        case ExtractValue:
            return 0;
        case InsertValue:
            return 0;
        case LandingPad:
            return 0;
    }
}