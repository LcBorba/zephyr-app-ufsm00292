Write-Host "Executando APP_gfschuster no QEMU e salvando logs..." -ForegroundColor Cyan

# Remove arquivo antigo
if (Test-Path "qemu_output.txt") {
    Remove-Item "qemu_output.txt"
}

# Executa o QEMU e grava a saída no arquivo
qemu-system-x86_64 -machine accel=tcg -nographic -kernel build/zephyr/zephyr.elf | Out-File -FilePath "qemu_output.txt" -Encoding utf8
