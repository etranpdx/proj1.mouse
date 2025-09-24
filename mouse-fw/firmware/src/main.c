#include <stdio.h>
#include "pico/stdlib.h"

int main(void) {
    stdio_init_all();
    sleep_ms(1500);
    
    while (true) {
        printf("mouse-fw skeleton alive\r\n");
        sleep_ms(1000);
    }
}