require "config"
require "Vector"
print(config.win_height)

v=Vector(1, 1)
x=Vector(2,3)
print(v)
print(x.y)
print(v+x)
print(x-v)
print(x:mag())
print("test angle")
print(Vector(0,1):angle())
print(Vector(1,1):angle())
print(Vector(-1,-1):angle())

print("the result end")

math.randomseed(os.time())
print(math.random(1.0,10.0))