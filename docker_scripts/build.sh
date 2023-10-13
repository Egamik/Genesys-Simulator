#!/bin/bash

cd ..
GENESYS = $(pwd)

# Buildando a imagem
docker build -t genesys-sim .

# Criando pasta do pacote
mkdir GenesysPkg

# Adicionando imagem compactada a pasta do pacote
cd GenesysPkg
docker save -o genesys-sim.tar genesys-sim:latest

# Adicionando script de execução da imagem
cp GENESYS/docker_scripts/start_container.sh ./

# Compactando o pacote da imagem com o script
cd ..
tar -cvf GenesysPkg.tar GenesysPkg

# Limpando execução do script
rm -r GenesysPkg