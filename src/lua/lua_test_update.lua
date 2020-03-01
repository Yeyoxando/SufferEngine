function Start()
  print "Starting SPHERE from LUA!"
  SetGeometry("Cube")
  SetDrawMode("Triangles")

end

local rotation_ = 0
local speed_ = 10
function Rotation()
  rotation_ = rotation_ + 0.005
  Rotate(0.0, rotation_, rotation_)
end

local x = 0
local speed = 0
function Update()
  Rotation()
  Translate(math.sin(os.clock()) * 20.0, 
            0.0, 
            0.0)
end