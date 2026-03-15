	.section	.note.gnu.property,"a",@note
	.p2align	3, 0x0
	.long	4
	.long	16
	.long	5
	.asciz	"GNU"
	.long	3221225474
	.long	4
	.long	3
	.p2align	3, 0x0
	.text
	.file	"rt_render_sphere.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function rt_cast_spheres
.LCPI0_0:
	.quad	0x3fe0000000000000              # double 0.5
.LCPI0_1:
	.quad	0xc010000000000000              # double -4
.LCPI0_2:
	.quad	0x8000000000000000              # double -0
	.section	.text.hot.,"ax",@progbits
	.globl	rt_cast_spheres
	.p2align	4
	.type	rt_cast_spheres,@function
rt_cast_spheres:                        # @rt_cast_spheres
	.cfi_startproc
# %bb.0:
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	subq	$352, %rsp                      # imm = 0x160
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movq	%rdx, 88(%rsp)                  # 8-byte Spill
	movq	%rsi, 80(%rsp)                  # 8-byte Spill
	movq	%fs:40, %rax
	movq	%rax, 320(%rsp)
	cmpq	$0, 72(%rdi)
	je	.LBB0_8
# %bb.1:
	movq	%rdi, %r15
	leaq	16(%rbp), %r14
	leaq	32(%r14), %rax
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	movq	80(%rsp), %rax                  # 8-byte Reload
	addq	$32, %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	xorl	%ebx, %ebx
	vmovsd	.LCPI0_0(%rip), %xmm2           # xmm2 = [5.0E-1,0.0E+0]
	xorl	%r12d, %r12d
	movq	80(%rsp), %r13                  # 8-byte Reload
	jmp	.LBB0_2
	.p2align	4
.LBB0_3:                                #   in Loop: Header=BB0_2 Depth=1
	vmovsd	.LCPI0_0(%rip), %xmm2           # xmm2 = [5.0E-1,0.0E+0]
.LBB0_7:                                #   in Loop: Header=BB0_2 Depth=1
	incq	%r12
	addq	$32, %rbx
	cmpq	72(%r15), %r12
	jae	.LBB0_8
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	vmovaps	(%r14), %ymm0
	vmovaps	32(%r14), %ymm1
	vmovaps	%ymm1, 256(%rsp)
	vmovaps	%ymm0, 224(%rsp)
	movq	80(%r15), %rax
	movq	88(%r15), %rcx
	vmulsd	(%rcx,%r12,8), %xmm2, %xmm0
	vmovsd	%xmm0, 72(%rsp)                 # 8-byte Spill
	vmovaps	(%rax,%rbx), %ymm0
	vmovaps	%ymm0, 32(%rsp)
	vmovaps	(%r14), %ymm0
	vmovaps	%ymm0, (%rsp)
	leaq	288(%rsp), %rdi
	vzeroupper
	callq	ft_3dsub@PLT
	leaq	256(%rsp), %rax
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, 32(%rsp)
	vmovapd	288(%rsp), %ymm0
	vmovapd	%ymm0, (%rsp)
	vzeroupper
	callq	ft_3ddot@PLT
	vaddsd	%xmm0, %xmm0, %xmm0
	vmovapd	%xmm0, 112(%rsp)                # 16-byte Spill
	vmovapd	288(%rsp), %ymm0
	vmovapd	%ymm0, 32(%rsp)
	vmovapd	%ymm0, (%rsp)
	vzeroupper
	callq	ft_3ddot@PLT
	vmovsd	72(%rsp), %xmm1                 # 8-byte Reload
                                        # xmm1 = mem[0],zero
	vfnmadd231sd	%xmm1, %xmm1, %xmm0     # xmm0 = -(xmm1 * xmm1) + xmm0
	vmulsd	.LCPI0_1(%rip), %xmm0, %xmm0
	vmovapd	112(%rsp), %xmm1                # 16-byte Reload
	vfmadd231sd	%xmm1, %xmm1, %xmm0     # xmm0 = (xmm1 * xmm1) + xmm0
	vxorpd	%xmm1, %xmm1, %xmm1
	vucomisd	%xmm0, %xmm1
	ja	.LBB0_3
