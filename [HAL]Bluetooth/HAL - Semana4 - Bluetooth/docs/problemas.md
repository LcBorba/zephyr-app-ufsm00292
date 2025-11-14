# Troubleshooting & Tentativas

Este arquivo sumariza os erros encontrados e como foram corrigidos.

## 1) `west` não reconhecido
- **Causa**: PATH não tinha o West.
- **Fix**: `py -m pip install --user west` e usar sempre `py -m west ...`.

## 2) Sample `peripheral_uart` não existe
- **Causa**: sample renomeado. Hoje é `samples/bluetooth/peripheral_nus`.
- **Fix**: usar `peripheral_nus` no comando de build.

## 3) `ModuleNotFoundError: jsonschema` (fase CMake)
- **Causa**: dependências Python do Zephyr ausentes.
- **Fix**: `py -m pip install --user -r zephyr\scripts\requirements.txt`.

## 4) Board nome incorreto
- **Causa**: usamos `atsamd21_xpro` por engano.
- **Fix**: board correta é `samd21_xpro`.

## 5) `Missing DT chosen property for HCI`
- **Causa**: faltava `chosen { zephyr,bt-hci = &bt_hci_uart; }` apontando para um nó `zephyr,bt-hci-uart`.
- **Fix**: overlay com `bt_hci_uart` pendurado na UART (SERCOM4).

## 6) `current-speed` não declarado em SERCOM
- **Causa**: propriedade colocada no nó `&sercom4` (pai), mas pertence ao nó UART.
- **Fix**: especializar `&sercom4` como UART (`compatible = "atmel,sam0-uart";`) e então setar `current-speed`.

## 7) `rxpo` / `txpo` obrigatórios
- **Causa**: binding `atmel,sam0-uart` exige declarar os PADs usados.
- **Fix**: `rxpo = <1>` (RX em PAD1) e `txpo = <0>` (sem RTS/CTS) **ou** `txpo = <2>` (com RTS/CTS).

## 8) `undefined reference to bt_nus_inst_*`
- **Causa**: habilitamos Kconfigs do NCS (`CONFIG_BT_NUS`, `CONFIG_SHELL_BT_NUS`), que não existem no Zephyr puro.
- **Fix**: no Zephyr **mainline**, o NUS é embutido no sample; basta `CONFIG_BT` + `CONFIG_BT_PERIPHERAL`
  (e manter o include `zephyr/bluetooth/services/nus.h` do sample).
