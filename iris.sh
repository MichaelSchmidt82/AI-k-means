#!/bin/bash
cluster_max=140
num_of_attributes=4
data_file="datasets/iris-data.txt"
out="iris-results.txt"

echo "Clustering has started."
for ((cluster=1; cluster<=$cluster_max; cluster++)); do
	./scripts/iris-pass.sh "$cluster"
	echo "finished clustering ($cluster)"
done

paste out{1..140} > tmp/$out
rm tmp/out*
echo "finished."
