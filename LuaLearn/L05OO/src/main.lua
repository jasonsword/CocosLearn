--通过闭包的方式进行处理
function People(name)
	local self = {}
	
	--推荐属性使用此类方式进行处理，简介直观
	--内部函数使用此种方式，只有闭包的方式才能使用这种
	local function init()
		self.name = name
	end
	
	--公开的属性使用此种方式定义
	self.sayHi = function()
		print("Hi "..self.name)
	end
	
	init()
	return self
end

local p = People("zhangsan")
p:sayHi()

--通过闭包的方式进行处理
function Man(name)
	local self = People(name)
	
	local function init()
    self.age = 18
	end
	
	self.sayHello = function ()
		print("Hello "..self.name.." age is "..self.age)
	end
	
	init()
	return self
end

local m = Man("LiSi")
m:sayHi()
m:sayHello()
