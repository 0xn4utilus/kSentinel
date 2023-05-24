 export C_INCLUDE_PATH=/usr/include/x86_64-linux-gnu
compile:
	clang -O2 -g -Wall -I/usr/include -I/usr/include/bpf -o run run.c -lbpf
	clang -O2 -g -target bpf -c kprobe1.c -o kprobe1.o