#!/bin/bash
echo -e 'Test question 8 - suppression de fichiers'

echo -e '\n\tDELETE  - lambda_b user deleting in lambda_as dir_a file.txt'
echo 'before delete:'
ls -la /home/lambda_a/dir_a/
sh /home/admin/a.out /home/lambda_a/dir_a/file.txt
echo -e '\tafter rename:'
ls -la /home/lambda_a/dir_a/file.txt