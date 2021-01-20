#!/bin/bash
echo 'USER admin:'
echo -e '\tlecture fichier et sous-répertoires dans dir_b:'
cat /home/lambda_b/dir_b/file.txt
cat /home/lambda_b/dir_b/tmp/file.txt
echo -e '\tOK'

echo -e '\n\tlecture fichier et sous-répertoires dans dir_c:'
cat /home/admin/dir_c/file.txt
cat /home/admin/dir_c/tmp/file.txt
echo -e '\tOK'

TODO