import rospy
from std_msgs.msg import Int64
from geometry_msgs.msg import Twist
import random
import time

x = 0
publisher = rospy.Publisher("/cmd_vel", Twist, queue_size=10)

def callback(data):
	# For capturing data
	global x
	x = data.data
	
def talker():
	global x
	rospy.init_node("chatter", anonymous = True)
	rospy.Subscriber("chatter", Int64, callback = callback)
	while True:
		# Capture data
		ones = x % 10;
		tens = (int)(x / 10);

		lin_x = 0.3 * (tens - 1)
		rot_x = 0.3 * (ones - 1)

		# Construct a twist data structure
		twist = Twist()
		twist.linear.x = lin_x
		twist.angular.z = rot_x

		# Send it to the vehicle in simulation
		publisher.publish(twist)
		time.sleep(0.1)

	rospy.spin()

if __name__ == "__main__":
	talker()
