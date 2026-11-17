
#include <iostream>
#include <unistd.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>

int main() {
    // البحث عن الملف في المجلد الحالي مباشرة
    const char *path = "aegis_probes.bpf.o";
    struct bpf_object *obj = bpf_object__open(path);
    if (libbpf_get_error(obj)) {
        // محاولة المسار البديل
        path = "src/kernel/aegis_probes.bpf.o";
        obj = bpf_object__open(path);
        if (libbpf_get_error(obj)) {
            std::cerr << "[!] Failed to open BPF object file!" << std::endl;
            return 1;
        }
    }

    if (bpf_object__load(obj)) {
        std::cerr << "[!] Failed to load BPF object into kernel" << std::endl;
        return 1;
    }

    struct bpf_program *prog = bpf_object__find_program_by_name(obj, "trace_mprotect");
    if (!prog) {
        std::cerr << "[!] Failed to find BPF program" << std::endl;
        return 1;
    }

    struct bpf_link *link = bpf_program__attach(prog);
    if (libbpf_get_error(link)) {
        std::cerr << "[!] Failed to attach BPF program to kprobe" << std::endl;
        return 1;
    }

    std::cout << "=== AEGIS-SENTINEL REAL KERNEL ENFORCEMENT ACTIVE ===" << std::endl;
    std::cout << "[ACTIVE] Intercepting and blocking W^X violations in-kernel. Press Ctrl+C to exit." << std::endl;

    while (true) {
        sleep(1);
    }

    bpf_link__destroy(link);
    bpf_object__close(obj);
    return 0;
}
