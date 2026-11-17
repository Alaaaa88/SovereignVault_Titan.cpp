typedef unsigned char __u8;
typedef short int __s16;
typedef unsigned short int __u16;
typedef int __s32;
typedef unsigned int __u32;
typedef long long __s64;
typedef unsigned long long __u64;
typedef __u32 __be32;
typedef __u16 __be16;
typedef __u32 __wsum;
typedef __u32 u32;
typedef __u64 u64;
typedef unsigned long size_t;

#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

#define PROT_WRITE 0x2
#define PROT_EXEC  0x4
#define EPERM 1

// تعريف مسبق لتجنب مشاكل الرؤية في المترجم
struct vm_area_struct;

SEC("lsm/file_mprotect")
int BPF_PROG(aegis_mprotect_audit, struct vm_area_struct *vma, unsigned long reqprot, unsigned long prot) {
    if ((prot & PROT_WRITE) && (prot & PROT_EXEC)) {
        bpf_trace_printk("AEGIS LSM BLOCK: Denied W^X violation\n", 35);
        return -EPERM;
    }
    return 0;
}

char LICENSE[] SEC("license") = "GPL";
