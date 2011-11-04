# ############################################################################
# mathutils.py - Python version of the Vector2, ... classes
#
# Author: Kevin Todisco
# ############################################################################

import math

def dist(x,y):
    # print x, y
    return math.sqrt((x.x-y.x)**2 + (x.y-y.y)**2)

def distance(x1,y1,x2,y2):
    return math.sqrt((x1-x2)**2 + (y1-y2)**2)
    
def approximately(x,y):
    return math.fabs(x-y) < 0.0001
    
def compute_barycentric(point,tri):
    alpha = float((tri[1].y - tri[2].y)*(point.x - tri[2].x) + (tri[2].x - tri[1].x)*(point.y - tri[2].y)) /\
            float((tri[1].y - tri[2].y)*(tri[0].x - tri[2].x) + (tri[2].x - tri[1].x)*(tri[0].y - tri[2].y))
    beta = float((tri[2].y - tri[0].y)*(point.x - tri[2].x) + (tri[0].x - tri[2].x)*(point.y - tri[2].y)) /\
           float((tri[1].y - tri[2].y)*(tri[0].x - tri[2].x) + (tri[2].x - tri[1].x)*(tri[0].y - tri[2].y))
    gamma = 1.0 - alpha - beta
    return (alpha,beta,gamma)
    
class Vector2(object):
    def __init__(self,x=0.0,y=0.0,w=0.0):
        self.x = x;
        self.y = y;
        self.w = w;
        
    def __add__(self,v):
        assert isinstance(v,Vector2)
        return Vector2(self.x+v.x, self.y+v.y, self.w)
        
    def __sub__(self,v):
        assert isinstance(v,Vector2)
        return Vector2(self.x-v.x, self.y-v.y, self.w)
        
    def __mul__(self,v):
        assert isinstance(v,Vector2)
        return (self.x*v.x) + (self.y*v.y)
        
    def __str__(self):
        return "Vector2 <%.3f %.3f>"%(self.x,self.y)
        
    def cross(self,other):
        assert isinstance(other,Vector2)
        return (self.x*other.y) - (self.y*other.x)
        
    def reflect(self,other):
        assert isinstance(other,Vector2)
        # v = Vector2(self.x,self.y)
        # v = v.project_onto(other).scale(2) - v
        c1 = (Vector2(self.x,self.y) * other)
        v = Vector2(self.x,self.y) - (other.scale(c1).scale(2))
        return v
        
    def mag(self):
        return math.sqrt(self.x**2 + self.y**2)
        
    def smag(self):
        sign = 1
        if self.x < 0: sign = -1
        return self.mag() * sign
        
    def normalize(self):
        mag = self.mag()
        self.x = self.x / mag
        self.y = self.y / mag
        
    def normal(self):
        mag = self.mag()
        if mag == 0:
            return Vector2(0.0,0.0)
        return Vector2(self.x/mag, self.y/mag)
        
    def perpendicular(self):
        return Vector2(-self.y,self.x)
        
    def scale(self,s):
        if isinstance(s,Vector2):
            return Vector2(self.x*s.x, self.y*s.y)
        else:
            return Vector2(self.x*s, self.y*s)
        
    def project_onto(self,other):
        assert isinstance(other,Vector2)
        denom = other * other
        if denom == 0:
            return Vector2(0.0,0.0)
        return other.scale((self * other) / (other * other))
        
class Matrix2D(list):
    def __init__(self):
        super(Matrix2D,self).__init__()
        self.append([1.0,0.0,0.0])
        self.append([0.0,1.0,0.0])
        self.append([0.0,0.0,1.0])
        
    def translate_x(self,x):
        self[0][2] += x;
        
    def translate_y(self,y):
        self[1][2] += y;
        
    def rotate(self,theta):
        theta = math.radians(theta)
        s = math.sin(theta)
        c = math.cos(theta)
        
        rotation = Matrix2D()
        rotation[0][0] = c
        rotation[0][1] = -s
        rotation[1][0] = s
        rotation[1][1] = c
        
        rotation = self * rotation
        for row in range(len(self)):
            for item in range(len(self[row])):
                self[row][item] = rotation[row][item]
                
    def reset(self):
        for row in range(len(self)):
            self[row] = [0.0,0.0,0.0]
            self[row][row] = 1.0
            
    def __str__(self):
        return "\n".join([' '.join(["%.3f"%col for col in row]) for row in self])
        
    def __mul__(self,other):
        assert isinstance(other,Vector2) or isinstance(other,Matrix2D)
        if isinstance(other,Vector2):
            result = Vector2()
            result.x = (self[0][0] * other.x) + (self[0][1] * other.y) + (self[0][2] * other.w)
            result.y = (self[1][0] * other.x) + (self[1][1] * other.y) + (self[1][2] * other.w)
            return result
        else:
            result = Matrix2D()
            result[0][0] = (self[0][0] * other[0][0]) + (self[0][1] * other[1][0]) + (self[0][2] * other[2][0])
            result[0][1] = (self[0][0] * other[0][1]) + (self[0][1] * other[1][1]) + (self[0][2] * other[2][1])
            result[0][2] = (self[0][0] * other[0][2]) + (self[0][1] * other[1][2]) + (self[0][2] * other[2][2])
            
            result[1][0] = (self[1][0] * other[0][0]) + (self[1][1] * other[1][0]) + (self[1][2] * other[2][0])
            result[1][1] = (self[1][0] * other[0][1]) + (self[1][1] * other[1][1]) + (self[1][2] * other[2][1])
            result[1][2] = (self[1][0] * other[0][2]) + (self[1][1] * other[1][2]) + (self[1][2] * other[2][2])
            return result