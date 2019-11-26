#!/bin/bash


##first implementation
mkfifo firstPipe
exec 33<>firstPipe
mkfifo secondPipe
exec 53<>secondPipe

./riddle 34>&33 54>&53

rm firstPipe secondPipe

##second implementation
#mkfifo firstPipe
#mkfifo secondPipe

#exec 33<>firstPipe
#exec 34<>firstPipe
#exec 53<>secondPipe
#exec 54<>secondPipe

#./riddle

#rm firstPipe secondPipe
