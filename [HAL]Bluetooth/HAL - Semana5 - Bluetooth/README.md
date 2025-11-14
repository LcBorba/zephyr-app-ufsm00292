Este pacote consolida **o que foi feito, tentado e corrigido** até aqui para rodar o sample
`zephyr/samples/bluetooth/peripheral_nus` no **ATSAMD21 Xplained Pro** usando o **Atmel BTLC1000 Xplained Pro**
como **controlador BLE externo** via **HCI UART (H:4)** — e também documenta os passos de **flash via OpenOCD** no Windows.

> **Resumo do estado atual**
> - **Build passa e linka** (Zephyr 4.2.99 nos logs do usuário).
> - **Falha no flash** por OpenOCD inicialmente (OpenOCD ausente), resolvido instalando **xPack OpenOCD**.
> - **Novo erro no flash:** `Error connecting DP: cannot read IDR` durante `reset init`. Foram descritas e roteirizadas
>   **3 tentativas de recuperação** (backends + reset sob SRST, **chip-erase** com OpenOCD, ou **erase** via Microchip Studio/atprogram).


Build & flash (exemplo):
   ```powershell
   cd C:\Users\angel\zephyrproject
   py -m west build -b samd21_xpro -p -s zephyr\samples\bluetooth\peripheral_nus
   py -m west flash
   ```

   > Se o `west flash` reclamar do OpenOCD ausente, siga `docs/flash_openocd_windows.md` **ou** use diretamente os
   > comandos prontos de `scripts/flash_openocd_examples.ps1` (que apontam para o xPack OpenOCD).

---

## Principais problemas encontrados e correções

### 1) **Samples BLE**: não existe `peripheral_uart` nas versões recentes
- O sample equivalente é **`peripheral_nus`** (Nordic UART Service da Zephyr).

### 2) **Board name**: usar `samd21_xpro` (sem `at` no início)
- `atsamd21_xpro` não existe; o correto é `samd21_xpro` (Zephyr lista boards com `west boards`).

### 3) **Bindings DT** do SAM0 (SERCOM como UART)
- Erro do tipo *“'current-speed' appears in sercom... but not declared ...”* ou *“'rxpo' is required”*.
- Use `compatible = "atmel,sam0-uart";` e informe **`rxpo`/`txpo`** e `current-speed`. O **SERCOM4** da SAMD21 foi usado
  para HCI-UART do BTLC1000 (no header EXT1).

### 4) **Kconfig** (Zephyr 4.1+)
- `CONFIG_BT_NUS` mudou para **`CONFIG_BT_ZEPHYR_NUS`**.
- Itens deprecated: **não** usar `CONFIG_BT_BUF_ACL_RX_COUNT`.
- Regra de buffers: **`CONFIG_BT_BUF_EVT_RX_COUNT` > `CONFIG_BT_BUF_ACL_TX_COUNT`**. Ex.: `ACL_TX=6`, `EVT_RX=8`.
- Remova `CONFIG_BT_H4_ENABLE_FLOW_CONTROL` e `CONFIG_BT_HCI_UART_BAUDRATE` do `prj.conf` (são setados via DT atualmente).

### 5) **Link error** com `bt_nus_inst_*`
- Causado por símbolos do NUS antigo. Ao trocar para `CONFIG_BT_ZEPHYR_NUS=y` e limpar o build (`-p`), o link passou.

### 6) **Flash** no Windows
- `required program openocd not found` → resolver instalando **xPack OpenOCD** e apontando `--openocd`/`--openocd-search`,
  ou adicionando o `bin` ao PATH.
- `Error connecting DP: cannot read IDR` → ver `docs/troubleshooting.md` (Tentativas A/B/C). Geralmente é:
  - Backend do CMSIS-DAP (HID/WinUSB/libusb) incompatível com o driver atual do Windows.
  - Reset sob SRST necessário (`reset_config` + `connect_assert_srst`) para impedir que um firmware acorde o chip.
  - Chip protegido/travado → `at91samd chip-erase` (OpenOCD) **ou** `erase` via Microchip Studio/`atprogram`.

