#include "prog.h"
#include "james.h"

int main(void) {
    uart_init();
    print_hexdump();
    while (1);
}

