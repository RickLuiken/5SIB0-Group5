//
// Created by thijslaptop on 19-03-21.
//

#include "Latency.h"
#include "Utils.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;


float get_instruction_latency(const Instruction *I) {
    if (!I) return 0;

    switch (I->getOpcode()) {
        // Terminator instructions
        case Instruction::Ret:
        case Instruction::Br:
        case Instruction::Switch:
        case Instruction::IndirectBr:
        case Instruction::Invoke:
        case Instruction::Resume:
        case Instruction::Unreachable:
            return 0.0;
        
        // Binary operators
        case Instruction::Add:
        case Instruction::Sub:
            return INT_ADD;
        case Instruction::FAdd:
        case Instruction::FSub:
            return FP_ADD;
        case Instruction::Mul: {
            Value *multiplier_op = I->getOperand(1);
            if (auto *const_val_ptr = dyn_cast<ConstantInt>(multiplier_op)) {
                int const_val = const_val_ptr->getSExtValue();
                if (is_power_of_2(const_val)) {
                    // a shift will be used
                    return SHIFT;
                } else {
                    const_val = const_val < 0 ? -const_val : const_val;
                    int power_bound = closest_power_of_2(const_val);
                    int delta = const_val - power_bound;
                    delta = delta < 0 ? -delta : delta;
                    if (is_power_of_2(delta)) {
                        return SHIFT+INT_ADD;
                    } else {
                        return INT_MULT;
                    }
                }
            } else {
                // a mulitiplication has to be used
                return IMULT;
            }
        }
        case Instruction::FMul:
            return FP_MULT;
        case Instruction::SDiv:
        case Instruction::SRem: {
            Value *divider_op = I->getOperand(1);
            if (auto *const_val_ptr = dyn_cast<ConstantInt>(divider_op)) {
                int const_val = const_val_ptr->getSExtValue();
                if (is_power_of_2(const_val)) {
                    return SELECT_LATENCY + 2 * INT_ADD;
                }
            } else {
                return IDIV;
            }
        }
        case Instruction::UDiv:
        case Instruction::URem: {
            Value *divider_op = I->getOperand(1);
            if (auto *const_val_ptr = dyn_cast<ConstantInt>(divider_op)) {
                int const_val = const_val_ptr->getSExtValue();
                if (is_power_of_2(const_val)) {
                    return SELECT_LATENCY + 2 * INT_ADD;
                }
            } else {
                return U_DIV;
            }
        }
        case Instruction::FDiv:
        case Instruction::FRem:
            return FP_DIV;

        // Logical operators
        case Instruction::Shl:
        case Instruction::LShr:
        case Instruction::AShr:
            return SHIFT;
        case Instruction::And:
        case Instruction::Or:
        case Instruction::Xor:
            return INT_ADD;
        case Instruction::Alloca:
            return ALLOCA_LATENCY;

        // these are done seperately somewhere else
        case Instruction::Load:
            return 20.0;
        case Instruction::Store:
            return 20.0;

        case Instruction::GetElementPtr:
            return GEP_LATENCY;

        case Instruction::Fence:
        case Instruction::AtomicCmpXchg:
        case Instruction::AtomicRMW:
            return 0.0;

        // Cast operators
        case Instruction::Trunc:
        case Instruction::ZExt:
        case Instruction::SExt:
        case Instruction::FPTrunc:
        case Instruction::FPExt:
            return 0.0;
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

        // Other operators
        case Instruction::ICmp:
            return ICMP_LATENCY;
        case Instruction::FCmp:
            return FCMP_LATENCY;
        case Instruction::PHI:
            return PHI_LATENCY;
        case Instruction::Call:
            return 0.0;
        case Instruction::Select:
            return SELECT_LATENCY;

        case Instruction::UserOp1:
        case Instruction::UserOp2:
        case Instruction::VAArg:
        case Instruction::ExtractElement:
        case Instruction::InsertElement:
        case Instruction::ShuffleVector:
        case Instruction::ExtractValue:
        case Instruction::InsertValue:
        case Instruction::LandingPad:
            return 0.0;
        
        default:
            errs() << "An instruction could not be handled\n";
            I->dump();
            exit(0);
    }
}