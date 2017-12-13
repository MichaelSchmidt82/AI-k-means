#!/bin/bash
cluster_max=95
num_of_attributes=9
data_file="datasets/cancer-data.txt"
out="cancer-results.txt"

echo "Clustering has started."
for ((cluster=1; cluster<=$cluster_max; cluster++)); do
	./cancer-pass.sh "$cluster"
	echo "finished clustering ($cluster)"
done

paste out{1..95} > $out
rm out*
echo "finished."
