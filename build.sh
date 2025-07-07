#!/bin/bash

echo "=== Smart City DS - Build Script ==="

# Detectar o sistema operacional
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    echo "Sistema detectado: Windows"
    echo "Use o Visual Studio para compilar o projeto (.sln)"
    echo "Ou use: cl *.c /Fe:smartcity.exe"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Sistema detectado: macOS"
    echo "Compilando com GCC..."
    make clean
    make
    if [ $? -eq 0 ]; then
        echo "✅ Compilação bem-sucedida!"
        echo "Execute com: ./smartcity"
    else
        echo "❌ Erro na compilação"
    fi
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Sistema detectado: Linux"
    echo "Compilando com GCC..."
    make clean
    make
    if [ $? -eq 0 ]; then
        echo "✅ Compilação bem-sucedida!"
        echo "Execute com: ./smartcity"
    else
        echo "❌ Erro na compilação"
    fi
else
    echo "Sistema não reconhecido: $OSTYPE"
    echo "Tente compilar manualmente com: gcc *.c -o smartcity"
fi 