#include<bpf/libbpf.h>

int main(){
    const char* file_path = "prog.o";
    const char* prog_name = "detect_printf";
    struct bpf_object* bpfObject;
    struct bpf_program* bpfProgram;
    
    bpfObject = bpf_object__open(file_path);
    if(!bpfObject){
        printf("Failed to open %s\n",file_path);
        return 1;
    }
    int err = bpf_object__load(bpfObject);
    if(err){
        printf("Failed to load %s\n",file_path);
        return 1;
    }
    bpfProgram = bpf_object__find_program_by_name(bpfObject,prog_name);
    if(!bpfProgram){
        printf("Failed to find the program %s\n",prog_name);
        return 1;
    }
    bpf_program__attach(bpfProgram);
    while(1){
    }
    return 0;
}