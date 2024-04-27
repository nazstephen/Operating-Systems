#!/bin/bash

# Functions (must be defined before use)
funcRed() {
echo " This message is from function Red"
}
funcBlue() {
echo " This message is from function Blue" 
}
funcYellow() { 
echo " This message is from function Yellow" 
}

# Beginning of the main script

# prompt the user to get their choice
echo "Enter a color Red, Blue, or Yellow"
read n

# Call the chosen function
func$n
