from pprint import pprint
FILENAME = 'facts-nns.csv'
RESULT_SIZE = 100
RESULT_FILENAME = 'result.txt'
NEIGHBOURS_COUNT = 100

def jaccard(a: set, b: set):
	return len(a.intersection(b)) / len(a.union(b))


class UserProvider():
	def __init__(self, fn):
		self.f = open(fn)
		self.f.readline()
		self.last_user, self.last_song = self._get_row()
		self.ended = False
		
	def next(self):
		if self.ended:
			return None
			
		songs = {self.last_song}
		while True:
			try:
				user, song = self._get_row()
				if user == self.last_user:
					songs.add(song)
				else:
					result = [self.last_user, songs]
					self.last_user = user
					self.last_song = song
					return result
			except:
				result = [self.last_user, songs]
				self.ended = True
				return result
			
	def all(self):
		users = []
		while True:
			print(len(users))
			user = self.next()
			if user is None:
				return users
			users.append(user)
		
	def _get_row(self):
		a, b = self.f.readline()[:-1].split(',')
		return [int(a), int(b)]
			
def write_results(users):
	with open(RESULT_FILENAME, 'w') as f:
		for i in range(1, RESULT_SIZE + 1):
			print("User = {}".format(i), file=f)
			print("{:7d} {:7.5f}".format(i, 1.0), file=f)
			for record in sorted(users[i], key= lambda x: (x[1], x[0]), reverse=True)[:NEIGHBOURS_COUNT - 1]:
				print("{:7d} {:7.5f}".format(record[0], record[1]), file=f)

if __name__=="__main__":
	up = UserProvider(FILENAME)
	users = up.all()
	users_similarity = {}
	for j in range(RESULT_SIZE):
		print("j: {}".format(j))
		if users[j][0] not in users_similarity.keys():
			users_similarity[users[j][0]] = []
			
		for i in range(j + 1, len(users)):
			similarity = jaccard(users[j][1], users[i][1])
			if similarity == 0.0:
				continue
			users_similarity[users[j][0]].append([users[i][0], similarity])
			if i < RESULT_SIZE:
				if users[i][0] not in users_similarity.keys():
					users_similarity[users[i][0]] = []
				users_similarity[users[i][0]].append([users[j][0], similarity])

	write_results(users_similarity)
	print("Koniec: ")
			
