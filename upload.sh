#!/bin/sh
now="$(date +'%d/%m/%Y')"
cd Desktop/keystroke
git add .
git commit -m now
git push -u origin master
echo Press Enter...
read