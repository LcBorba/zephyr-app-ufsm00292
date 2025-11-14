/*
 * Aplicação de teste para sensor AT30TSE752A
 * Semana 6 - Integração completa
 * PLACA: SAM D21 Xplained Pro
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>
#include <stdio.h>

void main(void)
{
	printk("Iniciando aplicação de teste AT30TSE752A\n");
	printk("Placa: SAM D21 Xplained Pro\n");
	printk(" Sensor: AT30TSE752A (I2C 0x49)\n\n");

	const struct device *temp_sensor = DEVICE_DT_GET(DT_NODELABEL(temperature_sensor));
	
	if (!device_is_ready(temp_sensor)) {
		printk("ERRO: Sensor de temperatura não está pronto!\n");
		printk("   Possíveis causas:\n");
		printk("   - Device Tree overlay incorreto\n");
		printk("   - Endereço I2C diferente de 0x49\n");
		printk("   - Barramento I2C não habilitado\n");
		printk("   - Sensor não conectado\n");
		return;
	}

	printk("Sensor AT30TSE752A detectado e inicializado!\n");
	printk("Iniciando leituras contínuas...\n\n");

	int leitura_count = 0;
	
	while (1) {
		struct sensor_value temp;
		int ret;

		// Ler sensor
		ret = sensor_sample_fetch(temp_sensor);
		if (ret < 0) {
			printk("Erro na leitura I2C: %d\n", ret);
			k_sleep(K_SECONDS(2));
			continue;
		}

		// Obter temperatura
		ret = sensor_channel_get(temp_sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		if (ret < 0) {
			printk("Erro na conversão: %d\n", ret);
			k_sleep(K_SECONDS(2));
			continue;
		}

		// Mostrar temperatura
		leitura_count++;
		printk("[%03d] Temperatura: %d.%06d°C\n", 
		       leitura_count, temp.val1, temp.val2);
		
		// Aguardar 2 segundos
		k_sleep(K_SECONDS(2));
	}
}
