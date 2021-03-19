//
// Created by thijslaptop on 19-03-21.
//

#ifndef LOOPUNROLLPASS_INSTRUCTION_H
#define LOOPUNROLLPASS_INSTRUCTION_H


class Instruction {
public:
    enum class Type {
        Ret,
        Br,
        Switch,
        IndirectBr,
        Invoke,
        Resume,
        Unreachable,
        Add,
        Sub,
        FAdd,
        FSub,
        Mul,
        FMul,
        SDiv,
        SRem,
        UDiv,
        URem,
        FDiv,
        FRem,
        Shl,
        LShr,
        AShr,
        And,
        Or,
        Xor,
        Alloca,
        Load,
        Store,
        GetElementPtr,
        Fence,
        AtomicCmpXchg,
        AtomicRMW,
        Trunc,
        ZExt,
        SExt,
        FPTrunc,
        FPExt,
        PtrToInt,
        IntToPtr,
        BitCast,
        FPToUI,
        FPToSI,
        UIToFP,
        SIToFP,
        ICmp,
        FCmp,
        PHI,
        Call,
        Select,
        UserOp1,
        UserOp2,
        VAArg,
        ExtractElement,
        InsertElement,
        ShuffleVector,
        ExtractValue,
        InsertValue,
        LandingPad
    };


private:
    enum class Latency {
        INT_ADD = 0.2,
        INT_MULT 1.4    //actual 1.0, cannot chain with load and store. cannot chain with small operations either.
        IMULT 6.0       //actual 6.0, can chain with load and store, also small operations. not small and store/load together. not other large operations.
        INT_DIV  7.0    //actual 7.0, same with imult.
        IDIV  34.0      //actual 36.0, same with imult, but can chain with small and store together. not chain with other large operations.
        U_DIV 6.0
        UDIV  34.0
        FP_ADD   4.0    //not chain
        FP_MULT  3.0    //not chain
        FP_DIV  10.0    //not chain
        SI_TO_FP 4.0    //can chain
        FP_TO_SI 1.0
        SHIFT 0.05
        ALLOCA_LATENCY 1.0
        GEP_LATENCY 0.0
        CAST_LATENCY 0.2
        PHI_LATENCY 1.5//1.0
        ICMP_LATENCY 0.15
        FCMP_LATENCY 4.0
        SELECT_LATENCY 0.05
        CALL_LATENCY 1.0
    };

    Type type;
};


#endif //LOOPUNROLLPASS_INSTRUCTION_H
