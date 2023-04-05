# this code is based on the wave equation example from this article
# https://beltoforion.de/en/recreational_mathematics/2d-wave-equation.php

import pygame
import numpy as np
import time

hs = 0.66                    # spatial step width
ts = 0.000001               # time step width in s
dimx = 300                  # width of the simulation domain
dimy = 300                  # height of the simulation domain
cellsize = 2                # display size of a cell in pixel
    
speed_of_sound = 343000     # mm/s Wave velocity of sound in air
f = 40000                   # frequency
l = speed_of_sound/f        # wavelength
dist = 10                   # disctance between point sources
count = 10                  # number of point sources

def create_arrays():
    global velocity
    global tau
    global kappa
    global u
    
    # The three dimensional simulation grid 
    u = np.zeros((3, dimx, dimy))       

    # A field containing the velocity for each cell
    velocity = np.zeros((dimx, dimy))   

    # A field containing the factor for the Laplace Operator that  combines Velocity and Grid Constants for the Wave Equation
    tau  = np.zeros((dimx, dimy))       

    # A field containing the factor for the Laplace Operator that combines Velocity and Grid Constants for the Boundary Condition 
    kappa = np.zeros((dimx, dimy))      


def set_initial_conditions(u):
    global velocity
    global tau
    global kappa

    velocity[0:dimx,0:dimy] = speed_of_sound

    # compute tau and kappa from the velocity field
    tau = ( (velocity*ts) / hs )**2
    kappa = ts * velocity / hs


def update(u : any):
    u[2] = u[1]
    u[1] = u[0]
    
    # ok, (8th) https://www.ams.org/journals/mcom/1988-51-184/S0025-5718-1988-0935077-0/S0025-5718-1988-0935077-0.pdf; Page 702
    boundary_size = 4
    u[0, 4:dimx-4, 4:dimy-4]  = tau[4:dimx-4, 4:dimy-4]\
                                * ( -  1/560 * u[1, 4:dimx-4, 0:dimy-8]  # c,   r-4
                                    +  8/315 * u[1, 4:dimx-4, 1:dimy-7]  # c,   r-3
                                    -    1/5 * u[1, 4:dimx-4, 2:dimy-6]  # c,   r-2
                                    +    8/5 * u[1, 4:dimx-4, 3:dimy-5]  # c,   r-1

                                    - 1/560  * u[1, 0:dimx-8, 4:dimy-4]  # c - 4, r
                                    + 8/315  * u[1, 1:dimx-7, 4:dimy-4]  # c - 3, r
                                    -   1/5  * u[1, 2:dimx-6, 4:dimy-4]  # c - 2, r
                                    +   8/5  * u[1, 3:dimx-5, 4:dimy-4]  # c - 1, r
                                    - 410/72 * u[1, 4:dimx-4, 4:dimy-4]  # c    , r
                                    +   8/5  * u[1, 5:dimx-3, 4:dimy-4]  # c + 1, r
                                    -   1/5  * u[1, 6:dimx-2, 4:dimy-4]  # c + 2, r
                                    + 8/315  * u[1, 7:dimx-1, 4:dimy-4]  # c + 3, r
                                    - 1/560  * u[1, 8:dimx  , 4:dimy-4]  # c + 4, r

                                    +    8/5 * u[1, 4:dimx-4, 5:dimy-3]  # c  , r+1
                                    -    1/5 * u[1, 4:dimx-4, 6:dimy-2]  # c  , r+2
                                    +  8/315 * u[1, 4:dimx-4, 7:dimy-1]  # c  , r+3
                                    -  1/560 * u[1, 4:dimx-4, 8:dimy  ]  # c  , r+4
                                    ) \
                                + 2*u[1, 4:dimx-4, 4:dimy-4] \
                                -   u[2, 4:dimx-4, 4:dimy-4]  

    # Absorbing Boundary Conditions:
    mur = True
    if mur==True:
        update_boundary(u, boundary_size)


