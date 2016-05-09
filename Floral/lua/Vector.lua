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
    function meta:scale(factor)
        return Vector(self.x*factor, self.y*factor)
    end
    function meta:norm()
        local mag=self:mag()
        return Vector(self.x/mag, self.y/mag)
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
        local x=self.x
        local y=self.y
      
        if (x==0 and y>=0)then return 90.0 end
        if (x==0 and y<0)then return 270.0 end
        if (x>0 and y==0)then return 0.0 end
        if (x<0 and y==0)then return 180.0 end
        
        if (y>0 and x>0)
        then
            return rad2deg(math.atan(y/x))
        end
        if (y>0 and x<0)
        then
            return regulizeDeg(rad2deg(math.atan(y/x))+180.0)
        end
        if (y<0 and x<0)
        then
            return regulizeDeg(rad2deg(math.atan(y/x))+180.0)
        end
          
        
        if (y<0 and x>0)
        then
            return regulizeDeg(rad2deg(math.atan(y/x))+360.0)
        end
        
    end
    function meta:angleLerp(v, clockwise, ratio,length)
        
        local myAngle=self:angle()
        
        local yourAngle=v:angle()
        
        local newAngle=0
        if (clockwise and myAngle<yourAngle)
        then 
          myAngle=myAngle+360
        end
        if (not clockwise and myAngle>yourAngle)
        then 
          yourAngle=yourAngle+360
        end
        newAngle=regulizeDeg(myAngle+(yourAngle-myAngle)*ratio)
        
        return Vector(1,0):rotate(newAngle):scale(length)
    end
    
    function meta:midAngleLerp(v, clockwise, length)
      return self:angleLerp(v, clockwise, 0.5, length)
    end
    
    
    function meta:plain()
      return self.x, self.y
    end
    setmetatable( Vector, {
        __call = function( V, x ,y ) return setmetatable( {x = x, y = y}, meta ) end
    } )
end

Vector.__index=Vector

return Vector
