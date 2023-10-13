#!/bin/bash

function handle_load {
        echo "Loading image..."
        docker load -i genesys-sim.tar
}

function handle_save {
        echo "Saving container image..."
        docker commit genesys genesys-sim
        docker save genesys-sim > genesys-sim.tar
}

function handle_build {
        echo "Building new image..."
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
}

function handle_run {
        echo "Starting genesys container..."
        # Working directory of socket file
        export XSOCK=/tmp/.X11-unix
        # Temporary access token 
        export XAUTH=/tmp/.docker.xauth

        # Check if temoporary token file exists, if not create one
        [ -e "$XAUTH" ] || touch "$XAUTH"

        # Generate new access token, set the Authentication Family to 'FamilyWild'
        xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

        # Start container
        docker run -it --net host --name genesys \
                -e DISPLAY=$DISPLAY \
                -e XAUTHORITY=$XAUTH \
                -v $XSOCK:$XSOCK \
                -v $XAUTH:$XAUTH \
                genesys-sim
}

read -p "Enter a command (load, save, run, build): " input
case "$input" in
        "load")
        handle_load
        ;;
        "save")
        handle_save
        ;;
        "run")
        handle_run
        ;;
        "build")
        handle_build
        ;;
        *)
        echo "Invalid command. Please enter load, save, run, or build."
        ;;
esac