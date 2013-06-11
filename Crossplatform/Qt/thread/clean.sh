#/bin/bash

proname=$(ls *.pro)
name=${proname%.pro}

rm -fr ./debug
rm -fr ./release
rm -f ./${name}
rm -f ./*.pro.user
rm -f ./moc_*
rm -f ./Makefile*
rm -f ./*.o
backups=$(ls *~)
for arg in $backups ; do
  rm ${arg}
done
