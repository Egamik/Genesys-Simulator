# Genesys-Simulator
Dockerização do ambiente de desenvolvimento para o simulador Genesys

# Docker
Escrever coisas legais sobre docker

# X Window System 11
O protocolo se trata de um sistema de janelas por rede para sistemas UNIX, criado em 1980 o protocolo tem como objetivo permitir que um cliente e um servidor possam abrir seções interativas por meio de janelas GUI, em que o cliente pode executar um processo e o servidor pode abrir a janela do processo e interajir com o mesmo por meio dos seus dispositivos de entrada. Atualmente, o X11 vem empacotado com a maioria das distribuicoes Linux.

# Set up e execucao
Antes de subir o container certifique-se de que o X11 está instalado na máquina hospedeira. Você pode executar o comando abaixo para certificar que o pacote está presente:

```
dpkg -l | grep xorg
```

Para sistemas UNIX basta que o xorg esteja instalado, juntamente com o xauth e executar o script start_container.sh.

OBS: Containers docker não têm seus contextos salvos apos o termino da execucao, se voce fez alteracoes no container e que manter as modificacoes ou salve o container como uma nova imagem, ou não remova o container.

## Executando outros comandos no container
Por padrão, o container irá executar o comando declarado na Dockerfile durante a build da imagem e irá parar de executar com a morte do processo, para executar outros comandos sob o mesmo container basta reiniciar o contaier e executar um comando:

```
docker start container-name

docker exec -it container-name command
```