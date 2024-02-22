#!/bin/bash
# Le premier argument est le nom du répertoire à créer
repo_name=$1
# Le deuxième argument est le nombre de fichiers à créer
prefix=$2
# Le troisième argument est le préfixe des noms de fichiers
n=$3
# Le quatrième argument est l'écart en millisecondes entre la création de chaque fichier
m=$4
# Créer le répertoire s'il n'existe pas déjà
mkdir -p $repo_name
# Se déplacer dans le répertoire
cd $repo_name
# Créer une boucle pour générer n fichiers
for ((i=1; i<=n; i++))
do
  # Générer le nom du fichier avec le préfixe et la date système
  file_name=${prefix}_$(date +"%Y-%m-%d-%H-%M-%S-%3N").txt
  # Créer le fichier vide avec la commande touch
  touch $file_name
  # Attendre m millisecondes avant de créer le prochain fichier
  sleep $m
done
