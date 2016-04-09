local candy = Candy("localhost")

local width = candy:get_width()
local height = candy:get_height()

local x = width / 2
local y = height / 2

local scale_factor = y / 3
local pos_0 = {x=x                        , y=y      }

local rings = { }

rings[1] = {}
for i=0,4 do
  rings[1][i+1] = {
    x=x+math.cos(math.pi+math.pi/2+math.pi*0/5+math.pi*2*i/5)*scale_factor,
    y=y+math.sin(math.pi+math.pi/2+math.pi*0/5+math.pi*2*i/5)*scale_factor
  }
end

scale_factor = scale_factor * 2
rings[2] = {}
for i=0,4 do
  rings[2][i+1] = {
    x=x+math.cos(math.pi+math.pi/2+math.pi*1/5+math.pi*2*i/5)*scale_factor,
    y=y+math.sin(math.pi+math.pi/2+math.pi*1/5+math.pi*2*i/5)*scale_factor
  }
end

scale_factor = scale_factor * 1.22
rings[3] = {}
for i=0,4 do
  rings[3][i+1] = {
    x=x+math.cos(math.pi+math.pi/2+math.pi*0/5+math.pi*2*i/5)*scale_factor,
    y=y+math.sin(math.pi+math.pi/2+math.pi*0/5+math.pi*2*i/5)*scale_factor
  }
end

candy:add_strip(rings[1][1],  pos_0,       70);
candy:add_strip(rings[1][1],  rings[1][2], 82);
candy:add_strip(rings[1][1],  rings[2][5], 84);
candy:add_strip(rings[1][1],  rings[2][1], 84);

candy:add_strip(rings[1][2],  pos_0,       70);
candy:add_strip(rings[1][2],  rings[1][3], 82);
candy:add_strip(rings[1][2],  rings[2][2], 84);
candy:add_strip(rings[1][2],  rings[2][1], 84);


candy:add_strip(rings[1][3],  pos_0,       70);
candy:add_strip(rings[1][3],  rings[1][4], 82);
candy:add_strip(rings[1][3],  rings[2][3], 84);
candy:add_strip(rings[1][3],  rings[2][2], 84);

candy:add_strip(rings[1][4],  pos_0,       70);
candy:add_strip(rings[1][4],  rings[1][5], 82);
candy:add_strip(rings[1][4],  rings[2][4], 84);
candy:add_strip(rings[1][4],  rings[2][3], 84);

candy:add_strip(rings[1][5],  pos_0,       70);
candy:add_strip(rings[1][5],  rings[1][1], 82);
candy:add_strip(rings[1][5],  rings[2][4], 84);
candy:add_strip(rings[1][5],  rings[2][5], 84);

-------------- V2 -----------------

candy:add_strip(rings[3][1],  rings[1][1], 82);
candy:add_strip(rings[3][1],  rings[2][5], 84);
candy:add_strip(rings[3][1],  rings[2][1], 84);

candy:add_strip(rings[3][2],  rings[1][2], 82);
candy:add_strip(rings[3][2],  rings[2][1], 84);
candy:add_strip(rings[3][2],  rings[2][2], 84);

candy:add_strip(rings[3][3],  rings[1][3], 82);
candy:add_strip(rings[3][3],  rings[2][2], 84);
candy:add_strip(rings[3][3],  rings[2][3], 84);

candy:add_strip(rings[3][4],  rings[1][4], 82);
candy:add_strip(rings[3][4],  rings[2][3], 84);
candy:add_strip(rings[3][4],  rings[2][4], 84);

candy:add_strip(rings[3][5],  rings[1][5], 82);
candy:add_strip(rings[3][5],  rings[2][4], 84);
candy:add_strip(rings[3][5],  rings[2][5], 84);
