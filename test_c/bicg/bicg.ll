; ModuleID = './bicg/bicg.c'
source_filename = "./bicg/bicg.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nofree norecurse nounwind uwtable
define dso_local void @kernel_bicg([32 x i32]* nocapture readonly %0, i32* nocapture %1, i32* nocapture %2, i32* nocapture readonly %3, i32* nocapture readonly %4) local_unnamed_addr #0 {
  br label %6

6:                                                ; preds = %5, %27
  %7 = phi i64 [ 0, %5 ], [ %28, %27 ]
  %8 = getelementptr inbounds i32, i32* %4, i64 %7
  %9 = getelementptr inbounds i32, i32* %2, i64 %7
  br label %10

10:                                               ; preds = %6, %10
  %11 = phi i64 [ 0, %6 ], [ %25, %10 ]
  %12 = getelementptr inbounds i32, i32* %1, i64 %11
  %13 = load i32, i32* %12, align 4, !tbaa !2
  %14 = load i32, i32* %8, align 4, !tbaa !2
  %15 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i64 %7, i64 %11
  %16 = load i32, i32* %15, align 4, !tbaa !2
  %17 = mul nsw i32 %16, %14
  %18 = add nsw i32 %17, %13
  store i32 %18, i32* %12, align 4, !tbaa !2
  %19 = load i32, i32* %9, align 4, !tbaa !2
  %20 = load i32, i32* %15, align 4, !tbaa !2
  %21 = getelementptr inbounds i32, i32* %3, i64 %11
  %22 = load i32, i32* %21, align 4, !tbaa !2
  %23 = mul nsw i32 %22, %20
  %24 = add nsw i32 %23, %19
  store i32 %24, i32* %9, align 4, !tbaa !2
  %25 = add nuw nsw i64 %11, 1
  %26 = icmp eq i64 %25, 32
  br i1 %26, label %27, label %10, !llvm.loop !6

27:                                               ; preds = %10
  %28 = add nuw nsw i64 %7, 1
  %29 = icmp eq i64 %28, 32
  br i1 %29, label %30, label %6, !llvm.loop !9

30:                                               ; preds = %27
  ret void
}

attributes #0 = { nofree norecurse nounwind uwtable "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 13.0.0 (https://github.com/llvm/llvm-project.git 66e3a4abe99c89cc12cc5818f988d7f3519d5c65)"}
!2 = !{!3, !3, i64 0}
!3 = !{!"int", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C/C++ TBAA"}
!6 = distinct !{!6, !7, !8}
!7 = !{!"llvm.loop.mustprogress"}
!8 = !{!"llvm.loop.unroll.disable"}
!9 = distinct !{!9, !7, !8}
