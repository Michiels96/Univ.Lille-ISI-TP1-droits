#!/bin/bash
echo 'USER lambda_a:'
echo -e '\tlecture fichier et sous-répertoires dans dir_a:'
#ls -al /home/lambda_a/dir_a
cat /home/lambda_a/dir_a/file.txt
cat /home/lambda_a/dir_a/tmp/file.txt
echo -e '\tOK'

echo -e '\n\tlecture fichier et sous-répertoires dans dir_c:'
#ls -al /home/admin/dir_c
cat /home/admin/dir_c/file.txt
cat /home/admin/dir_c/tmp/file.txt
echo -e '\tOK'



echo -e '\n\n\tImpossibilité à supp/renommer/modifier/créer fichiers dans dir_c:'
echo -e '\n\tMODIFY'
echo -e 'content of file:'
cat /home/admin/dir_c/doNotRenameDeleteOrModify.txt
echo 'abc' > /home/admin/dir_c/doNotRenameDeleteOrModify.txt
echo -e '\tafter modify: (should be the same)'
cat /home/admin/dir_c/doNotRenameDeleteOrModify.txt

echo -e '\n\tRENAME'
ls -la /home/admin/dir_c/
mv /home/admin/dir_c/doNotRenameDeleteOrModify.txt /home/admin/dir_c/mod.txt
echo -e '\tafter rename:'
ls -la /home/admin/dir_c/


echo -e '\n\tDELETE'
ls -la /home/admin/dir_c/
rm -f /home/admin/dir_c/doNotRenameDeleteOrModify.txt
echo -e '\tafter delete:'
ls -la /home/admin/dir_c/


echo -e '\n\tCREATE'
ls -la /home/admin/dir_c/
touch /home/admin/dir_c/newFile.txt
echo -e '\tafter create:'
ls -la /home/admin/dir_c/



echo -e '\n\n\tPossibilité de modifier un fichier et créer des fichiers/repertoires dans tte larborescence dans dir_a:'

echo -e '\n\tMODIFY File'
cat /home/lambda_a/dir_a/file.txt
echo 'file.txt in dir_a readed! MODIFIED' > /home/lambda_a/dir_a/file.txt
echo -e '\tafter modify:'
cat /home/lambda_a/dir_a/file.txt

echo -e '\n\tCREATE File'
ls -la /home/lambda_a/dir_a/
touch /home/lambda_a/dir_a/newFile.txt
echo -e '\tafter create:'
ls -la /home/lambda_a/dir_a/

echo -e '\n\tCREATE Repository'
ls -la /home/lambda_a/dir_a/
mkdir /home/lambda_a/dir_a/newRepo
echo -e '\tafter create:'
ls -la /home/lambda_a/dir_a/



echo -e '\n\n\tImpossibilité de renommer/supprimer un fichier dun autre utilisateur du meme groupe dans tte larborescence dans dir_a:'


echo -e '\n\tRENAME File'
ls -la /home/lambda_a/dir_a/
mv /home/lambda_a/dir_a/lambda_a1File.txt /home/lambda_a/dir_a/lambda_a11File.txb
echo -e '\tafter rename:'
ls -la /home/lambda_a/dir_a/

echo -e '\n\tDELETE File'
ls -la /home/lambda_a/dir_a/
rm /home/lambda_a/dir_a/lambda_a1File.txt
echo -e '\tafter delete:'
ls -la /home/lambda_a/dir_a/




echo -e '\n\n\tImpossibilité de lire/modifier/supprimmer/créer un fichier dans dir_b:'

echo -e '\n\tREAD File'
cat /home/lambda_b/dir_b/lambda_b1File.txt

echo -e '\n\tMODIFY File'
cat /home/lambda_b/dir_b/lambda_b1File.txt
echo 'lambda_b1File.txt in dir_b readed! MODIFIED' > /home/lambda_b/dir_b/lambda_b1File.txt
echo -e '\tafter modify:'
cat /home/lambda_b/dir_b/lambda_b1File.txt

echo -e '\n\tDELETE File'
ls -la /home/lambda_b/dir_b/
rm /home/lambda_b/dir_b/lambda_b1File.txt
echo -e '\tafter delete:'
ls -la /home/lambda_b/dir_b/

echo -e '\n\tCREATE File'
ls -la /home/lambda_b/dir_b/
touch /home/lambda_b/dir_b/newFileFrom_lambda_a.txt
echo -e '\tafter create:'
ls -la /home/lambda_b/dir_b/