def update_boundary(u, sz) -> None:
    """Update the boundary cells. 
    
        Implement MUR boundary conditions. This represents an open boundary were waves can leave the
        simulation domain with little remaining reflection artifacts. Although this is of a low error 
        order it is good enough for this simulation.
    """
    c = dimx-1
    u[0, dimx-sz-1:c, 1:dimy-1] = u[1,  dimx-sz-2:c-1, 1:dimy-1] + (kappa[dimx-sz-1:c, 1:dimy-1]-1)/(kappa[ dimx-sz-1:c, 1:dimy-1]+1) * (u[0,  dimx-sz-2:c-1,1:dimy-1] - u[1, dimx-sz-1:c,1:dimy-1])
    
    c = 0
    u[0, c:sz, 1:dimy-1]        = u[1, c+1:sz+1, 1:dimy-1]       + (kappa[c:sz, 1:dimy-1]-1)/(kappa[c:sz, 1:dimy-1]+1)                * (u[0, c+1:sz+1,1:dimy-1]       - u[1,c:sz,1:dimy-1])

    r = dimy-1
    u[0, 1:dimx-1, dimy-1-sz:r] = u[1, 1:dimx-1, dimy-2-sz:r-1] + (kappa[1:dimx-1, dimy-1-sz:r]-1)/(kappa[1:dimx-1, dimy-1-sz:r]+1) * (u[0, 1:dimx-1, dimy-2-sz:r-1] - u[1, 1:dimx-1, dimy-1-sz:r])

    r = 0
    u[0, 1:dimx-1, r:sz] = u[1, 1:dimx-1, r+1:sz+1] + (kappa[1:dimx-1, r:sz]-1)/(kappa[1:dimx-1, r:sz]+1) * (u[0, 1:dimx-1, r+1:sz+1] - u[1, 1:dimx-1, r:sz])


def draw_waves(display, u, data, offset):
    global velocity
    global font

    #data[1:dimx, 1:dimy, 0] = np.clip(u[0, 1:dimx, 1:dimy]*2 + 128, 0, 255)
    #data[1:dimx, 1:dimy, 1] = np.clip(u[1, 1:dimx, 1:dimy]*2 + 128, 0, 255)
    #data[1:dimx, 1:dimy, 2] = np.clip(u[2, 1:dimx, 1:dimy]*2 + 128, 0, 255)

    data[1:dimx, 1:dimy, 0] = 255 - np.clip((u[0, 1:dimx, 1:dimy]>0) * 10 * u[0, 1:dimx, 1:dimy]+u[1, 1:dimx, 1:dimy]+u[2, 1:dimx, 1:dimy], 0, 255)
    data[1:dimx, 1:dimy, 1] = 255 - np.clip(np.abs(u[0, 1:dimx, 1:dimy]) * 10, 0, 255)
    data[1:dimx, 1:dimy, 2] = 255 - np.clip((u[0, 1:dimx, 1:dimy]<=0) * -10 * u[0, 1:dimx, 1:dimy] + u[1, 1:dimx, 1:dimy] + u[2, 1:dimx, 1:dimy], 0, 255) 

    surf = pygame.surfarray.make_surface(data)
    display.blit(pygame.transform.scale(surf, (dimx * cellsize, dimy * cellsize)), offset)    


def draw_text(display, fps, tick):
    global font

    text_surface = font.render('2D Wave Equation - Explicit Euler (Radiating Boundary Conditions)', True, (0, 0, 40))
    display.blit(text_surface, (5,5))

    text_surface = font.render(f'FPS: {fps:.1f}; t={tick:.6f} s; area={dimx*hs}x{dimy*hs} mm', True, (0, 0, 40))
    display.blit(text_surface, (5, dimy*cellsize - 20))

def calculate_phase_for_focus(source, point):
    return np.sqrt((point[0] + source[0])**2 + (point[1] + source[1])**2) * ((np.pi*2)/l)


def main():
    global font

    pygame.init()
    pygame.font.init()
                   
    font = pygame.font.SysFont('Consolas', 15)    
    display = pygame.display.set_mode((dimx*cellsize, dimy*cellsize))
    pygame.display.set_caption("Solving the 2d Wave Equation")

    create_arrays()
    set_initial_conditions(u)

    image1data = np.zeros((dimx, dimy, 3), dtype = np.uint8 )

    tick = 0
    last_tick = 0
    fps = 0
    start_time = time.time()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

        tick = tick + ts/2

        current_time = time.time() 
        if current_time - start_time > 0.5:
            fps = (tick*1000000-last_tick) / (current_time - start_time) 
            start_time = time.time()
            last_tick = tick*1000000

        x, y = pygame.mouse.get_pos()
        w = (dimx/(2) - (x)/cellsize)*hs
        h = (dimy*2 - ((y*2)/cellsize))*hs

        x = np.linspace(-(count - 1)*dist*0.5, (count - 1)*dist*0.5, count)

        for idx, i in enumerate(x):
            phase = calculate_phase_for_focus((x[idx], 0), (w,h))
            u[0:2, int(dimx/(2)+i/hs), int(dimy-10)] = np.sin(tick*2*np.pi*f + phase)*40

        update(u)
        draw_waves(display, u,  image1data, (0,0))
        draw_text(display, fps, tick)

        #surf1 = pygame.Surface((5,5))
        #display.blit(surf1, (int(dimx) - w*cellsize, int(dimy) - h))

        pygame.display.update()

if __name__ == "__main__":
    main()