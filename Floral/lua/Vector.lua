function regulizeDeg(x)
  while (x>360)
  do
    x=x-360
  end
  while (x<0)
  do
    x=x+360
  end
  return x;
end

function rad2deg(x)
  return regulizeDeg(x/math.pi*180.0)
end
function deg2rad(x)
  return regulizeDeg(x)*math.pi/180.0
end

Vector={}
do
   local meta = {
        _metatable = "Private metatable",
        _DESCRIPTION = "Vectors in 2D"
    }

    meta.__index = meta

    function meta:__add( v )
        return Vector(self.x + v.x, self.y+ v.y)
    end
    
    function meta:__sub( v )
        return Vector(self.x - v.x, self.y - v.y)
    end
    function meta:__mul( v )
        return self.x * v.x + self.y * v.y
    end
    
    function meta:__tostring()
        return ("<%g, %g>"):format(self.x, self.y)
    end
    --rotate counter clockwise
    function meta:rotate(deg)
        local rad=deg2rad(deg)
        local sin=math.sin(rad)
        local cos=math.cos(rad)
        return Vector(self.x*cos-self.y*sin,self.y*cos+self.x*sin)
    end
      
    function meta:mag()
        return math.sqrt( self * self )
    end
    
  
    function meta:angle()
        if (self.x==0 and self.y>=0)then return 90.0 end
        if (self.x==0 and self.y<0) then return 270.0 end
        if (self.x>0 and self.y==0) then return 0.0 end
        if (self.x>0 and self.y==0) then return 180.0 end
        
        return rad2deg(math.atan2(self.y,self.x))
    end
    
    function meta:plain()
      return self.x, self.y
    end
    setmetatable( Vector, {
        __call = function( V, x ,y ) return setmetatable( {x = x, y = y}, meta ) end
    } )
end

Vector.__index=Vector

v=Vector(0,1)
print(v:rotate(90))
return Vector
