#!/bin/sh
now="$(date +'%d/%m/%Y')"
git add .
git commit -m now
git push -u origin master
echo Done. Press Enter...
read