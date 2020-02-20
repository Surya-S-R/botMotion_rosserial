#!/usr/bin/env python


import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import String

rospy.init_node("twistMessage_to_rosSerial")
pub = rospy.Publisher('Bot_movement_cmd',String)

def callBack(msg):
    print(msg)
    
    if msg.linear.x == 2:
        pub.publish("F")
        print("Moving forward.....")
    if msg.linear.x == -2:
        pub.publish("B")
        print("Moving backward.....")

    if msg.angular.z == 2:
        pub.publish("L")
        print("Turning Left.....")
    if msg.angular.z == -2:
        pub.publish("R")
        print("Turning Right.....")
    print("------")

sub = rospy.Subscriber('/turtle1/cmd_vel',Twist,callback=callBack)








rospy.spin()