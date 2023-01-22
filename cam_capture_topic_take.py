#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv2
import os
import datetime

class TakePhoto:

    def __init__(self):
        self.bridge = CvBridge()
        self.cv_image = None
        self.image_sub = rospy.Subscriber("/usb_cam/image_raw", Image, self.image_callback)
        self.take_photo_sub = rospy.Subscriber("/take", String, self.take_callback)
        self.image_path = os.path.expanduser("~/Downloads")

    def image_callback(self, data):
        try:
            self.cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

    def take_callback(self, data):
        if data.data == "ok":
            if self.cv_image is not None:
                timestamp = datetime.datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
                file_name = "webcam_photo_" + timestamp + ".jpg"
                file_path = os.path.join(self.image_path, file_name)
                cv2.imwrite(file_path, self.cv_image)
                rospy.loginfo("Saved webcam photo to: {}".format(file_path))
            else:
                rospy.loginfo("No image received yet.")

if __name__ == '__main__':
    rospy.init_node("webcam_photo")
    TakePhoto()
    rospy.spin()
