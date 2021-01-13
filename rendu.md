# Rendu "Les droits d’accès dans les systèmes UNIX"

## Binome

- Michiels Pierre 

- Saulquin Clément clement.saulq1@gmail.com

## Question 1

Réponse

## Question 2

Réponse: L'utilisateur toto n'a pas pu entrer dans le dossier mydir. En effet, nous avons retirer la permission 'x' à ce fichier pour tous les membre du groupe ubuntu. On peut donc déduire que la permission 'x' sur un dossier ne sert pas à exécuter le dossier mais permet de dire si on peut rentrer dedans.
Quand on lance la commande **ls -al mydir** voilà le resultat obtenue.

```
ls: impossible d'accéder à 'mydir/..': Permission non accordée
ls: impossible d'accéder à 'mydir/.': Permission non accordée
ls: impossible d'accéder à 'mydir/data.txt': Permission non accordée
total 0
d????????? ? ? ? ?              ? .
d????????? ? ? ? ?              ? ..
-????????? ? ? ? ?              ? data.txt
```
L'utilisateur toto n'a que très peu d'information sur le contenue du fichier. Il sait juste que à l'intérieur il y a le ficier data.txt. Il ne peut pas avoir plus d'information car la commande lancer par toto ne peut pas entrer dans le dossier pour récupérer les informations manquantes.

## Question 3

Voice le resultat de la commande suid sans avoir activer le flag set-user-id.

```
Affichage des id du programme
- EUID : 1001
- EGID : 1000
- RUID : 1001
- RGID : 1000
Cannot open file on read mode: Permission denied
```
On vois que EUID et RUID ont la même valeur *(1001 qui correspond à l'utilisateur toto)* et EGID et RGID ont aussi la même valeur *(1000 qui correspond au groupe ubuntu)*

Voici le résultat de la commande après avoir activer le flag set-user-id

```
Affichage des id du programme
- EUID : 1000
- EGID : 1000
- RUID : 1001
- RGID : 1000
File open correctly on read mode
```
On remarque que les ID de groupe EGID et RGID n'ont pas changé, toto à toujours un RUID a 1001. Ce qui change c'est que maintenant, le EUID correspond non plus à celui de toto mais à celui d'ubuntu. Le programme vas donc s'executer en faisant croire qu'il à les même permission que l'utilisateur ubuntu. Comme ubuntu peut lire le fichier data.txt, le programme vas donc pouvoir lire le fichier data.txt sans problème.

## Question 4

Réponse

## Question 5

Réponse

## Question 6

Réponse

## Question 7

Mettre les scripts bash dans le repertoire *question7*.

## Question 8

Le programme et les scripts dans le repertoire *question8*.

## Question 9

Le programme et les scripts dans le repertoire *question9*.

## Question 10

Les programmes *groupe_server* et *groupe_client* dans le repertoire
*question10* ainsi que les tests. 








