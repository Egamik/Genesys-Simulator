#!/bin/bash

source config.sh

default_git_repo=https://github.com/rlcancian2/Genesys-Simulator  # Default Genesys Git repository
default_git_branch=2023  # Default Genesys Git repository branch
docker_hub_image=modsimgrupo6/genesys:1.0  # Name of the genesys image in the Docker Hub
container_command=/bin/bash  # Default container command

function handle_save {
        docker commit genesys-container genesys-image > /dev/null
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

        docker rm genesys-container > /dev/null 2> /dev/null

}

function run_genesys {
        prepare_environment

        # Start container
        docker run -it --net host --name genesys-container \
                -e DISPLAY=$DISPLAY \
                -e XAUTHORITY=$XAUTH \
                -e GIT_USER=$GIT_USER \
                -e GIT_EMAIl=$GIT_EMAIL \
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

# Executar criação de chaves SSH no container
# Só será criada uma chave SSH no container se não houver uma
docker rm genesys-container > /dev/null 2> /dev/null
docker run -it --name genesys-container genesys-image generate-ssh-key
handle_save

echo -e '1. Configuração do Git
..............................................\n'

if [ -z "$GIT_USERNAME" ] || [ -z "$GIT_EMAIL" ] || [ -z "$GIT_REPO" ] || [ -z "$GIT_BRANCH" ]; then

    if [ -z "$GIT_USERNAME" ]; then
        read -p 'Digite o seu username: ' GIT_USERNAME
    fi


    if [ -z "$GIT_EMAIL" ]; then
        read -p 'Digite o seu email: ' GIT_EMAIL
    fi

    if [ -z "$GIT_REPO" ]; then
        read -p $'Digite a URL do repositório git que será utilizado\n(entrada vazia para usar o repositório padrão)\n> ' GIT_REPO
        if [ -z "$GIT_REPO" ]; then 
            GIT_REPO=$default_git_repo
            GIT_BRANCH=$default_git_branch
        fi
    fi

    if [ -z "$GIT_BRANCH" ]; then
        read -p $'\nDigite a branch do repositório:\n> ' GIT_BRANCH
    fi
else
    echo -e "Username: ${GIT_USERNAME}\nEmail: ${GIT_EMAIL}\nRepositório: ${GIT_REPO}\nBranch: ${GIT_BRANCH}"
fi

# Atualizando arquivo de configuração
echo -e "GIT_USERNAME=${GIT_USERNAME}\nGIT_EMAIL=${GIT_EMAIL}\nGIT_REPO=${GIT_REPO}\nGIT_BRANCH=${GIT_BRANCH}" > config.sh


if [ "$GIT_REPO" == "$default_git_repo" ]; then
      # Usar repositório padrão

      clone_command=${GIT_REPO}
      read -p $'\nDeseja atualizar o repositório padrão (s/N)?\n> ' input_update_repo
      
      if [ "$input_update_repo" == "s" ]; then
        # Atualizar repositório padrão
        docker rm genesys-container > /dev/null 2> /dev/null && docker run -it --name genesys-container -e REPO_PADRAO=true -e clone_command=$clone_command genesys-image ./clone-repo.sh
        handle_save
      else
        # Fazer pull do repositório padrão
        docker pull ${docker_hub_image}
        docker image tag ${docker_hub_image} genesys-image:latest
      fi
      
else
      # Repositório personalizado
      clone_command="--branch ${GIT_BRANCH} ${GIT_REPO}"
      
      docker rm genesys-container > /dev/null 2> /dev/null
      docker run -it --name genesys-container -e clone_command="${clone_command}" genesys-image ./clone-repo.sh
      handle_save
fi


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
                command=run-default-gui
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
