all: aegis_probes.bpf.o aegis_sentinel real_exploit_test

aegis_probes.bpf.o: src/kernel/aegis_probes.bpf.c
	clang -O2 -g -target bpf -D__TARGET_ARCH_x86 -c $< -o $@

aegis_sentinel: src/engine/main.cpp
	g++ -std=c++20 -O3 $< -o $@ -lbpf -lelf -lz

real_exploit_test: tests/real_exploit_test.c
	gcc $< -o $@

clean:
	rm -f src/kernel/*.o *.o aegis_sentinel real_exploit_test
