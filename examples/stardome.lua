local candy = Candy("localhost")

local width = 800
local height = 480

local x = width / 2
local y = height / 2

local scale_factor = y / 7.8
local pos_0 = {x=x                        , y=y      }

local pos_1 = {x=x + scale_factor *  3.917, y=y + scale_factor *  1.272}
local pos_2 = {x=x + scale_factor *  0    , y=y + scale_factor *  4.118}
local pos_3 = {x=x + scale_factor * -3.917, y=y + scale_factor *  1.272}
local pos_4 = {x=x + scale_factor * -2.421, y=y + scale_factor * -3.332}
local pos_5 = {x=x + scale_factor *  2.421, y=y + scale_factor * -3.332}

local pos_6 = {x=x + scale_factor *  4.423, y=y + scale_factor *  6.088}
local pos_7 = {x=x + scale_factor * -4.423, y=y + scale_factor *  6.088}
local pos_8 = {x=x + scale_factor * -7.157, y=y + scale_factor * -2.325}
local pos_9 = {x=x + scale_factor *  0    , y=y + scale_factor * -7.526}
local pos_A = {x=x + scale_factor *  7.157, y=y + scale_factor * -2.325}

candy:add_strip(pos_1, pos_0, 70);
candy:add_strip(pos_1, pos_2, 82);
candy:add_strip(pos_1, pos_A, 84);
candy:add_strip(pos_1, pos_6, 84);

candy:add_strip(pos_2, pos_0, 70);
candy:add_strip(pos_2, pos_3, 82);
candy:add_strip(pos_2, pos_7, 84);
candy:add_strip(pos_2, pos_6, 84);


candy:add_strip(pos_3, pos_0, 70);
candy:add_strip(pos_3, pos_4, 82);
candy:add_strip(pos_3, pos_8, 84);
candy:add_strip(pos_3, pos_7, 84);

candy:add_strip(pos_4, pos_0, 70);
candy:add_strip(pos_4, pos_5, 82);
candy:add_strip(pos_4, pos_9, 84);
candy:add_strip(pos_4, pos_8, 84);

candy:add_strip(pos_5, pos_0, 70);
candy:add_strip(pos_5, pos_1, 82);
candy:add_strip(pos_5, pos_9, 84);
candy:add_strip(pos_5, pos_A, 84);
