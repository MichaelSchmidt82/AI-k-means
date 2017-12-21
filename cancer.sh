#!/bin/bash
cd "${0%/*}"

cluster_max=95
num_of_attributes=9
data_file="datasets/cancer-data.txt"
out="cancer-results.txt"

echo "Clustering has started."
for ((cluster=1; cluster<=$cluster_max; cluster++)); do
	./scripts/cancer-pass.sh "$cluster"
	echo "finished clustering ($cluster)"
done

paste tmp/out{1..95} > $out
rm tmp/out*
echo "finished."
