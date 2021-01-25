#!/bin/bash
echo -e 'Test question 8 - suppression de fichiers'

echo -e '\n\tDELETE  - lambda_a user deleting in lambda_bs dir_b file.txt'
echo 'before delete:'
ls -la /home/lambda_b/dir_b/
sh /home/admin/a.out /home/lambda_b/dir_b/file.txt
echo -e '\tafter rename:'
ls -la /home/lambda_b/dir_b/