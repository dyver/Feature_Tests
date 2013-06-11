#/bin/bash

proname=$(ls *.pro)
name=${proname%.pro}

rm -fr ./debug
rm -fr ./release
rm -f ./lib${name}.so
rm -f ./${name}
rm -f ./${name}.pro.user*
rm -f ./moc_*
rm -f ./ui_*.h
rm -f ./Makefile*
rm -f ./*.o
backups=$(ls *~)
for arg in $backups ; do
  rm ${arg}
done
