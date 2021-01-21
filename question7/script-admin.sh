#!/bin/bash
echo 'USER admin:'

echo -e '\n\tlecture fichier et sous-répertoires dans dir_c:'
cat /home/admin/dir_c/file.txt
cat /home/admin/dir_c/tmp/file.txt
echo -e '\tOK'


echo -e '\n\n\tPossibilité de modifier/créer des fichiers dans tte larborescence dans dir_c:'

echo -e '\n\tMODIFY File'
cat /home/admin/dir_c/file.txt
echo 'file.txt in dir_c readed! MODIFIED' > /home/admin/dir_c/file.txt
echo -e '\tafter modify:'
cat /home/admin/dir_c/file.txt

echo -e '\n\tCREATE File'
ls -la /home/admin/dir_c/
touch /home/admin/dir_c/newFile.txt
echo -e '\tafter create:'
ls -la /home/admin/dir_c/




echo -e '\n\n\tPossibilité de modifier/créer des fichiers dans tte larborescence dans dir_a:'

echo -e '\n\tRENAME File'
ls -la /home/lambda_a/dir_a/
mv /home/lambda_a/dir_a/newFile.txt /home/lambda_a/dir_a/newNewFile.txt
echo -e '\tafter create:'
ls -la /home/lambda_a/dir_a/

echo -e '\n\tDELETE File'
ls -la /home/lambda_a/dir_a/
rm /home/lambda_a/dir_a/newFile.txt
echo -e '\tafter delete:'
ls -la /home/lambda_a/dir_a/
