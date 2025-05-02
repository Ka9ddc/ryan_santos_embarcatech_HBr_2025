## Projeto de testes unitários

Projeto para realizar testes unitários para verificar a conversão de valores ADC para temperatura em Celsius.

---
### Como compilar?

Para compilar o teste utilize o seguinte comando no terminal:

```bash
gcc test/test_temp.c src/unity.c hal/hal_temp.c -Iinclude -Isrc -o test/teste_temperatura.exe
```

Para executar o teste utilize o seguinte comando no terminal:

```bash
./test/teste_unitario.exe
```
---