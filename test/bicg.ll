; ModuleID = 'bicg.c'
source_filename = "bicg.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nofree norecurse nounwind uwtable
define dso_local void @kernel_bicg([32 x i32]* nocapture readonly %A, i32* nocapture %s, i32* nocapture %q, i32* nocapture readonly %p, i32* nocapture readonly %r) local_unnamed_addr #0 {
entry:
  br label %for.cond1.preheader

for.cond1.preheader:                              ; preds = %for.inc24, %entry
  %indvars.iv48 = phi i64 [ 0, %entry ], [ %indvars.iv.next49, %for.inc24 ]
  %arrayidx5 = getelementptr inbounds i32, i32* %r, i64 %indvars.iv48
  %arrayidx13 = getelementptr inbounds i32, i32* %q, i64 %indvars.iv48
  br label %for.body3

for.body3:                                        ; preds = %for.body3, %for.cond1.preheader
  %indvars.iv = phi i64 [ 0, %for.cond1.preheader ], [ %indvars.iv.next, %for.body3 ]
  %arrayidx = getelementptr inbounds i32, i32* %s, i64 %indvars.iv
  %0 = load i32, i32* %arrayidx, align 4, !tbaa !2
  %1 = load i32, i32* %arrayidx5, align 4, !tbaa !2
  %arrayidx9 = getelementptr inbounds [32 x i32], [32 x i32]* %A, i64 %indvars.iv48, i64 %indvars.iv
  %2 = load i32, i32* %arrayidx9, align 4, !tbaa !2
  %mul = mul nsw i32 %2, %1
  %add = add nsw i32 %mul, %0
  store i32 %add, i32* %arrayidx, align 4, !tbaa !2
  %3 = load i32, i32* %arrayidx13, align 4, !tbaa !2
  %4 = load i32, i32* %arrayidx9, align 4, !tbaa !2
  %arrayidx19 = getelementptr inbounds i32, i32* %p, i64 %indvars.iv
  %5 = load i32, i32* %arrayidx19, align 4, !tbaa !2
  %mul20 = mul nsw i32 %5, %4
  %add21 = add nsw i32 %mul20, %3
  store i32 %add21, i32* %arrayidx13, align 4, !tbaa !2
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %exitcond = icmp eq i64 %indvars.iv.next, 32
  br i1 %exitcond, label %for.inc24, label %for.body3

for.inc24:                                        ; preds = %for.body3
  %indvars.iv.next49 = add nuw nsw i64 %indvars.iv48, 1
  %exitcond50 = icmp eq i64 %indvars.iv.next49, 32
  br i1 %exitcond50, label %for.end26, label %for.cond1.preheader

for.end26:                                        ; preds = %for.inc24
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
