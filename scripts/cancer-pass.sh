#!/bin/bash
(cd "${0%/*}" && cd ..)
clusters=$1

num_of_attributes=9
data_file="datasets/cancer-data.txt"

touch tmp/out$1

for ((seed=1;seed<=100;seed++)); do
    cat $data_file | ./scripts/split.sh 10 kmeans $seed $clusters $num_of_attributes; done >> tmp/out$1
