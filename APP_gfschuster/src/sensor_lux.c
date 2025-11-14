#include <zephyr/kernel.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"

void sensor_lux_thread(void *a, void *b, void *c)
{
    sensor_msg_t msg;

    while (1) {
        msg.valor = rand() % 1000; // 0 a 999 lx
        strcpy(msg.tipo, "LUX");
        k_msgq_put(&sensor_msgq, &msg, K_NO_WAIT);
        k_msleep(1200);
    }
}
