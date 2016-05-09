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
function containCircle(v, radius)
  if (contain(v) and 
    contain(v+Vector(0,1):scale(radius)) and
    contain(v+Vector(1,0):scale(radius)) and
    contain(v+Vector(-1,0):scale(radius)) and
    contain(v+Vector(0,-1):scale(radius)))
  then
   
      return true
  else
    
      return false
  end--if
end
  
gen.tsBranchInside=function(branch)
  local lastPoint=branch.root
  local lastOri=not branch.clockwise
  local lastRadius=0
  for i=0, branch.total-2,1
  do
    local startVec, endVec
    if (inCircle(lastPoint, lastRadius, branch[i]))
    then 
      --preserve the lastOri
      lasRadius=lastRadius-(branch[i]-lastPoint):mag()
      startVec=branch[i]-lastPoint
    else
      lastRadius=(branch[i]-lastPoint):mag()-lastRadius
      startVec=lastPoint-branch[i]
      lastOri=not lastOri
    end--if
    
    endVec=branch[i+1]-branch[i]
    if (i+1==3) then print("aSDFFDFDFSF") end
    for j=0,1,0.2
    do
      --lerp the point
      if (not contain(branch[i]+startVec:angleLerp(endVec, lastOri, j,lastRadius)))
      then
        return false
      end--if
      
    end--for j
  end--for i
  --checking for the last spiral
  if (inCircle(lastPoint, lastRadius, branch[branch.total-1]))
  then
    return containCircle(branch[branch.total-1],lastRadius-(branch[branch.total-1]-lastPoint):mag())
  else
    return containCircle(branch[branch.total-1],(branch[branch.total-1]-lastPoint):mag()-lastRadius)
  end
  
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
    if (not gen.tsBranchInside(branch))
    then
      vtable:removeLastBranch()
    end
    
  until(vtable.total>=config.max_branch)
  return vtable
end

return gen