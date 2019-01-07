FILENAME = 'facts-nns.csv'
RESULT_SIZE = 100
RESULT_FILENAME = 'result.txt'
NEIGHBOURS_COUNT = 100

def jaccard(a: set, b: set):
	inter = len(a.intersection(b))
	union = len(a) + len(b) - inter
	return inter / union

class User:
	__slots__ = ['id', 'songs', 'similarity']
	
	def __init__(self, user_id: int, songs: set):
		self.id = user_id
		self.songs = songs
		self.similarity = []
		
	def add_similar(self, user_id: int, distance):
		self.similarity.append([user_id, distance])

class UserProvider:
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
					result = User(self.last_user, songs)
					self.last_user = user
					self.last_song = song
					return result
			except:
				result = User(self.last_user, songs)
				self.ended = True
				self.f.close()
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
		
def write_result(user, f):
	print("User = {}".format(user.id), file=f)
	print("{:7d} {:7.5f}".format(user.id, 1.0), file=f)
	for record in sorted(user.similarity, key= lambda x: (x[1], x[0]), reverse=True)[:NEIGHBOURS_COUNT - 1]:
		print("{:7d} {:7.5f}".format(record[0], record[1]), file=f)

if __name__=="__main__":
	f = open(RESULT_FILENAME, 'w')
	up = UserProvider(FILENAME)
	users = up.all()
	for j in range(RESULT_SIZE):
		user = users.pop(0)
		print("User = {}".format(user.id))			
		for i in range(len(users)):
			other = users[i]
			similarity = jaccard(user.songs, other.songs)
			if similarity == 0.0:
				continue
			user.add_similar(other.id, similarity)
			if i < RESULT_SIZE:
				other.add_similar(user.id, similarity)
		write_result(user, f)
	f.close()
	print("Koniec")

