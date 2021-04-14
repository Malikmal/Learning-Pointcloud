#!/usr/bin/env python3
import cv2
import mediapipe as mp
import rospy
from std_msgs.msg import String
from cv_bridge import CvBridge


mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands


# def talker():
#       pub = rospy.Publisher('chatter', String, queue_size=10)
#       rospy.init_node('talker', anonymous=True)
#       rate = rospy.Rate(10) # 10hz
#       while not rospy.is_shutdown():
#         hello_str = "hello world %s" % rospy.get_time()
#         rospy.loginfo(hello_str)
#         pub.publish(hello_str)
#         rate.sleep()

# if __name__ == '__main__':
#     try:
#         talker()
#     except rospy.ROSInterruptException:
#         pass

# For webcam input:
cap = cv2.VideoCapture(0)
with mp_hands.Hands(
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5) as hands:
  while cap.isOpened():
    success, image = cap.read()
    if not success:
      print("Ignoring empty camera frame.")
      # If loading a video, use 'break' instead of 'continue'.
      continue

    # Flip the image horizontally for a later selfie-view display, and convert
    # the BGR image to RGB.
    image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
    # To improve performance, optionally mark the image as not writeable to
    # pass by reference.
    image.flags.writeable = False
    results = hands.process(image)

    # Draw the hand annotations on the image.
    image.flags.writeable = True
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    if results.multi_hand_landmarks:
      for hand_landmarks in results.multi_hand_landmarks:
        mp_drawing.draw_landmarks(
            image, hand_landmarks, mp_hands.HAND_CONNECTIONS)
    cv2.imshow('MediaPipe Hands', image)

    bridge = CvBridge()
    cv_image = bridge.imgmsg_to_cv2(image, desired_encoding='passthrough')
    rospy.Subscriber("image_topic",cv_image)

    if cv2.waitKey(5) & 0xFF == 27:
      break
cap.release()
