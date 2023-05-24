#include<linux/bpf.h>
#include<bpf/bpf_helpers.h>
#include "kprobe1.h"

struct event{
    int pid;
    char filename[64];
};

struct{
    __uint(type,BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries,256*1024);
}ringbuf SEC(".maps");

SEC("kprobe/prepare_kernel_cred")
int trace_prepare_kernel_cred(struct pt_regs* ctx){
    __u32 pid = bpf_get_current_pid_tgid();
    struct event* evt = bpf_ringbuf_reserve(&ringbuf,sizeof(struct event),0);
    if(!evt){
        bpf_printk("bpf_ringbuf_reserve failed");
        return 1;
    }
    evt->pid = pid;
    bpf_get_current_comm(evt->filename,sizeof(evt->filename));
    bpf_ringbuf_submit(evt,0);
    return 0;
}

char _license[] SEC("license") = "GPL";