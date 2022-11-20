#!/bin/bash
./ft_containers > ft
./std_containers > std
diff ft std > diff
rm -rf ft std

if [ ! -s ./diff ]
then
	echo "No diff between std and ft ✅"
else
	echo "Diff between std and ft check diff file for more details ... ❗️"
fi