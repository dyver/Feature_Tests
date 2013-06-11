#!/bin/bash

. clean.sh
rm *.pro
qmake -project
echo "QT += widgets" >> *.pro
qmake
