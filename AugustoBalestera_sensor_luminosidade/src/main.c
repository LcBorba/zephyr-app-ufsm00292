#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>

void main(void)
{
    printk("Simulador sensor de luminosidade iniciado!\n");
    int lux = 200;
    while (1) {
        uint32_t r = sys_rand32_get() % 21;  // 0..20
        lux += (int)r - 10;                 // varia -10..+10
        if (lux < 0) lux = 0;
        printk("Luminosidade: %d lx\n", lux);
        k_sleep(K_SECONDS(1));
    }
}


