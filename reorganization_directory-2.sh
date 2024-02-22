#!/bin/bash

name=$1

mkdir -p Root

for nom_fichier in ${name}/*.txt;
    do
        prefix=$(basename "$nom_fichier" | cut -d'_' -f1)
        ye=$(basename "$nom_fichier" | cut -d'-' -f1 | cut -d'_' -f2)
        month=$(basename "$nom_fichier" | cut -d'-' -f2)
        day=$(basename "$nom_fichier" | cut -d'-' -f3)
        hour=$(basename "$nom_fichier" | cut -d'-' -f4)
        minute=$(basename "$nom_fichier" | cut -d'-' -f5)
        seconde=$(basename "$nom_fichier" | cut -d'-' -f6)
        ms=$(basename "$nom_fichier" | cut -d'-' -f7 | cut -d'.' -f1)

        newdir="Root/${name}/${prefix}/${ye}/${month}/${day}/${hour}"
        mkdir -p "$newdir"

        newfile="${minute}${seconde}${ms}.dat"

        mv "$nom_fichier" "$newfile"

        echo "$nom_fichier" > "$newdir/$newfile"
        echo "$newdir/$newfile" >> "$newdir/$newfile"
        echo "$0" >> "$newdir/$newfile"
        chmod 700 "$newdir/$newfile"
    done
