from mathutils import *
from raycasting import *

if __name__ == "__main__":
    pygame.init()

    screen = pygame.display.set_mode((600,400))
    clock = pygame.time.Clock()
    
    camera = Vector2(100.0,200.0)
    
    rays = []
    planeHeight = 5.0
    for i in range(planeHeight*25):
        ray = Ray(camera,Vector2(120.0,(200.0-planeHeight/2.0)+((planeHeight*i)/100.0)))
        rays.append(ray)
    
    circle1 = Circle(Vector2(400.0,200.0),50,(255,0,0))
    circle2 = Circle(Vector2(300.0,150.0),30,(0,255,0))
    circle3 = Circle(Vector2(250.0,300.0),20,(0,0,255))
    circles = [circle1, circle2, circle3]
    
    light1 = Light(Vector2(100.0,100.0),(255,255,255))
    lights = [light1]
    
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
            
        for light in lights:
            light.draw(screen)
            
        drawnRays = []
        for ray in rays:
            ray.cast_for_shadows(circles,lights,screen)
            drawnRays.append(ray)
            # drawnRays.extend(ray.cast(circles,screen))
        drawnRays.sort(key=lambda x: x.depth, reverse=True)
        for ray in drawnRays:
            ray.draw(screen)
        
        pygame.display.update()

