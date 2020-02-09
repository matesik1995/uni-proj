import scipy.spatial.distance as dist
import numpy as np

# TF matrix
d1 = [1, 0, 1, 0, 1, 0, 1, 0, 0]
d2 = [1, 0, 0, 0, 1, 1, 1, 1, 0]
d3 = [0, 0, 0, 0, 1, 1, 1, 0, 1]
d4 = [1, 1, 0, 1, 1, 0, 0, 0, 1]
docs = [d1, d2, d3, d4]


# cosine similarity based on TF matrix and query
q = [0, 0, 0, 0, 0, 1, 1, 0, 0]

print(f"Cosine similarity to q {q}")
for i, d in enumerate(docs):
	print(f"d{i+1}: {1-dist.cosine(q, d)}")
	
	
# TF-IDF from TF
print("TF.IDF from TF")
def tf_idf(docs):
	tf = []
	hits = []
	for j in range(len(docs[0])):
		c = 0
		for i in range(len(docs)):
			if docs[i][j] == 1:
				c += 1
		hits.append(c)

	for i in range(len(docs)):
		tf.append([])
		for j in range(len(docs[i])):
			tf[-1].append(docs[i][j] * np.log(len(docs)/hits[j]))
	return tf

tf = tf_idf(docs)
for t in tf:
	print(t)
	
# cosine similarity after TF.IDF
q = [0, 0, 0, 0, 0, 1, 1, 0, 0]
def tf_val(tf, n):
	for t in tf:
		if t[n] != 0:
			return t[n]
	return 0
	
q_tf = [tf_val(tf, i) if x == 1 else 0 for i, x in enumerate(q)]
print(f"Cosine similarity after tfidf to q {q_tf}")
for i, d in enumerate(tf):
	print(f"d{i+1}: {1-dist.cosine(q_tf, d)}")
