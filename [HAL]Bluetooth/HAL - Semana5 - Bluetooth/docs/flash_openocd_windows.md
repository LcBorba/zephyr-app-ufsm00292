# Flash no Windows com xPack OpenOCD

## Instalação (sem Chocolatey)
1. Baixe o **xPack OpenOCD** (Windows x64) e descompacte em:
   `C:\Users\angel\AppData\Roaming\xPacks\openocd\xpack-openocd-0.12.0-7\`
2. Caminhos que iremos usar:
   - Binário: `...\bin\openocd.exe`
   - Scripts: `...\share\openocd\scripts\` (ou `...\openocd\scripts\`, conforme o pacote)

## Flash (apontando caminhos, sem PATH)
No seu workspace (`C:\Users\angel\zephyrproject`):
```powershell
py -m west flash -r openocd `
  --openocd "C:\Users\angel\AppData\Roaming\xPacks\openocd\xpack-openocd-0.12.0-7\bin\openocd.exe" `
  --openocd-search "C:\Users\angel\AppData\Roaming\xPacks\openocd\xpack-openocd-0.12.0-7\share\openocd\scripts"
```

Se falhar com `cannot read IDR`, veja `docs/troubleshooting.md` (Tentativas A/B/C).
