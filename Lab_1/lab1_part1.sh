# Name: Carlo Bilbao 
# # Date: 1/12/23 
# # Title: Lab1 – Unix/Linux Commands 
# # Description: This program computes displayes various 
# # pieces of information about the user running the program

#Sample shell program for the Lab assignment
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$

user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "salagtash" ] #use your username instead of salagtash
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!" 
        exit 1
fi
