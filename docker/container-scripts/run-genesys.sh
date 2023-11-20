#!/bin/bash
$command

# Salvar o trabalho
echo -e "\nNão se esqueça de salvar seu trabalho. Commite suas alterações e faça o push.\nLembrete: você pode usar o VSCode por meio do comando 'vscode'\n\n"

read -p $'Gostaria de acessar o terminal antes de sair (s/N)?\n> ' input_access_terminal

if [ "$input_access_terminal" == "s" ]; then

  echo -e '1. Configuração do usuário do git\n..............................................\n'
  read -p 'Digite o seu email: ' input_email
  read -p 'Digite o seu username: ' input_username

  git config --global user.email "${input_email}"
  git config --global user.name "${input_username}"

  echo -e "\nPara poder fazer push e pull requests para um repositório do GitHub, adicione a seguinte chave pública SSH à sua conta do GitHub:\n"

  cat ~/id_rsa.pub


  cd /home/Genesys-Simulator && bash     
fi

