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
            break;
        case Br:
            break;
        case Switch:
            break;
        case IndirectBr:
            break;
        case Invoke:
            break;
        case Resume:
            break;
        case Unreachable:
            break;
        case Add:
            break;
        case Sub:
            break;
        case FAdd:
            break;
        case FSub:
            break;
        case Mul:
            break;
        case FMul:
            break;
        case SDiv:
            break;
        case SRem:
            break;
        case UDiv:
            break;
        case URem:
            break;
        case FDiv:
            break;
        case FRem:
            break;
        case Shl:
            break;
        case LShr:
            break;
        case AShr:
            break;
        case And:
            break;
        case Or:
            break;
        case Xor:
            break;
        case Alloca:
            break;
        case Load:
            break;
        case Store:
            break;
        case GetElementPtr:
            break;
        case Fence:
            break;
        case AtomicCmpXchg:
            break;
        case AtomicRMW:
            break;
        case Trunc:
            break;
        case ZExt:
            break;
        case SExt:
            break;
        case FPTrunc:
            break;
        case FPExt:
            break;
        case PtrToInt:
            break;
        case IntToPtr:
            break;
        case BitCast:
            break;
        case FPToUI:
            break;
        case FPToSI:
            break;
        case UIToFP:
            break;
        case SIToFP:
            break;
        case ICmp:
            break;
        case FCmp:
            break;
        case PHI:
            break;
        case Call:
            break;
        case Select:
            break;
        case UserOp1:
            break;
        case UserOp2:
            break;
        case VAArg:
            break;
        case ExtractElement:
            break;
        case InsertElement:
            break;
        case ShuffleVector:
            break;
        case ExtractValue:
            break;
        case InsertValue:
            break;
        case LandingPad:
            break;
    }
}