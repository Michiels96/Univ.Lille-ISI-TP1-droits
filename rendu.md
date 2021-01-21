# Rendu "Les droits d’accès dans les systèmes UNIX"

## Binome

- Michiels Pierre pierre.michiels.etu@univ-lille.fr

- Saulquin Clément clement.saulquin.etu@univ-lille.fr

## Question 1

Réponse:
Non il ne peut pas écrire car lors de l'exécution du processus lancé par toto, l'EUID du processus est comparé avec l'id
de l'utilisateur 'toto' et comme ce sont les mêmes id, on va prendre le triplet des droits du fichier 'titi.txt' (=> 'r--')
Les droits du fichier titi.txt ne permettent pas à l'utilisateur toto d'écrire ('w').
Il est dès lors pas possible pour le processus d'écrire dans le fichier 'titi.txt'.

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
L'utilisateur toto n'a que très peu d'information sur le contenu du fichier. 
Il sait juste que à l'intérieur il y a le fichier data.txt. 
Il ne peut pas avoir plus d'information car la commande lancée par toto 
ne peut pas entrer dans le dossier pour récupérer les informations manquantes.

## Question 3

Réponse:

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
On remarque que les ID de groupe EGID et RGID n'ont pas changé, toto à toujours un RUID a 1001. 
Ce qui change c'est que maintenant, le EUID correspond non plus à celui de toto mais à celui d'ubuntu. 
Le programme vas donc s'executer en faisant croire qu'il à les même permission que l'utilisateur ubuntu. 
Comme ubuntu peut lire le fichier data.txt, le programme va donc pouvoir lire le fichier data.txt sans problème.

## Question 4

Réponse:

Le résultat de la commande **python3 suid.py** est:

```
- EUID : 1001
- EGID : 1000
```

Les valeurs de EUID est donc 1001, l'id de l'utilisateur toto et la valeur de EGID est 1000, 
la valeur de l'utilisateur ubuntu.

## Question 5

Réponse:

**chfn** permet de modifier le nom et les informations associées à un utilisateur particulier.
Le résultat de la commande *ls -al /usr/bin/chfn* est le suivant:

```
-rwsr-xr-x 1 root root 85064 mai   28  2020 /usr/bin/chfn
```

Les informations on bien été mis à jour:
```
toto:x:1001:1000:,2,4012,6012:/home/toto:/bin/bash 
``` 
## Question 6

Réponse:

Le fichier /etc/passwd ne contient aucun mot de passe 
car le fait de stocker des mots de passe dans un fichier qui s'appelle passwd, 
et qui réunis tous les mots de passe serait relativement idiot. 
Les mots de passe sont stocké dans des fichiers cryptés où le chemin (path) est donné dans ce fichier. 
Par exemple le mot de passe pour l'utilisateur toto est stocké en crypté dans /home/toto:/bin/bash.  
L'avantage d'une telle méthode est que cela permet d'augmenter le nombre de fichiers à décrypter 
en cas d'attaque....a mon avis.

## Question 7
Oui, il est nécessaire de créer d'autres utilisateurs 
pour créer des répertoires dans dir_a/dir_b 
pour tester les droits entre utilisateurs du même groupe.

création 2 groupes:
#sudo groupadd groupe_a
#sudo groupadd groupe_b

création compte admin, lambda_a, lambda_a1, lambda_b et lambda_b1
#adduser admin
#adduser lambda_a
#adduser lambda_b
#adduser lambda_a1
#adduser lambda_b1

Affectation des utilisateurs à leurs groupes
#usermod -g groupe_a lambda_a
#usermod -g groupe_b lambda_b

#usermod -g groupe_a lambda_a1
#usermod -g groupe_b lambda_b1

Permet à l'user admin d'aller effacer (ou renommer) des fichiers dans dir_a/dir_b
#usermod -aG groupe_a admin
#usermod -aG groupe_b admin


création des répertoires dir_a, dir_b et dir_c
(en tant que utilisateur lambda_a dans /home/lambda_a)
#mkdir dir_a

droits pour dir_a
#chgrp groupe_a dir_a
#chmod o-rwx dir_a


(en tant que utilisateur lambda_b dans /home/lambda_b)
#mkdir dir_b

droits pour dir_b
#chgrp groupe_b dir_b
#chmod o-rwx dir_b

(en tant qu'utilisateur admin dans /home/admin)
créer le dossier dir_c
#mkdir dir_c

droits pour dir_c
#chmod o+x dir_c
#chmod o-w dir_c

exceptions pour l'utilisateur admin
TODO



Mettre les scripts bash dans le repertoire *question7*.

## Question 8

Le programme et les scripts dans le repertoire *question8*.

## Question 9

Le programme et les scripts dans le repertoire *question9*.

## Question 10

Les programmes *groupe_server* et *groupe_client* dans le repertoire
*question10* ainsi que les tests. 








