import matplotlib
import matplotlib.pyplot as plt

in_file = open ("input_latex.txt", "r")

plt.figure(figsize=(8,6))

str = ""
for s in in_file:
    str = str + s + "\n" 

plt.text(-0.15, 1.13,
    str,
    fontsize = 16, color = "#ff4f00",
    bbox={'facecolor':'#210672', 'alpha':1, 'pad':1000},
         linespacing = 0.5,
         verticalalignment = "top")

#hide axes
fig = matplotlib.pyplot.gca()
plt.savefig('expr.png')
