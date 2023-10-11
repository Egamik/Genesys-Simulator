# Genesys-Simulator
Dockerização do ambiente de desenvolvimento para o simulador Genesys


# X Window System 11
O protocolo se trata de um sistema de janelas por rede para sistemas UNIX, criado em 1980 o protocolo tem como objetivo permitir que um cliente e um servidor possam abrir seções interativas por meio de janelas GUI, em que o cliente pode executar um processo e o servidor pode abrir a janela do processo e interajir com o mesmo por meio dos seus dispositivos de entrada. Atualmente, o X11 vem empacotado com a maioria das distribuicoes Linux.

# Set up
Antes de subir o container certifique-se de que o X11 está instalado na máquina hospedeira. Você pode executar o comando abaixo para certificar que o pacote está presente:

```
dpkg -l | grep xorg
```

Para sistemas UNIX basta que o xorg esteja instalado, juntamente com o xauth e executar o script start_container.sh