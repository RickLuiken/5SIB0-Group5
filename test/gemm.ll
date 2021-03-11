; ModuleID = 'gemm.c'
source_filename = "gemm.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nofree norecurse nounwind uwtable
define dso_local void @kernel_gemm([16 x i32]* nocapture %C, [16 x i32]* nocapture readonly %A, [16 x i32]* nocapture readonly %B) local_unnamed_addr #0 {
entry:
  br label %for.cond1.preheader

for.cond1.preheader:                              ; preds = %for.inc32, %entry
  %indvars.iv68 = phi i64 [ 0, %entry ], [ %indvars.iv.next69, %for.inc32 ]
  br label %for.body3

for.body3:                                        ; preds = %for.body3, %for.cond1.preheader
  %indvars.iv = phi i64 [ 0, %for.cond1.preheader ], [ %indvars.iv.next, %for.body3 ]
  %arrayidx5 = getelementptr inbounds [16 x i32], [16 x i32]* %C, i64 %indvars.iv68, i64 %indvars.iv
  %0 = load i32, i32* %arrayidx5, align 4, !tbaa !2
  %mul = shl nsw i32 %0, 1
  store i32 %mul, i32* %arrayidx5, align 4, !tbaa !2
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %exitcond = icmp eq i64 %indvars.iv.next, 16
  br i1 %exitcond, label %for.cond9.preheader, label %for.body3

for.cond9.preheader:                              ; preds = %for.body3, %for.inc29
  %indvars.iv65 = phi i64 [ %indvars.iv.next66, %for.inc29 ], [ 0, %for.body3 ]
  %arrayidx15 = getelementptr inbounds [16 x i32], [16 x i32]* %A, i64 %indvars.iv68, i64 %indvars.iv65
  br label %for.body11

for.body11:                                       ; preds = %for.body11, %for.cond9.preheader
  %indvars.iv62 = phi i64 [ 0, %for.cond9.preheader ], [ %indvars.iv.next63, %for.body11 ]
  %1 = load i32, i32* %arrayidx15, align 4, !tbaa !2
  %mul16 = mul nsw i32 %1, 3
  %arrayidx20 = getelementptr inbounds [16 x i32], [16 x i32]* %B, i64 %indvars.iv65, i64 %indvars.iv62
  %2 = load i32, i32* %arrayidx20, align 4, !tbaa !2
  %mul21 = mul nsw i32 %mul16, %2
  %arrayidx25 = getelementptr inbounds [16 x i32], [16 x i32]* %C, i64 %indvars.iv68, i64 %indvars.iv62
  %3 = load i32, i32* %arrayidx25, align 4, !tbaa !2
  %add = add nsw i32 %3, %mul21
  store i32 %add, i32* %arrayidx25, align 4, !tbaa !2
  %indvars.iv.next63 = add nuw nsw i64 %indvars.iv62, 1
  %exitcond64 = icmp eq i64 %indvars.iv.next63, 16
  br i1 %exitcond64, label %for.inc29, label %for.body11

for.inc29:                                        ; preds = %for.body11
  %indvars.iv.next66 = add nuw nsw i64 %indvars.iv65, 1
  %exitcond67 = icmp eq i64 %indvars.iv.next66, 16
  br i1 %exitcond67, label %for.inc32, label %for.cond9.preheader

for.inc32:                                        ; preds = %for.inc29
  %indvars.iv.next69 = add nuw nsw i64 %indvars.iv68, 1
  %exitcond70 = icmp eq i64 %indvars.iv.next69, 16
  br i1 %exitcond70, label %for.end34, label %for.cond1.preheader

for.end34:                                        ; preds = %for.inc32
  ret void
}

attributes #0 = { nofree norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0 (https://github.com/llvm-mirror/clang.git aa231e4be75ac4759c236b755c57876f76e3cf05) (https://github.com/llvm-mirror/llvm.git 2c4ca6832fa6b306ee6a7010bfb80a3f2596f824)"}
!2 = !{!3, !3, i64 0}
!3 = !{!"int", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C/C++ TBAA"}
