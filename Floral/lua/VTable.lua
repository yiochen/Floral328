#vtable, use to save a branch information
require "lua.Vector"
VTable={total=0}
do
   local meta = {
        _metatable = "Private metatable",
        _DESCRIPTION = "table use to store vectors"
    }

    meta.__index = meta
    meta.__newindex=meta
    function newBranch()
      local branch={total=0}
      branch.root=Vector(0,0)
      branch.clockwise=false
      return branch
    end
    
    function meta:addBranch()
      t=newBranch()
      self[self.total]=t
      self.total=self.total+1
      return t
    end
    
    function meta:getCurrentBranch()
      if (self.total<=0)
      then
        addBranch()
      end
      return self[self.total-1]
    end
    
    function meta:addVec(v)
      local b=self:getCurrentBranch()
      if (b.total>=config.max_vert_per_branch)
      then 
        b=self:addBranch()
      end
      b[b.total]=v
      b.total=b.total+1  
    end
    
    function meta:removeLastVec()
      local b=self:getCurrentBranch()
      if (b.total>0)
      then
        b.total=b.total-1;
      end
    end
    
    function meta:__tostring()
      result=""
      result=result..self.total.." branches\n"
      for i=0,self.total-1,1
      do
        result=result..self[i].total..": "
        for j=0,self[i].total-1,1
        do
          result=result.." <"..self[i][j].x..","..self[i][j].y..">"
          
        end
        result=result.."\n"
      end
      return result
    end
    setmetatable( VTable, {
        __call = function(V) return setmetatable( {total=0}, meta ) end
    } )
end
VTable.__index=VTable
return VTable