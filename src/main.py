#!/usr/bin/env python
import rospy
from std_msgs.msg import String, Empty
import os

def chatter_callback1(message):
    #get_caller_id(): Get fully resolved name of local node
    s=str(message)
    #print(list(s.split('"'))[1])
    s=list(s.split('"'))[1]
    print(s)
    s='robo 1 finished'
    if(s=='robo 1 finished'):
        talker2()
        print('ayo you moving mad fam')

def chatter_callback2(message):
    #get_caller_id(): Get fully resolved name of local node
    s=str(message)
    #print(list(s.split('"'))[1])
    s=list(s.split('"'))[1]
    print(s)
    if(s=='robo 2 finished'):
        print('Program over')
        exit()


def such():
    print("Hello I am sacchin")

def talker1():
    pub = rospy.Publisher('chatter', Empty, queue_size=10)
    rospy.init_node('main', anonymous=True)
    rate = rospy.Rate(1) # 1hz
    i = 0
    while not rospy.is_shutdown():
        hello_str = "Publishing finished for bot 1"
        rospy.loginfo(hello_str)
        pub.publish()
        rate.sleep()
        i=i+1
        if i==5:
            break
    such()
    listener1()

def talker2():
    pub = rospy.Publisher('chatter2', Empty, queue_size=10)
    # rospy.init_node('talker2', anonymous=True)
    rate = rospy.Rate(1) # 1hz
    i = 0
    while not rospy.is_shutdown():
        hello_str = "Publishing Finished for bot 2"
        rospy.loginfo(hello_str)
        pub.publish()
        rate.sleep()
        i=i+1
        if i==10:
            break
    such()
    listener2()

def listener1():
    # rospy.init_node('listener1', anonymous=True)
    rospy.Subscriber("chatter1", String,chatter_callback1)
    rospy.spin()
    print('end')

def listener2():
    # rospy.init_node('listener2', anonymous=True)
    rospy.Subscriber("chatter3", String,chatter_callback2)
    rospy.spin()
    print('end')

if __name__ == '__main__':
    # listener()
    talker1()