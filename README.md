imgsvr, udp based image server for foscams 
Use udp protocol to establish a server that allows requests for images and transfer the requested images
back to the client. The protocol will initially involve sending an integer number this number will repreent
the latest N images taken by the camera. 
