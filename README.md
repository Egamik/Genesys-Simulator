# Genesys-Simulator
Dockerização do ambiente de desenvolvimento e simulação do simulador Genesys.

# Docker
Docker é uma poderosa plataforma para desenvolvimento, compartilhamento e execução de aplicações. Ela nos oferece uma forma de empacotar aplicações e suas dependências em container leves e portáveis. Esses containers podem ser executados consistentemente em diferentes ambientes, desde de o laptop do desenvolvedor até um server de produção, garantindo que a aplicação se comporte da mesma maneira em qualquer lugar.

# X Window System 11
O protocolo se trata de um sistema de janelas por rede para sistemas UNIX, criado em 1980 o protocolo tem como objetivo permitir que um cliente e um servidor possam abrir seções interativas por meio de janelas GUI, em que o cliente pode executar um processo e o servidor pode abrir a janela do processo e interagir com o mesmo por meio dos seus dispositivos de entrada. Atualmente, o X11 vem empacotado com a maioria das distribuições Linux.

# Setup

## Linux (Ubuntu)

Nas principais distribuições Linux não é necessário fazer nenhum setup, visto que os pacotes necessários para este projeto já vêm por padrão no sistema operacional.

Para sistemas UNIX basta que o xorg (implementação do protocolo X11) esteja instalado, juntamente com o xauth. Você pode executar os comandos abaixo para certificar-se que os pacotes estão presentes:

```
dpkg -l | grep xorg
```
```
dpkg -l | grep xauth
```


## Windows

Em sistemas windows será necessario instalar o Windows Subsystem for Linux (WSL). 

Em uma seção Powershell administrador, execute o comando:

```
wsl --install
```

Após a instalação, comandos docker executados em uma seção WSL serão processados pelo Docker engine da máquina host e poderão ser visualizados na interface Docker Desktop.
Assim como para o container para Linux, é necessário montar o volume do socket X11 do Ubuntu WSL com o container. Os comandos disponibilizados no script `docker-genesys.sh` são válidos para execucao no WSL, contudo como os sockets X11 do WSL estão em volumes especiais no windows, os containers não irão funcionar como esperado. Para iniciar um container no windows basta seguir os passos abaixo:

![install_wsl](https://github.com/Egamik/Genesys-Simulator/assets/44400533/3a9aae4e-20fb-494b-974d-6c65ee0d7286)
Legenda: Instalação do WSL no Powershell

![file_explorer](https://github.com/Egamik/Genesys-Simulator/assets/44400533/e3cc6794-aaf6-4e0f-a5fe-4fa26e131d6d)

![wsl_file_location](https://github.com/Egamik/Genesys-Simulator/assets/44400533/4e512553-027f-41c9-bc3e-bd25fbf2ae8a)
Legenda: Caminho do volume a ser montado durante inicialização do container

![volumes](https://github.com/Egamik/Genesys-Simulator/assets/44400533/615a86ba-4a3a-4640-82dc-9b696647b59c)
Legenda: Montagem do volume da pasta dentro do WSL para pasta do container

# Configuração

A configuração da aplicação é feita no arquivo `config.sh`.

Neste arquivo você pode configurar:

- Username do Git
- Email do Git
- Repositório Git a ser utilizado no Docker
- Branch do repositório

A configuração é feita da seguinte forma: `nome_da_configuração=valor`

Não podem haver espaços na string de configuração.


# Execução

A partir do diretório `docker/` deste projeto, execute o script `docker-genesys.sh`:

```
./docker-genesys.sh
```

Feito isto, basta seguir as instruções do script que vão surgir no seu terminal.

## Push e Pull de repositórios remotos

Para poder fazer push para repositórios remotos, ou pull de repositórios privados, é necessário o uso de um par de chaves SSH
para fazer a autenticação do usuário. Portanto, dentro do container será gerado um par de chaves SSH, e a chave pública será escrita
no arquivo de configuração `config.sh`, na entrada `SSH_PUBLIC_KEY`.

Adicione esta chave pública à sua conta do GitHub/GitLab para poder fazer operações de push e pull no repositório remoto.


# Informações adicionais

A imagem Docker gerada pelo Dockerfile deste projeto encontra-se disponível para download em [https://hub.docker.com/repository/docker/modsimgrupo6/genesys/general](https://hub.docker.com/repository/docker/modsimgrupo6/genesys/general).

## Como obter a imagem do Genesys Docker sem o uso do script

**1. Realizando pull da imagem a partir do Docker Hub**

```
docker pull modsimgrupo6/genesys:1.0
docker image tag modsimgrupo6/genesys:1.0 genesys-image:latest
```
A imagem estará disponível na sua máquina com o nome `genesys-image`

**2. Buildando a imagem a partir do Dockerfile**

Dentro do diretório `docker/` deste projeto, execute:

```
docker build -t genesys-image .
```

A imagem estará disponível na sua máquina com o nome `genesys-image`

