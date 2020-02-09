import numpy as np
import scipy.spatial.distance

a = [4, 3, 4, np.nan, np.nan, 1]
b = [4,1,2,2,np.nan,1]
c = [4, np.nan, np.nan, 3,1, np.nan]
d = [1,4,2,np.nan,4,np.nan]
e = [1, np.nan, 3,1,3,2]


def sim(a,b):
	print(f"a: {a}")
	print(f"b: {b}")
	a_m = np.nanmean(a)
	b_m = np.nanmean(b)
	print(f"a_m: {a_m}")
	print(f"b_m: {b_m}")
	
	aa = [x-a_m if x is not np.nan else 0 for x in a]
	bb = [x-b_m if x is not np.nan else 0 for x in b]
	
	res = 1 - scipy.spatial.distance.cosine(aa, bb)
	return res
	
def sim2(a,b):
	print(f"a: {a}")
	print(f"b: {b}")
	a_m = np.nanmean(a)
	b_m = np.nanmean(b)
	print(f"a_m: {a_m}")
	print(f"b_m: {b_m}")
	
	l=0
	m=0
	for x,y in zip(a,b):
		if x is not np.nan and y is not np.nan:
			l += (x-a_m) * (y-b_m)
			m += np.abs(x-a_m) * np.abs(y-b_m)
	return l/m

def predict(a,x,y,n):
	"""
		Predict weighted value
		a : user array of rates
		b : first closest similar
		c : second closest similar
		n : index of to be predicted rate
	"""
	a_m = np.nanmean(a)
	x_m = np.nanmean(x)
	y_m = np.nanmean(y)
	xx = sim2(a,x) * (x[n] - x_m)
	yy = sim2(a,y) * (y[n] - y_m)
	print(xx)
	print(yy)
	return a_m + (xx + yy / (sim2(a,x) + sim2(a,y)))
	
	
print(f"sim(a,b) = {sim2(a,b)}")
print(f"sim(a,c) = {sim2(a,c)}")
print(f"sim(a,d) = {sim2(a,d)}")
print(f"sim(a,e) = {sim2(a,e)}")

print(f"predict(a,b,c,3): {predict(a,b,c,3)}")
