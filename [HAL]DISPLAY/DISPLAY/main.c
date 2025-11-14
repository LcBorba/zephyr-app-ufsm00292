#include <atmel_start.h>
#include <hal_gpio.h>
#include <string.h>

#include "gfx_mono_main.h"
#include "gfx_mono_font_basic_6x7.h"


#define TEXT_X_POS   20
#define TEXT_Y_POS   12
#define TEXT_WIDTH   (UG2832HSWEG04_LCD_WIDTH - TEXT_X_POS)
#define TEXT_HEIGHT  7


void clear_text_area(void) {
	gfx_mono_draw_filled_rect(&MONOCHROME_GRAPHICS_desc,
						 TEXT_X_POS,
						 TEXT_Y_POS,
						 TEXT_WIDTH,
						 TEXT_HEIGHT,
						 GFX_PIXEL_CLR
						 );
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	// Display Message
	uint8_t msg[32];
	strcpy((char *)msg, "Inicializando");
	
	// Enable SPI and OLED
	spi_m_sync_enable(&DISPLAY_SPI);
	gfx_mono_init();
	
	// Desenha borda inicial
	gfx_mono_draw_rect(&MONOCHROME_GRAPHICS_desc,
						 0, 
						 0,
						 UG2832HSWEG04_LCD_WIDTH,
						 UG2832HSWEG04_LCD_HEIGHT,
						 GFX_PIXEL_SET
						 );
	
	
	// Draw a Message
	gfx_mono_text_draw_string(&MONOCHROME_TEXT_desc, msg, TEXT_X_POS, TEXT_Y_POS, &basic_6x7);
	
	
	/* Replace with your application code */
	while (1) {
        // Verifica o estado do botão
        if (gpio_get_pin_level(DISPLAY_BUTTON_1)) {

            gpio_set_pin_level(PA12, false); // LIGA LED
            gpio_set_pin_level(PA13, false); // LIGA LED
            gpio_set_pin_level(PA15, false); // LIGA LED
            
            // 2. Atualizar Display
            clear_text_area();
            strcpy((char *)msg, "LEDs Ligados");
            gfx_mono_text_draw_string(&MONOCHROME_TEXT_desc, msg, TEXT_X_POS, TEXT_Y_POS, &basic_6x7);
        } else {
            // 3. DESLIGAR LEDs
            gpio_set_pin_level(PA12, true); // DESLIGA LED
            gpio_set_pin_level(PA13, true); // DESLIGA LED
            gpio_set_pin_level(PA15, true); // DESLIGA LED

            // 4. Atualizar Display
            clear_text_area();
            strcpy((char *)msg, "LEDs Desligados");
            gfx_mono_text_draw_string(&MONOCHROME_TEXT_desc, msg, TEXT_X_POS, TEXT_Y_POS, &basic_6x7);
        }
        delay_ms(10); 
	}
}