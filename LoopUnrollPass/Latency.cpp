//
// Created by thijslaptop on 19-03-21.
//

#include "Latency.h"
#include "Utils.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"
#include <map>


using namespace llvm;


float compute_critical_path_latency(BasicBlock& BB) {
    float max_latency = 0;
    std::map<const Instruction *, float> schedule;

    for (Instruction &inst : BB) {
        for (User *user : inst.users()) {
            Instruction *I = dyn_cast<Instruction>(user);
            if (I && I->getParent() == &BB && !isa<PHINode>(I)) {
                float latency = schedule[&inst] + get_instruction_latency(&inst);
                float inst_latency = get_instruction_latency(I);
                if (isa<LoadInst>(&inst)) {
                    // load result is only available after one cycle
                    int load_cycle = std::floor(latency / 10.0);
                    int chain_cycle = std::floor((latency + inst_latency) / 10.0);
                    if (load_cycle != chain_cycle) {
                        latency = std::ceil(latency / 10.0) * 10.0;
                    }
                }
                schedule[I] = std::max(schedule[I], latency);
                max_latency = std::max(max_latency, schedule[I] + inst_latency);
            }
        }
    }

    for (const auto& [inst, t] : schedule) {
        errs() << inst->getOpcodeName() << t << "\n";
    }
    return max_latency;
}



float get_instruction_latency(Instruction *I) {
    if (!I) return 0;

    //errs() << I->getOpcodeName() << "\n";

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
                // a multiplication has to be used
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
            return 13.25;
        case Instruction::Store:
            return 3.25;

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