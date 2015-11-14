#ifndef _FS_EBPF_H
#define _FS_EBPF_H

#include <linux/bpf.h>

#define INSN(_code, _dst, _src, _off, _imm)	\
	((struct bpf_insn) {			\
		.code  = _code,			\
		.dst_reg = _dst,		\
		.src_reg = _src,		\
		.off   = _off,			\
		.imm   = _imm			\
	})

#define EXIT INSN(BPF_JMP | BPF_EXIT, 0, 0, 0, 0)

#define MOV_IMM(_dst, _imm) INSN(BPF_ALU64 | BPF_MOV | BPF_K, _dst, 0, 0, _imm)

struct ebpf {
	struct bpf_insn prog[BPF_MAXINSNS];
	struct bpf_insn *ip;
};

struct ebpf *ebpf_init(struct ebpf *e);



int fs_compile(struct fs_node *n, struct ebpf *e);

#endif	/* _FS_EBPF_H */