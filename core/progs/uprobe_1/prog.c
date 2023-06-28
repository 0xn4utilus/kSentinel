#include<linux/bpf.h>
#include<bpf/bpf_helpers.h>

SEC("uprobe/libc.so.6:printf")
void detect_printf(struct pt_regs* ctx){
    bpf_printk("printf called");
}

char _license[] SEC("license") = "GPL";