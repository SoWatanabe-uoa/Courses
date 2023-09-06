#!/bin/bash
rm -rf repos/
user="s1260231"
pass="4Tnkw5zH"
path=$(pwd)
path="$path/repos"
mkdir $path
while read line; do    
    c1=$(echo "$line" | cut -d "," -f 1)
    c2=$(echo "$line" | cut -d "," -f 2)    
    if [ ! -z "$c2" ]; then
        mkdir "repos/$c1"
        git -C "$path/$c1/" clone https://$user:$pass@$c2    
    fi
done < repos.csv
