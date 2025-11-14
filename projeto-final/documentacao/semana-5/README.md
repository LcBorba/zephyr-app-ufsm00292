# 📋 Relatório Semana 5 - Conversão de Temperatura

## 🎯 OBJETIVO
Implementar conversão de dados brutos do sensor AT30TSE752A para temperatura em Celsius

## ✅ CONQUISTAS
- [x] Função temperature_channel_get() implementada
- [x] Conversão 12-bit → Celsius (0.0625°C/LSB)
- [x] Suporte a temperaturas negativas (complemento de 2)
- [x] Logs detalhados para debugging

## 🔧 IMPLEMENTAÇÃO

- Fórmula: temperatura = (raw_temp >> 4) * 0.0625
- Suporte a valores negativos via complemento de 2
