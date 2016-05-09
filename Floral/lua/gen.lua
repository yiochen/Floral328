# generate control points
require "lua.config"
require "lua.Vector"
require "lua.VTable"
gen={}

math.randomseed(os.time())
gen.randomPoint=function()
  return Vector(math.random(0,config.win_width),math.random(0, config.win_height))
end
gen.tsRootTest=function(branch)
  if (branch.total>1)then return true end
end

function contain(v)
  if (v.x>=0 and v.x<=config.win_width and v.y>=0 and v.y<=config.win_height)
  then 
    return true
  else 
    return false
  end
end
function inCircle(center, radius, v2)
  if ((v2-center):mag()<=radius)
  then
    return true
  else
    return false
  end
end
function getNextRadius(lastCenter, lastRadius, center)
  if (inCircle(lastCenter, lastRadius, center)) then
      return lastRadius-(lastCenter-center):mag()
    else
      return (lastCenter-center):mag()-lastRadius
    end
end

--check if the branch root will not go out of frame
gen.tsBoundaryBranch=function(branch)
  if (branch.total>1 or branch.total==0)
  then
    --more than one vertex in this branch alreay
    --or zero vertex
    return true
  else
    local factor=1
    if (branch.clockwise)
    then
      local factor=-1
    end--clockwise
  
    if (contain((branch.root-branch[0]):rotate(factor*10)+branch[0]))
    then
      return true
    else
      return false
    end--contain
  end--total>1
  return true
end

--the ratio of two consecutive circle's radii cannot be too different
gen.tsRelativeRadius=function(branch)
  if (branch.total<2)
  then 
    --not enough circles
    return true
  else
    local lastCenter=branch[0]
    local lastRadius=(branch.root-branch[0]):mag()
    for i=1,branch.total-1,1
    do
      local newRadius=getNextRadius(lastCenter, lastRadius, branch[i])
      local ratio=newRadius/lastRadius
      if (ratio<0.5 or ratio>2) 
      then 
        
        return false
      end
      lastRadius=newRadius
      lastCenter=branch[i]
    end
    return true
  end
  return false--it wont get here
end
gen.getAngle=function(branch,i)
  if (branch.total<i+2)
  then 
    print("cannot calculate angle ",i,"for a branch with",branch.total,"control points")
    return 0
  else
    
  end
end

gen.tsBranchInside=function(branch)
  
end

  

gen.basic=function()
  local vtable=VTable()
  repeat
    local branch=vtable:addBranch()
    repeat
      vtable:addVec(gen.randomPoint())
      if (not gen.tsBoundaryBranch(branch) or 
        not gen.tsRelativeRadius(branch)) 
      then 
        vtable:removeLastVec() 
      end
    until(branch.total>=config.max_vert_per_branch)
      
  until(vtable.total>=config.max_branch)
  return vtable
end

return gen