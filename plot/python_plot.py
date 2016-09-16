from matplotlib import pylab

def plot(filename):
	f = open(filename, 'r')
	data = [each.rstrip("\r\n") for each in f.readlines()]
	truevoltage, measuredvoltage, kalman = [] , [], []
	numsteps = 0
	for each in data:
		t, m, k = each.split(",")
		truevoltage.append(float(t))
		measuredvoltage.append(float(m))
		kalman.append(float(k))
		numsteps+=1
	pylab.plot(range(numsteps),measuredvoltage,'b',range(numsteps),truevoltage,'r',range(numsteps),kalman,'g')
	pylab.xlabel('Time')
	pylab.ylabel('Voltage')
	pylab.title('Voltage Measurement with Kalman Filter')
	pylab.legend(('measured','true voltage','kalman'))
	pylab.show()


if __name__ == '__main__':
        import sys
        try:
                args = sys.argv[1]
        except:
                args = "../KalmanFilter/dummy.txt"
	plot(args);
