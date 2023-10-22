#!/usr/bin/bash

curl -s https://cseweb.ucsd.edu/\~jmcauley/datasets/amazon_v2/ >urls.txt

# Categories to avoid
avoid_categories=("Books" "Movies_and_TV" "Prime_Pantry" "Software" "Kindle_Store" "Digital_Music" "CDs_and_Vinyl" "Magazine_Subscriptions")

# Create a single exclusion pattern for egrep
exclude_pattern=$(
    IFS="|"
    echo "${avoid_categories[*]}"
)

cat urls.txt | egrep categoryFilesSmall | egrep '.json.gz' | egrep -o '\"http.*?"' | sed 's/\"//g' | egrep -v "$exclude_pattern" >reviews_urls.txt
cat urls.txt | egrep metaFiles2 | egrep '.json.gz' | egrep -o '\"http.*?"' | sed 's/\"//g' | egrep -v "$exclude_pattern" >meta_urls.txt

mkdir -p ../data/reviews
mkdir -p ../data/meta

npd=5

aria2c -c -s $npd -x $npd -d ../data/reviews -i reviews_urls.txt --conditional-get=true --auto-file-renaming=false --no-conf=true
aria2c -c -s $npd -x $npd -d ../data/meta -i meta_urls.txt --conditional-get=true --auto-file-renaming=false --no-conf=true
