from wsgiref import headers
import pandas as pd
import matplotlib.pyplot as plt

def check_float(potential_float):
    try:
        float(potential_float)
        return True
    except ValueError:
        return False

class DataStruct():
	def __init__(self) -> None:
		self.__data = dict()
		self.headers = []

	def __repr__(self) -> str:
		s = ""
		for header in self.headers:
			s += header + "\t"
			s += "\n"
		for k, v in self.__data.items():
			for i in v:
				s += i + "\t"
			s += "\n"
		return s.expandtabs(20)

	def data_reading(self, dataset: str):
		try:
			with open(dataset) as f:
				self.headers = f.readline().strip("\n").split(',')
				self.__data = dict([(line.strip().split(',')[0], line.strip().split(',')[1:]) for line in f])
		except:
			raise("Error")
		return self.__data

	def mean_count(self, col):
		tot = 0
		count = 0
		for row in col:
			if (not check_float(row)):
				return 0, 0
			break
		for row in col:
			if (row != ''):
				tot += float(row)
				count += 1
		return tot/count, count
		
	def describe(self):
		for header in self.headers[1:]:
			col = self.view_cols(header)
			mean, count = self.mean_count(col)
			print(header, mean, count, sep="\t")

	def view_data(self):
		fig, ax = plt.subplots(figsize=(5, 2.7), layout='constrained')
		categories = ['Ravenclaw', 'Slytherin', 'Gryffindor', 'Hufflepuff']

	def view_cols(self, col):
		try:
			return [v[self.headers.index(col) - 1] for k, v in self.__data.items()]
		except:
			raise("Errore lettura dataset")
	
if __name__ == "__main__":
	train = "datasets/dataset_train.csv"
	test = "datasets/dataset_test.csv"
	train_set = DataStruct()
	test_set = DataStruct()
	
	train_set.data_reading(train)
	#test_set.data_reading(test)

	#my_col = train_set.view_cols(headers_train, train_df, "First Name")
	#print(train_set)
	train_set.describe()
	#print(my_col)