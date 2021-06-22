import time
import numpy as np

#100x100 arrays with float values between 0 and 100
A = [[np.random.random()*100] * 500 for i in range(500)]
B = [[np.random.random()*100] * 500 for i in range(500)]
C = [[0]*500 for i in range(500)]

#Multiply and track elapsed time
starttime = time.time()
for i in range(500):
	for j in range(500):
		for k in range(500):
			C[i][j] = A[i][k] * B[k][j]
endtime = time.time()

print(endtime - starttime)