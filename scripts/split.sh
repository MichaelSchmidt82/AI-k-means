#!/bin/bash
## Parameters Received:
# $1 test case
# $2 program
# 3 seed
# 4 cluster count
# 5 attribute count
# 6 additional flags from calling script

(cd "${0%/*}" && cd ../)

## Set a value for test cases
N=$1
shift

## Create a command string
base_cmd="$1 $2 $3 $4"
shift 4
flags=$@

## $@ contains the rest of the parameter

## Grab data from standard input
cat | shuf > tmp/temp.$$.txt

## All but last N
head -n -${N} tmp/temp.$$.txt > tmp/temp.$$.train.txt

## Only last N
tail -n ${N} tmp/temp.$$.txt > tmp/temp.$$.test.txt

## Run command with split data and flags appended
./$base_cmd tmp/temp.$$.train.txt tmp/temp.$$.test.txt $flags

## Remove temporary files
rm tmp/temp.$$.*
