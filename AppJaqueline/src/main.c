#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

void main(void)
{
    const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(sercom1));
    
    if (!device_is_ready(i2c_dev)) {
        LOG_ERR("I2C device not ready");
        return;
    }
    
    LOG_INF("I2C device ready: %s", i2c_dev->name);
    
    // Testar ambos os endereços possíveis do BNO055
    uint8_t addresses[] = {0x28, 0x29};
    uint8_t reg = 0x00;  // Registro CHIP_ID
    uint8_t data[1];
    
    LOG_INF("Testando endereços do BNO055...");
    
    for (int i = 0; i < 2; i++) {
        int ret = i2c_write_read(i2c_dev, addresses[i], &reg, 1, data, 1);
        
        if (ret == 0) {
            LOG_INF("✅ Dispositivo encontrado no endereço 0x%02X", addresses[i]);
            LOG_INF("Chip ID: 0x%02X", data[0]);
            
            if (data[0] == 0xA0) {
                LOG_INF("✅ BNO055 identificado corretamente!");
            } else {
                LOG_WRN("Chip ID inesperado. Esperado: 0xA0");
            }
        } else {
            LOG_INF("❌ Nenhum dispositivo no endereço 0x%02X (erro: %d)", addresses[i], ret);
        }
        
        k_msleep(100);
    }

    // Scan do barramento I2C (versão simplificada)
    LOG_INF("--- Scan do barramento I2C ---");
    for (uint8_t addr = 0x08; addr <= 0x77; addr++) {
        int ret = i2c_write_read(i2c_dev, addr, &reg, 1, data, 1);
        if (ret == 0) {
            LOG_INF("Dispositivo em: 0x%02X", addr);
        }
    }
    LOG_INF("--- Fim do scan ---");

    while (1) {
        k_msleep(1000);
    }
}