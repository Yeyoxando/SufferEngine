function Start()
  print "Starting CUBE from LUA!"
  Rotate(0.0, 0.0, 0.0)
  SetGeometry("Cube")
  SetDrawMode("Triangles")
  Translate(30.0, 10.0, 5.0)
end

local rotation = 0
local speed = 0
function Update()
  --print "Updating CUBE from LUA!"
  rotation = rotation + 0.01
  speed = speed + 0.005
  Rotate(rotation, rotation, rotation);
  Translate(math.sin(os.clock()) * 20.0 + speed, math.cos(os.clock()) * 20.0 + speed, math.cos(os.clock() + speed) * 20.0 + speed)
end