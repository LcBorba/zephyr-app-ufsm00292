#include <zephyr/kernel.h>
#include "app.h"

// Threads (stack, prioridade e delay)
K_THREAD_DEFINE(temp_tid, 1024, sensor_temp_thread, NULL, NULL, NULL, 2, 0, 0);
K_THREAD_DEFINE(lux_tid, 1024, sensor_lux_thread, NULL, NULL, NULL, 2, 0, 0);
K_THREAD_DEFINE(hum_tid, 1024, sensor_humidity_thread, NULL, NULL, NULL, 2, 0, 0);
K_THREAD_DEFINE(center_tid, 2048, data_center_thread, NULL, NULL, NULL, 1, 0, 0);
