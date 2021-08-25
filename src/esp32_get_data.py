#!/usr/bin/env python
import rospy
from std_msgs.msg import String

def chatter_callback(message):
    #get_caller_id(): Get fully resolved name of local node
    s=str(message)
    print(list(s.split('"'))[1])
    print(s)
def listener():
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber("chatter", String,chatter_callback)
    rospy.spin()
if __name__ == '__main__':
    listener()