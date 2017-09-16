import os

def getKey(x) :
	return int(x[1])

rootdir = 'Graph'
list = os.listdir(rootdir)

list2 = []

for filetxt in list :
	tmpEle = []
	tmpEle.append(filetxt)
	file = open('Graph/' + filetxt, 'r')
	try :
		haha = file.readline().split()
		tmpEle.append(haha[2])
		tmpEle.append(haha[3])
		list2.append(tmpEle)
	finally :
		file.close()

list2.sort(key = getKey)

for ele in list2:
	print(ele)

for filetxt in list2 :
	file = filetxt[0][:len(filetxt[0]) - 4]
	print(filetxt)
	os.system('./comple Graph/' + file + '.txt')
	print(file + ' converted to complementary graph is done')
	os.system('./KPLEX alpha/' + file + '.txt')
	print(file + ' alpha calculating is done')

	alpha_file = open('alpha/' + file + '.txt', 'r')
	tmp = ''
	try :
		tmp = alpha_file.read()
	finally :
		alpha_file.close()
	if (tmp == '-1') :
		print('alpha getting failed')
	else :
		print('alpha getting successed')
		print('alpha = ' + tmp)
		os.system('./MaxBG alpha/' + file + '.txt ' + 'Graph/' + file + '.txt ' + 'Out/' + file + '.txt')
		print('MaxBG ' + file + ' done')
		print('----------------')

	