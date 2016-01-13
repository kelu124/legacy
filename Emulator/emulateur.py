import socket
import time
import sys
import numpy as np
from operator import itemgetter, attrgetter
from math import *


usleep = lambda x: time.sleep(x/1000000.0)

try:
    sys.argv[1]
except NameError:
    fichier = 'Missing an arg'
else:
    fichier = sys.argv[1]

UDP_IP = "127.0.0.1"
UDP_PORT = 5005

print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
i = 0

with open(fichier, 'r') as echOpenLog:
	for line in echOpenLog:
		line = line.split('\t')
		del line[-1]
		#On prepare le packet
		line = np.array(line).astype(int)
		#conversion en int
		#et on tire
		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
		sock.sendto(line, (UDP_IP, UDP_PORT))
		dodo = 1000*(line[6]-line[5])
		if dodo > 333*1000:
			dodo = 333
		i=i+1
		print i, "\t(sleep: ",dodo/1000,"ms)"
		usleep(dodo)

