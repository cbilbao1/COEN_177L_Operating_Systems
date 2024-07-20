# Name: Carlo Bilbao 
# Date: 1/12/23 
# Title: Lab1 – Unix/Linux Commands 
# Description: This program computes the area of a 
# rectangle with given dimensions by the user

response="Yes"
while [ $response != "No" ]
do
        echo "Enter height of rectangle: "
        read height
        echo "Enter width of rectangle: "
        read width
        area=`expr $height \* $width`
	
        echo "The perimeter of the rectangle is $((height + height + width + width))"
	echo "The area of the rectangle is $area"

	echo "Would you like to repeat for another rectangle [Yes/No]?"
        read response
done

#Calculate the area and perimeter of a circle given a radius
response="Yes"
while [ $response != "No" ]
do
        echo "Enter radius of circle: "
        read radius
        echo "The perimeter of the circle is "
	echo "2.0 * 3.14 * $radius"|bc
	echo "The area of the circle is "
	echo "3.14 * $radius * $radius"|bc
	
	echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done
