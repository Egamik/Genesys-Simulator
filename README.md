# Genesys-Simulator
Dockerização do ambiente de desenvolvimento para o simulador Genesys.

# Docker
Docker é uma poderosa plataforma para desenvolvimento, compartilhamento e execução de aplicações. Ela nos oferece uma forma de empacotar aplicações e suas dependências em container leves e portáveis. Esses containers podem ser executados consistentemente em diferentes ambientes, desde de o laptop do desenvolvedor até um server de produção, garantindo que a aplicação se comporte da mesma maneira em qualquer lugar.

# X Window System 11
O protocolo se trata de um sistema de janelas por rede para sistemas UNIX, criado em 1980 o protocolo tem como objetivo permitir que um cliente e um servidor possam abrir seções interativas por meio de janelas GUI, em que o cliente pode executar um processo e o servidor pode abrir a janela do processo e interajir com o mesmo por meio dos seus dispositivos de entrada. Atualmente, o X11 vem empacotado com a maioria das distribuicoes Linux.

# Set up e execucao
Antes de subir o container certifique-se de que o X11 está instalado na máquina hospedeira. Você pode executar o comando abaixo para certificar que o pacote está presente:

```
dpkg -l | grep xorg
```

Para sistemas UNIX basta que o xorg esteja instalado, juntamente com o xauth e executar o script start_container.sh. Em sistemas windows será necessario instalar o Windows Subsystem for Linux (WSL). Em uma seção Powershell administrador, execute o comando:

```
wsl --install
```

Ápos a instalação comandos docker executados em secao WSL serão processados pelo Docker engine da máquina host e poderão ser visualizados na interface Docker Desktop.
Assim como para o container para Linux é necessário montar o volume do socket X11 do Ubuntu WSL com o container.

FOTO
FOTO
FOTO

OBS: Containers docker não têm seus contextos salvos apos o termino da execucao, se voce fez alteracoes no container e que manter as modificacoes ou salve o container como uma nova imagem, ou não remova o container.

## Executando outros comandos no container
Por padrão, o container irá executar o comando declarado na Dockerfile durante a build da imagem e irá parar de executar com a morte do processo, para executar outros comandos sob o mesmo container basta reiniciar o contaier e executar um comando:

```
docker start container-name

docker exec -it container-name command
```

# Scripts
Além dos containers foi disponibilizado alguns scripts para a manutenção e disponibilização.

## build
Esse script irá montar a imagem da interface gráfica do Genesys com base na branch do repositório em que ele foi executado, após montar a imagem ele irá também gerar um arquivo '.tar' dessa imagem, que será utilizado para gerar um segundo arquivo compactado contendo a imagem e um script para sua inicialização. A ideia é que ao rodar esse script você terá como retorno um pacote capaz de inicializar a interface gráfica do Genesys em qualquer máquina que possua o docker instalado.

## start_container
Esse script faz a inicialização do container da interface gráfica do Genesys. Basicamente ele necessita da imagem compactada do Genesys para carregar essa imagem usando o docker e inicializá-la como deve ser feita.

# Sugestões

## Integração Contínua
É possível utilizar runners, como do gitlab por exemplo, para automatizar a atualização das imagens do projeto. Eles iriam executar os scripts já existentes para buildar e disponibilizar as imagens, toda vez que a branch main fosse atualizada, mantendo assim a imagem sempre na versão mais atualizada do repositório.

## Registro de container
É possível utilizar serviços de registro de container, como o próprio Docker HUB ou outros, para se disponibilizar as imagens do projeto. A maioria dos registros são pagos, ou bloqueiam algumas funcionalidades através de pagamentos, entretando eles oferecem funções como versionamento de imagens, o que permitiria um usuário baixar qualquer versão do Genesys disponibilizada neste registro. Para acessar as imagens os usuários usariam o próprio docker, informando o url do registro na web (muitas vezes também um usuário e senha de acesso) e fariam download da imagem para seu registro local, tendo apenas que executar o script para sua inicialização localmente. Além disso, utilizando a integração contínua, é possível atualizar as versões das imagens no registro automaticamente.