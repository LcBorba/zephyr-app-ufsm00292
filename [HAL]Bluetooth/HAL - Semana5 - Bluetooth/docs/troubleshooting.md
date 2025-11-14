# Troubleshooting (erros vistos e correções)

## Devicetree / Bindings (SERCOM → UART)
- **Erro**: `'current-speed' appears in /soc/sercom@42001800 ... but is not declared in 'properties:' at atmel,sam0-sercom.yaml`
- **Causa**: usar `compatible` do SERCOM genérico. Para UART, usar `compatible = "atmel,sam0-uart";` e as props específicas **`rxpo`/`txpo`**.
- **Erro**: `'rxpo' is marked as required ... but does not appear in <Node /soc/sercom@42001800 ...>`
- **Correção**: adicionar `rxpo`/`txpo` (ex.: `rxpo=1`, `txpo=0`) e `current-speed` no node `&sercom4`.

## Kconfig / Buffers BLE (Zephyr 4.1+)
- **Erro de assert**: `Increase Event RX buffer count to be greater than ACL TX buffer count`  
  **Fix**: garantir `CONFIG_BT_BUF_EVT_RX_COUNT` **>** `CONFIG_BT_BUF_ACL_TX_COUNT`.
- **Deprecated**: `CONFIG_BT_BUF_ACL_RX_COUNT` → **remover**.
- **Renomeação**: `CONFIG_BT_NUS` → **`CONFIG_BT_ZEPHYR_NUS`**.
- **Undefined**: `CONFIG_BT_H4_ENABLE_FLOW_CONTROL`, `CONFIG_BT_HCI_UART_BAUDRATE` — são ajustados via **DT** nas versões novas.

## Linker (bt_nus_inst_*)
- **Sintoma**: `undefined reference to bt_nus_inst_send / bt_nus_inst_cb_register`
- **Causa**: símbolos do NUS antigo; limpar build e usar `CONFIG_BT_ZEPHYR_NUS=y`.
- **Fix**: `west build -p` e conferir `prj.conf` atualizado.

## Flash (Windows / OpenOCD)
- **Erro**: `required program openocd not found`  
  **Fix**: instalar **xPack OpenOCD** e apontar `--openocd` e `--openocd-search` no `west flash`.
- **Erro**: `Error connecting DP: cannot read IDR`  
  **Significa** que o OpenOCD fala com o EDBG, mas cai ao inicializar o core (reset/driver/segurança). Tente:
  1. **Backend/Reset/Velocidade**
     - `cmsis_dap_backend hid|winusb|libusb` (testar os 3), `adapter speed 50`, `transport select swd`, `reset_config srst_only srst_nogate connect_assert_srst`.
  2. **Chip erase (OpenOCD)**
     - `at91samd chip-erase` seguido de `program ... verify reset exit`.
  3. **Erase via Microchip (garantido)**
     - Microchip/Atmel Studio → *Device Programming* → Tool **EDBG**, Dev **ATSAMD21J18A**, IF **SWD** → **Erase**.
     - CLI: `atprogram.exe -t edbg -i SWD -d atsamd21j18a erase`.

**Checklist físico**
- Usar **USB DEBUG (EDBG/CMSIS-DAP)**.
- Fechar Microchip Studio/terminais seriais antes do `west flash`.
- Remover o **BTLC1000** do EXT1 ao gravar (evita interferência nos pinos do SERCOM).
- Testar SWD mais lento (`adapter speed 50` → `25`).
