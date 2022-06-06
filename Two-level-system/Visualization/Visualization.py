import matplotlib.pyplot as plt;

file1 = open("../Computation/graph1.txt", "r")
file2 = open("../Computation/graph2.txt", "r")
config = open("../Computation/config.txt", "r")

lines1 = file1.readlines()
lines2 = file2.readlines()
configlines = config.readlines()

datasetX1 = []
datasetY1 = []
datasetX2 = []
datasetY2 = []
maxTime = 1

for line in lines1:
    splited = line.split()
    datasetX1.append(float(splited[0]))
    datasetY1.append(float(splited[1]))

for line in lines2:
    splited = line.split()
    datasetX2.append(float(splited[0]))
    datasetY2.append(float(splited[1]))

for line in configlines:
    splited = line.split()
    if splited[0] == "maxTime:":
        maxTime = float(splited[1])

file1.close()
file2.close();

fig = plt.figure()
fig.set_figheight(5)
fig.set_figwidth(15)
ax = fig.add_subplot(111)
ax.plot(datasetX1, datasetY1, datasetX2, datasetY2)
ax.set_ylim([0, 1.1])
ax.set_xlim([0, maxTime])
ax.set_xlabel("time")
ax.set_ylabel("probability")
plt.grid();
plt.show()