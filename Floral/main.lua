#main

require "lua.config"
require "lua.Vector"
require "lua.gen"


math.randomseed(os.time())

function construct()
  return gen.basic()
end
print("start constructing")
math.random()
vt=construct()

function getTotalBranch()
  return vt.total
end

function getBranchSize(i)
  return vt[i].total
end

function getVec(i,j)
  return vt[i][j].x, vt[i][j].y
end

print(vt)




