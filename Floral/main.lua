#main

require "lua.config"
require "lua.Vector"

math.randomseed(os.time())

function getVec()
    return config.win_height
end

