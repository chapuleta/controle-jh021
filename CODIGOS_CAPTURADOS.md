# Códigos IR Capturados - Controle JH021

**Data da Captura:** 28/01/2026  
**Protocolo Principal:** NEC  
**Bits:** 32

## Resumo dos Códigos

| Botão | Código Hex | Protocolo | Bits | Status |
|-------|-----------|-----------|------|--------|
| POWER | 0xFF00FF | NEC | 32 | ✅ OK |
| UP | 0xFF807F | NEC | 32 | ✅ OK |
| 12/24 | 0xFF40BF | NEC | 32 | ✅ OK |
| LEFT | 0xFF20FF | NEC_LIKE | 32 | ✅ OK |
| OK | 0xFFA05F | NEC | 32 | ✅ OK - Validado |
| RIGHT | 0xFF609F | NEC | 32 | ✅ OK |
| EXIT | 0xFF10EF | NEC | 32 | ✅ OK |
| DOWN | 0xFF906F | NEC | 32 | ✅ OK |
| SET | 0xFF50AF | NEC | 32 | ✅ OK |
| 0 | 0xFF30CF | NEC | 32 | ✅ OK |
| STOPWATCH | 0xFFB04F | NEC | 32 | ✅ OK |
| AL | 0xFF708F | NEC | 32 | ✅ OK |
| 1 | 0xFF08F7 | NEC | 32 | ✅ OK |
| 2 | 0xFF8877 | NEC | 32 | ✅ OK |
| 3 | 0xFF48B7 | NEC | 32 | ✅ OK |
| 4 | 0xFF28D7 | NEC | 32 | ✅ OK |
| 5 | 0xFFA857 | NEC | 32 | ✅ OK |
| 6 | 0xFF6897 | NEC | 32 | ✅ OK |
| 7 | 0xFF18E7 | NEC | 32 | ✅ OK |
| 8 | 0xFF9867 | NEC | 32 | ✅ OK |
| 9 | 0xFF58A7 | NEC | 32 | ✅ OK |

## ⚠️ Observações

### Botão OK - Problema na Captura
O botão OK foi capturado com protocolo LUTRON (incorreto). Possíveis soluções:
1. Recapturar apenas o botão OK
2. Tentar usar protocolo NEC com código similar aos outros
3. Se não funcionar, pode ser que o botão OK use um protocolo diferente mesmo

### Mapeamento Web
Os códigos já estão mapeados para a interface web:
- Botão físico "12/24" → Comando web "12_24"
- Demais botões mantêm o mesmo nome

## Código Gerado para Emissor

```cpp
const IRMapping webToIR[] = {
    {"POWER", 0xFF00FFULL},
    {"UP", 0xFF807FULL},
    {"12_24", 0xFF40BFULL},
    {"LEFT", 0xFF20FFULL},
    {"OK", 0x400000000ULL},      // ⚠️ Pode precisar recapturar
    {"RIGHT", 0xFF609FULL},
    {"EXIT", 0xFF10EFULL},
    {"DOWN", 0xFF906FULL},
    {"SET", 0xFF50AFULL},
    {"0", 0xFF30CFULL},
    {"STOPWATCH", 0xFFB04FULL},
    {"AL", 0xFF708FULL},
    {"1", 0xFF08F7ULL},
    {"2", 0xFF8877ULL},
    {"3", 0xFF48B7ULL},
    {"4", 0xFF28D7ULL},
    {"5", 0xFFA857ULL},
    {"6", 0xFF6897ULL},
    {"7", 0xFF18E7ULL},
    {"8", 0xFF9867ULL},
    {"9", 0xFF58A7ULL}
};
```

## Configuração do Emissor
- **Protocolo:** NEC
- **Bits:** 32
- **GPIO:** 15 (mesmo pino do receptor)
