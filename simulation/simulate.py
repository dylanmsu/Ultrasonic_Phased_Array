import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
from matplotlib.animation import FuncAnimation

source = 10
#sources = [-3*source, -2*source, -source, 0, source, 2*source, 3*source]
sources = np.linspace(-20.0, 20.0, 5)
axlim = max(sources)*2 + 1
N = 1000
f = 1

x = np.linspace(-axlim, axlim, N)
y = np.linspace(-2*axlim, 0, N)
X, Y = np.meshgrid(x, y)


norm = plt.Normalize(-5, 5)
cmap = LinearSegmentedColormap.from_list('', ['blue', 'black', 'red'])
fig, ax = plt.subplots()
plt.gca().set_axis_off()
plt.subplots_adjust(top = 1, bottom = 0, right = 1, left = 0, hspace = 0, wspace = 0)
plt.margins(0,0)

# calculate phases for a focal point
#w = 0
#h = 30
#ax.plot(N/2*(1 - w/axlim), N/2*(2-h/axlim), 'ro')
#x = np.linspace(min(sources), max(sources), len(sources))
#pos = np.sqrt((-w - x)**2 + h**2)/8.575

# calculate phases for beamforming
x = np.linspace(min(sources), max(sources), len(sources))
a = -0.04
pos = (a*x)/(np.sqrt(1+a*a))
a = a*10


def update(p):
    ax.cla()
    Z = 0
    
    for i in range(len(sources)):
        R = np.sqrt((X - sources[i])**2 + Y**2)
        Z += (300*np.sin(np.pi*f*(R/8.575 - p/10 - pos[i])))/(4*np.pi*R)

    ax.imshow(Z,
              cmap = cmap,
              norm = norm)

    for s in sources:
        ax.plot(N/2*(1 - s/axlim), N-1, 'ro')

    arrow = [1, (1/a)]
    normal = arrow/np.linalg.norm(arrow)
    ax.arrow(N/2, N-1, normal[0]*500, normal[1]*500, color='#ff0000', capstyle='projecting', linewidth=4, head_width=10)

    #ax.set_title(f'f = {40} KHz')
    ax.set_aspect('equal')
    ax.axis('off')

ani = FuncAnimation(fig = fig, func = update, frames=60, interval = 3/8.575)
ani.save('./simulation/animation_beam.gif', writer='imagemagick', fps=30)

#plt.show()