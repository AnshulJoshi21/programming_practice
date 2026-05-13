__attribute__((naked))
void _start()
{
    asm volatile(
        "addi x1, x0, 5\n"
        "addi x2, x0, 7\n"
        "add  x3, x1, x2\n"
        "ecall\n"
    );
}
