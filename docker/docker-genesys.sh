#!/bin/bash

default_git_repo=https://github.com/rlcancian2/Genesys-Simulator  # Default Genesys Git repository
docker_hub_image=modsimgrupo6/genesys:1.0  # Name of the genesys image in the Docker Hub
container_command=/bin/bash  # Default container command

function handle_save {
        docker commit genesys-container genesys-image
}

function prepare_environment {
        echo "Iniciando container do Genesys..."
        # Working directory of socket file
        export XSOCK=/tmp/.X11-unix
        # Temporary access token 
        export XAUTH=/tmp/.docker.xauth

        # Check if temoporary token file exists, if not create one
        [ -e "$XAUTH" ] || touch "$XAUTH"

        # Generate new access token, set the Authentication Family to 'FamilyWild'
        xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

        docker rm genesys-container 2> /dev/null

}

function run_genesys {
        prepare_environment

        # Start container
        docker run -it --net host --name genesys-container \
                -e DISPLAY=$DISPLAY \
                -e XAUTHORITY=$XAUTH \
                -e command=${command} \
                -v $XSOCK:$XSOCK \
                -v $XAUTH:$XAUTH \
                genesys-image \
                ./run-genesys.sh
}

echo -e "\n========= Bem vindo ao Genesys docker ========= \n\n" 

# Checando se a imagem do genesys já está instalada na máquina
IMAGE_NAME=genesys-image
if docker image inspect $IMAGE_NAME >/dev/null 2>&1; then
    echo -e "Foi encontrada uma imagem do Genesys localmente!\n"
else
    dockerfile=./Dockerfile
    if [ -f "$dockerfile" ]; then
        echo "Não foi encontrada uma imagem do Genesys localmente, no entanto há um script Dockerfile disponível localmente."
        read -p $"O que deseja fazer?\n...................\n1. Compilar imagem a partir do Dockerfile\n2.Baixar imagem do Docker Hub\n> " input_imagem
        if [ "$input_imagem" == "1" ]; then
            docker build -t genesys-image .
        else
            # Fazer pull do repositório padrão
            docker pull ${docker_hub_image}
            docker image tag ${docker_hub_image} genesys-image:latest
        fi
    else
        echo "Não foi encontrada uma imagem do Genesys localmente. Baixando imagem do Docker Hub..."
        echo -e "Isto pode levar alguns minutos\n"
        docker pull ${docker_hub_image}
        docker image tag ${docker_hub_image} genesys-image:latest
    fi
fi

read -p $'1. Configuração do repositório git do Genesys
..............................................

Digite a URL do repositório git que será utilizado
(entrada vazia para usar o repositório padrão)\n> ' input_git_repo

if [ -z "$input_git_repo" ]; then
      # Usar repositório padrão

      clone_command=${default_git_repo}
      read -p $'\nDeseja atualizar o repositório padrão (s/N)?\n> ' input_update_repo
      
      if [ "$input_update_repo" == "s" ]; then
        # Atualizar repositório padrão
        docker rm genesys-container 2> /dev/null && docker run -it --name genesys-container -e clone_command=$clone_command genesys-image ./clone-repo.sh
        handle_save
      else
        # Fazer pull do repositório padrão
        docker pull ${docker_hub_image}
        docker image tag ${docker_hub_image} genesys-image:latest
      fi
      
else
      # Repositório personalizado
      read -p $'\nDigite a branch:\n> ' input_git_branch
      clone_command="--branch ${input_git_branch} ${input_git_repo}"
      
      docker rm genesys-container 2> /dev/null
      docker run -it --name genesys-container -e clone_command="${clone_command}" genesys-image ./clone-repo.sh
      handle_save
fi

# TODO: Executar criação de chaves SSH no container


read -p "
2. Menu: O que deseja executar?
..............................................
1. Genesys GUI
2. Genesys Shell
3. IDE do Genesys (QtCreator)
4. VSCode
> " input

case "$input" in  # TODO: Fazer um loop aqui
        "1")
        read -p $'\nDeseja compilar a partir do código-fonte (s/N)?\n> ' input_recompile
        if [ "$input_recompile" == "s" ]; then
                command=recompile-gui
        else
                command=/home/Genesys-Simulator/GenesysQtGUI
        fi
        run_genesys
        ;;       
        "2")
        read -p $'\nDeseja compilar a partir do código-fonte (s/N)?\n> ' input_recompile
        if [ "$input_recompile" == "s" ]; then
                command=recompile-shell
        else
                command=/home/Genesys-Simulator/GenesysShell
        fi
        run_genesys
        ;;
        "3")
        command=qtcreator
        run_genesys
        ;; 
        "4")
        command=vscode
        run_genesys
        ;; 
        *)
        echo -e "\nOpção inválida."
        ;;
esac

echo -e "\nSalvando imagem a partir do container..."
handle_save
