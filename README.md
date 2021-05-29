# insa_gl

## Introduction

Ce projet est réalisé par 5 étudiants de l'INSA Lyon, en première année de cycle d'ingénieur en informatique. L'objectif est de partir d'un besoin, de concevoir une solution, et de la réaliser (du moins, pour les fonctionnalités principales).

Le projet est développé en C++, en utilisant un Makefile compatible sur systèmes Unix et Windows.

## Installation

A la racine du projet, exécutez `make setup_win` si vous êtes sur système Windows, sinon `make setup` pour créer les dossiers nécessaires à la compilation du projet.

## Makefile

Les commandes du Makefile sont :

- `make setup` : crée les dossiers de l'architecture du projet pour systèmes UNIX
- `make setup_win` : crée les dossiers de l'architecture du projet pour systèmes WINDOWS
- `make all` : compile le projet
- `make test` : compile les tests unitaires
- `make dev` : compile l'exécutable de debug
- `make clean` : supprime les fichiers compilés .obj
- `make fclean` : supprime les fichiers compilés .obj et l'exécutable
- `make re` : supprime les fichiers compilés .obj, l'exécutable, et recompile le projet

Pour adapter le Makefile selon le système d'exploitation de votre machine, il est nécessaire de changer les variables `RM`, `MKDIR`, `EXT` et `S` (séparateur). 

## Exécution

Après compilation du projet (voir sections précédentes), à la racine, lancez l'exécutable 
`./gl_app.out` ou `./gl_app.exe` (selon le système)

## Tests unitaires

Après compilation des tests (voir sections précédentes), à la racine, lancez l'exécutable 
`./gl_test.out` ou `./gl_test.exe` (selon le système)

## Debug

Après compilation de l'exécutable de debug (voir sections précédentes), à la racine, lancez l'exécutable 
`./gl_dev.out` ou `./gl_dev.exe` (selon le système)
