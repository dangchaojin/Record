#!/bin/sh

# 1. change source

# 2. sudo passwd root;

echo "1" | sudo -S apt-get update;

echo "1" | sudo -S apt-get install vim;

echo "1" | sudo -S apt-get install git;

echo "1" | sudo apt-get install cloc;

echo "1" | sudo apt-get install tree;