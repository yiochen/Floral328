#main

require "lua.config"
require "lua.Vector"
require "lua.gen"


math.randomseed(os.time())

function construct()
  return gen.basic()
end
v=construct()

function getTotalBranch()
  return v.total
end

function getBranchSize(i)
  return v[i].total
end

function getVec(i,j)
  return v[i][j].x, v[i][j].y
end

print(v)




