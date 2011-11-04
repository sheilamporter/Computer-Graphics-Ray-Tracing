import pygame
import math, os, sys
from mathutils import *

def ray_circle_intersect(anchor, direction, center, radius):
    anchorToCenter = (center - anchor)
    l = None
    angle = math.degrees(math.acos(anchorToCenter.normal() * direction.normal()))
    if angle > 90: return (False,l)
    vtRay = direction.normal()
    
    b = 2 * (anchorToCenter * vtRay)
    c = anchorToCenter * anchorToCenter - radius**2
    a = vtRay * vtRay
    
    divisor = 1.0 / (2.0*a)
    discriminate = b**2 - 4*a*c
    
    if (discriminate <= 0): return (False,l)
    
    b4ac = math.sqrt(discriminate)
    l1 = (b - b4ac) * divisor
    l2 = (b + b4ac) * divisor
    
    l = l1 if l1 < l2 else l2
    
    return (True, l)

class Ray(object):
    def __init__(self,origin,point,depth=1):
        self.origin = origin
        self.direction = (point - origin).normal()
        self.colPoint = self.origin + self.direction.scale(1000)
        self.depth = depth
        self.color = (255,255,255)
        
    def cast(self,scene,screen):
        hits = []
        for circle in scene:
            col, colDist = ray_circle_intersect(self.origin, self.direction, circle.center, circle.radius)
            if col and self.depth < 5:
                hits.append((col,colDist,circle))
                
        # print hits
        rays = []
        if len(hits) > 0:
            hits.sort(key=lambda x: x[1])
            col = hits[0][0]
            colDist = hits[0][1]
            circle = hits[0][2]
            self.colPoint = self.origin + self.direction.scale(colDist)
            # spawn new rays and cast at self.depth + 1
            normal = (self.colPoint - circle.center).normal()
            reflectVector = self.direction.reflect(normal)
            reflectRay = Ray(self.colPoint,self.colPoint + reflectVector, self.depth+1)
            if self.depth < 4:
                rays.append(reflectRay)
            rays.extend(reflectRay.cast(scene,screen))
            self.color = circle.color
            self.color = tuple(map(lambda x,y: (x+y/2.0), list(circle.color), list(reflectRay.color)))
            
        return rays
        
    def draw(self,screen):
        self.color = tuple(min(x,255) for x in list(self.color))
        pygame.draw.line(screen, self.color, (self.origin.x,self.origin.y), (self.colPoint.x,self.colPoint.y), 3)

class Circle(object):
    def __init__(self,center,radius,color):
        self.center = center
        self.radius = radius
        self.color = color
        
    def draw(self,screen):
        pygame.draw.circle(screen, self.color, (self.center.x,self.center.y), self.radius)
        
        
if __name__ == "__main__":
    pygame.init()

    screen = pygame.display.set_mode((600,400))
    clock = pygame.time.Clock()
    
    camera = Vector2(100.0,200.0)
    
    # ray1 = Ray(camera,Vector2(120.0,197.0))
    # ray2 = Ray(camera,Vector2(120.0,199.5))
    # ray3 = Ray(camera,Vector2(120.0,203.0))
    # rays = [ray1, ray2, ray3]
    rays = []
    planeHeight = 5.0
    for i in range(planeHeight*25):
        ray = Ray(camera,Vector2(120.0,(200.0-planeHeight/2.0)+((planeHeight*i)/100.0)))
        rays.append(ray)
    
    circle1 = Circle(Vector2(400.0,200.0),50,(255,0,0))
    circle2 = Circle(Vector2(300.0,150.0),30,(0,255,0))
    circle3 = Circle(Vector2(250.0,300.0),20,(0,0,255))
    circles = [circle1, circle2, circle3]
    
    while True:
        clock.tick(30)
        screen.fill((0,0,0))
        
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    sys.exit(1)
                    
        for circle in circles:
            circle.draw(screen)
            
        drawnRays = []
        for ray in rays:
            drawnRays.append(ray)
            drawnRays.extend(ray.cast(circles,screen))
        drawnRays.sort(key=lambda x: x.depth, reverse=True)
        for ray in drawnRays:
            ray.draw(screen)
        
        pygame.display.update()