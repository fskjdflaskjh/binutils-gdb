	.SPACE $PRIVATE$
	.SUBSPA $DATA$,QUAD=1,ALIGN=8,ACCESS=31
	.SUBSPA $BSS$,QUAD=1,ALIGN=8,ACCESS=31,ZERO,SORT=82
	.SPACE $TEXT$
	.SUBSPA $LIT$,QUAD=0,ALIGN=8,ACCESS=44
	.SUBSPA $CODE$,QUAD=0,ALIGN=8,ACCESS=44,CODE_ONLY

	.SPACE $TEXT$
	.SUBSPA $CODE$

	.align 4
; Basic immediate instruction tests.  
;
; We could/should test some of the corner cases for register and 
; immediate fields.  We should also check the assorted field
; selectors to make sure they're handled correctly.
	extrw,u %r4,5,10,%r6
	extrw,u,= %r4,5,10,%r6
	extrw,u,< %r4,5,10,%r6
	extrw,u,od %r4,5,10,%r6
	extrw,u,tr %r4,5,10,%r6
	extrw,u,<> %r4,5,10,%r6
	extrw,u,>= %r4,5,10,%r6
	extrw,u,ev %r4,5,10,%r6

	extrw,s %r4,5,10,%r6
	extrw,s,= %r4,5,10,%r6
	extrw,s,< %r4,5,10,%r6
	extrw,s,od %r4,5,10,%r6
	extrw,tr %r4,5,10,%r6
	extrw,<> %r4,5,10,%r6
	extrw,>= %r4,5,10,%r6
	extrw,ev %r4,5,10,%r6

	extrw,u %r4,%sar,5,%r6
	extrw,u,= %r4,%sar,5,%r6
	extrw,u,< %r4,%sar,5,%r6
	extrw,u,od %r4,%sar,5,%r6
	extrw,u,tr %r4,%sar,5,%r6
	extrw,u,<> %r4,%sar,5,%r6
	extrw,u,>= %r4,%sar,5,%r6
	extrw,u,ev %r4,%sar,5,%r6
	
	extrw,s %r4,%sar,5,%r6
	extrw,s,= %r4,%sar,5,%r6
	extrw,s,< %r4,%sar,5,%r6
	extrw,s,od %r4,%sar,5,%r6
	extrw,tr %r4,%sar,5,%r6
	extrw,<> %r4,%sar,5,%r6
	extrw,>= %r4,%sar,5,%r6
	extrw,ev %r4,%sar,5,%r6
