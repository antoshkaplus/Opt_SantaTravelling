

from matplotlib import pyplot as plt
f = open('/Users/antoshkaplus/Documents/Programming/Contests/Kaggle/SantaProblem/Santa/Results/santa.cvs','r')
str = f.read()
f.close()
path1,path2 = zip(*map(lambda x: map(int,x.split(',')),str.split('\n')[:-1]))
f = open('/Users/antoshkaplus/Documents/Programming/Contests/Kaggle/SantaProblem/Santa/Samples/santa.tsp','r')
str = f.read()
f.close()
ps = map(lambda x: map(int,x.split(' ')[1:]),str.split('\n')[:-1])
x1, y1 = zip(*[ps[p] for p in path1])
x2, y2 = zip(*[ps[p] for p in path2])
#plt.plot(x1,y1,'r',(x1[0],x1[-1]),(y1[0],y1[-1]),'r')
plt.plot(x2,y2,'g',(x2[0],x2[-1]),(y2[0],y2[-1]),'g')
plt.show()