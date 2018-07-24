--rayCasting Engine
--Coded By R. Yonaba
--Uses raycasting algorithm , so credits to him.


lang="en"

--set messages
text=@{}
text["fr"]="Plus de Temps !"
text["en"]="Time is Over !"

--choose automatically the map
--file=io.open("temp/lvl.txt","r")
--lvl=file:read("*n")
--file:close()
--if lvl < 1 then lvl=1 
--elseif lvl>4 then lvl=4 end
lvl = 1

--   -= Begin Trigo =-
PITR = 3.141596 / 180
function math_angle(iangle)
  iangle = int(iangle);
  iangle = iangle % 360; 
  if (iangle < 0) then iangle = iangle+360 end;
  --if ( iangle < 0 or iangle > 359 ) then print( "ANGLE ERR : "..tostring(iangle) ) end
  return iangle;
end 

function math_cos(iangle) return cos(iangle*PITR) end
function math_sin(iangle) return sin(iangle*PITR) end
--   -= End Trigo =-

--loads map from file
--if isDektop() then
--  --dofile("maps/map"..lvl..".map")
--  dofile(CWD_PATH.."raycast/map"..lvl.."rc.lua")
--else
  dofile("map"..lvl.."rc.lua")
--end

--map_width  = 11
--map_height = table.getn(map)


-- Screen  size
--screenx  = 480
--screeny  = 272
--screenx  = screen.WIDTH
--screeny  = screen.HEIGHT
screenx  = 320
screeny  = 240

--set field of View
fov     = 60 
larg    = 5
zoom    = 135
ray_rez = 0.06
   
--others sets
fps   = math.ceil(screenx / larg)
aps   = fov / fps
fovbt = (fov / 2)

-- moa tries ----------------------
fps = fov
aps   = fov / fps
larg = screenx / fps
-- keep those (beware w/ ray_rez)

-- generates player variables
moving_speed   = 0.3
rotating_speed = 22
playerX = mapInitX
playerY = mapInitY
player_ang = mapInitAng
target=255
    
--the next phase is create a custom function which returns 1,else player's current position
function locate(x, y)
 x = math.floor(x)
 y = math.floor(y)
 if (x < 1 or y < 1) or (x > map_width or y > map_height) then return 1 end
 return map[y][x]
end
    
--Now raycasting  can be done
function raycasting(x, y, angle)
 dist = 0
 angle = math_angle( angle ); 
 dx = ray_rez*math_cos(angle);
 dy = ray_rez*math_sin(angle);
  
 repeat
	x = x + dx
	y = y + dy
	dist = dist + ray_rez
	collision = locate(x, y) 
	if (collision ~= 0) then break end
 until (false)
 return dist, collision
end

--minutor
--clock=Timer.new()
--clock:start()

in_game=true
message=50
reduce=100
main=true

while main do
  --currentTime = clock:time()

  --Enables Pad & Joystick
  --key = Controls.read()
  --ax=key:analogX()
  --ay=key:analogY()


  --temporarily position
  ox = playerX
  oy = playerY

  --draws the background:ground & sky
  screen:clear(Color.new(0,250,0))
  screen:fillRect(0,0,screenx,screeny/2,Color.new(50,50,255))

  if in_game then
	--Enables Player Moves
	--if key:up() or ay<-80 then 
	--  playerX = playerX + math.cos(player_ang * pibt) * moving_speed
	--  playerY = playerY + math.sin(player_ang * pibt) * moving_speed
	--elseif key:down() or ay>80  then
	--  playerX = playerX - math.cos(player_ang * pibt) * moving_speed
	--  playerY = playerY - math.sin(player_ang * pibt) * moving_speed
	--end
	--if key:right() or ax>80 then
	--  player_ang = (player_ang + rotating_speed) % 360
	--elseif key:left() or ax<-80 then
	--  player_ang = (player_ang + 360 - rotating_speed) % 360
	--end
  end

  --sets collisions when player hits a wall (O)
  if (locate(playerX, playerY) ~= 0) then
    playerX = ox
    playerY = oy
  end

  --raycast stuffs 
  sx = 0
  angle = player_ang - fovbt
  ray_len = 0
  collision = 0
  h = 0
  wall = 0
  
  -- Draws the slices
  --for s = 1, fps do
  for s = 1, fps,2 do  --- MOA Modif to reduce slice nb
    ray_len, collision = raycasting(playerX, playerY, angle)
    
    ray_len = ray_len * math_cos( math_angle( (player_ang - angle) ) )
    
    h = math.floor(zoom / ray_len)
    wall = math.floor((screeny - h) / 2)
    if (wall < 0) then	h = h + wall  wall = 0  end
    if (wall + h > screeny) then h = screeny - wall end

    --screen:fillRect(sx, wall, larg, h, Color.new(100,100,100))		
    --sx = sx + larg
    --angle = angle + aps
    
    screen:fillRect(sx, wall, larg*2, h, Color.new(100,100,100))		
    sx = sx + larg*2
    angle = angle + aps*2
  end
  --print("nb of slices = "..fps)

  if math.floor(playerX) == 5 or math.floor(playerX) == 6 then
    if math.floor(playerY)>= map_height then
      main=false
      lvl=lvl+1
      -- file=io.open("temp/lvl.txt","w")
      -- file:write(lvl)
      -- file:close()
      -- dofile("congrats.lua")

      screen:print(20,100,"You Win !",Color.new(255,0,0))
      in_game=false 
    end
  end

	
  screen:print(410,10,"Map  "..lvl.."/4",Color.new(255,0,0))

  --if lvl*1000-(currentTime)/reduce >= 0 then screen:print(300,25,"Time Remaining :"..math.ceil(lvl*1000-(currentTime)/reduce),Color.new(0,255,0))
  --else screen:print(330,25,"Time Remaining :"..0,Color.new(0,255,0))
  --end

  --screen:blit(0,10,background)
  screen:fillRect(math.floor(playerX)*4,10+math.floor(playerY)*4*(11/map_height),2,2,Color.new(255,255,0))
  screen:fillRect(20,10+(44)-4,5,5,Color.new(0,target,0))
  --screen.waitVblankStart()
  --screen.flip()
  
  -- TMP --
  --break;
  player_ang = (player_ang + rotating_speed) % 360
  if (player_ang > 180) then break end
  
end
