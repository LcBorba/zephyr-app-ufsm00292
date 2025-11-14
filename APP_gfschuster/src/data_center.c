#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include "app.h"

// Fila global
K_MSGQ_DEFINE(sensor_msgq, sizeof(sensor_msg_t), MSGQ_MAX_MSG, MSGQ_ALIGN);

// Acumuladores
static int temp_acc = 0, lux_acc = 0, hum_acc = 0;
static int temp_count = 0, lux_count = 0, hum_count = 0;

void data_center_thread(void *a, void *b, void *c)
{
    sensor_msg_t msg;
    print_header();

    while (1) {
        if (k_msgq_get(&sensor_msgq, &msg, K_FOREVER) == 0) {
            if (strcmp(msg.tipo, "TEMP") == 0) {
                temp_acc += msg.valor;
                temp_count++;
            } else if (strcmp(msg.tipo, "LUX") == 0) {
                lux_acc += msg.valor;
                lux_count++;
            } else if (strcmp(msg.tipo, "HUM") == 0) {
                hum_acc += msg.valor;
                hum_count++;
            }

            if (temp_count > 0 && lux_count > 0 && hum_count > 0) {
                int temp_med = temp_acc / temp_count;
                int lux_med = lux_acc / lux_count;
                int hum_med = hum_acc / hum_count;
                uint32_t tempo = k_uptime_get_32() / 1000;

                printk("%d,%d,%d\n", temp_med, lux_med, hum_med);

                temp_acc = lux_acc = hum_acc = 0;
                temp_count = lux_count = hum_count = 0;
            }
        }

        k_msleep(200);
    }
}