# %bb.4:                                #   in Loop: Header=BB0_2 Depth=1
	vmovsd	%xmm0, 72(%rsp)                 # 8-byte Spill
	callq	ft_drsqrt@PLT
	vmulsd	72(%rsp), %xmm0, %xmm0          # 8-byte Folded Reload
	vmovapd	112(%rsp), %xmm3                # 16-byte Reload
	vxorpd	.LCPI0_2(%rip){1to2}, %xmm3, %xmm1
	vsubsd	%xmm0, %xmm1, %xmm1
	vmovsd	.LCPI0_0(%rip), %xmm2           # xmm2 = [5.0E-1,0.0E+0]
	vmulsd	%xmm2, %xmm1, %xmm1
	vsubsd	%xmm3, %xmm0, %xmm0
	vmulsd	%xmm2, %xmm0, %xmm0
	vxorpd	%xmm3, %xmm3, %xmm3
	vcmpltsd	%xmm1, %xmm3, %k1
	vmovsd	%xmm1, %xmm0, %xmm0 {%k1}
	vucomisd	%xmm3, %xmm0
	jbe	.LBB0_7
# %bb.5:                                #   in Loop: Header=BB0_2 Depth=1
	movq	88(%rsp), %rax                  # 8-byte Reload
	vmovsd	(%rax), %xmm1                   # xmm1 = mem[0],zero
	vucomisd	%xmm0, %xmm1
	jbe	.LBB0_7
# %bb.6:                                #   in Loop: Header=BB0_2 Depth=1
	movq	88(%rsp), %rax                  # 8-byte Reload
	vmovsd	%xmm0, (%rax)
	vmovsd	%xmm0, 96(%r13)
	movq	96(%r15), %rax
	movl	(%rax,%r12,4), %eax
	movl	%eax, 104(%r13)
	vmovsd	%xmm0, 160(%rsp)
	vmovsd	%xmm0, 168(%rsp)
	vmovsd	%xmm0, 176(%rsp)
	movq	$0, 184(%rsp)
	vmovaps	160(%rsp), %ymm0
	vmovaps	%ymm0, 32(%rsp)
	movq	104(%rsp), %rax                 # 8-byte Reload
	vmovaps	(%rax), %ymm0
	vmovaps	%ymm0, (%rsp)
	leaq	192(%rsp), %rdi
	vzeroupper
	callq	ft_3dmul@PLT
	vmovaps	192(%rsp), %ymm0
	vmovaps	%ymm0, 32(%rsp)
	vmovaps	(%r14), %ymm0
	vmovaps	%ymm0, (%rsp)
	leaq	224(%rsp), %r14
	movq	%r14, %rdi
	vzeroupper
	callq	ft_3dadd@PLT
	vmovaps	224(%rsp), %ymm0
	vmovaps	%ymm0, (%r13)
	vmovups	(%r13), %ymm0
	vmovaps	%ymm0, 288(%rsp)
	movq	80(%r15), %rax
	vmovaps	(%rax,%rbx), %ymm0
	vmovaps	%ymm0, 32(%rsp)
	vmovaps	288(%rsp), %ymm0
	vmovaps	%ymm0, (%rsp)
	movq	%r14, %rdi
	leaq	16(%rbp), %r14
	vzeroupper
	callq	ft_3dsub@PLT
	vmovaps	224(%rsp), %ymm0
	vmovaps	%ymm0, (%rsp)
	leaq	128(%rsp), %rdi
	vzeroupper
	callq	ft_3dunit@PLT
	vmovsd	.LCPI0_0(%rip), %xmm2           # xmm2 = [5.0E-1,0.0E+0]
	vmovapd	128(%rsp), %ymm0
	movq	96(%rsp), %rax                  # 8-byte Reload
	vmovapd	%ymm0, (%rax)
	jmp	.LBB0_7
.LBB0_8:
	movq	%fs:40, %rax
	cmpq	320(%rsp), %rax
	jne	.LBB0_10
# %bb.9:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	vzeroupper
	retq
.LBB0_10:
	.cfi_def_cfa %rbp, 16
	vzeroupper
	callq	__stack_chk_fail@PLT
.Lfunc_end0:
	.size	rt_cast_spheres, .Lfunc_end0-rt_cast_spheres
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 20.1.7"
	.section	".note.GNU-stack","",@progbits
