function Start()
  print "Starting CUBE from LUA!"
  Rotate(0.0, 0.0, 0.0)
  SetGeometry("Sphere")
  SetDrawMode("Triangles")
  Translate(0.0, 0.0, 5.0)
end

local rotation = 0
local speed = 0
function Update()
  --print "Updating CUBE from LUA!"
  rotation = rotation + 0.01
  if rotation>=(2 * 3.141592) then rotation = 0 end
  Rotate(rotation, 0.0, rotation);
  --Translate(math.sin(os.clock()) * 20.0 + speed, 
  --          math.cos(os.clock()) * 20.0 + speed, 
  --          math.cos(os.clock() + speed) * 20.0 + speed)
end