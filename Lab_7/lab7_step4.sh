# Name: Carlo Bilbao 
# Date: 1/12/23 
# Title: Lab7 – Unix/Linux Commands 
# Description: This program will be running our test cases 
# for the FIFO, LRU, and Second Chance page replacement
# algorithms

#Sample shell program for the Lab assignment
#!/bin/bash
make;
echo "----------FIFO----------"
cat testInput.txt | ./lab7_step3_FIFO 10
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./lab7_step3_LRU 10
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./lab7_step3_SEC 10
echo "----------End Second Chance----------"

echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat testInput10k.txt | ./lab7_step3_FIFO 10 | wc -l
cat testInput10k.txt | ./lab7_step3_FIFO 50 | wc -l
cat testInput10k.txt | ./lab7_step3_FIFO 100 | wc -l
cat testInput10k.txt | ./lab7_step3_FIFO 250 | wc -l
cat testInput10k.txt | ./lab7_step3_FIFO 500 | wc -l
echo

echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat testInput10k.txt | ./lab7_step3_LRU 10 | wc -l
cat testInput10k.txt | ./lab7_step3_LRU 50 | wc -l
cat testInput10k.txt | ./lab7_step3_LRU 100 | wc -l
cat testInput10k.txt | ./lab7_step3_LRU 250 | wc -l
cat testInput10k.txt | ./lab7_step3_LRU 500 | wc -l
echo

echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat testInput10k.txt | ./lab7_step3_SEC 10 | wc -l
cat testInput10k.txt | ./lab7_step3_SEC 50 | wc -l
cat testInput10k.txt | ./lab7_step3_SEC 100 | wc -l
cat testInput10k.txt | ./lab7_step3_SEC 250 | wc -l
cat testInput10k.txt | ./lab7_step3_SEC 500 | wc -l
echo

make clean;
echo
