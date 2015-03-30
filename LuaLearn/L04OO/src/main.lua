function clone(tab)
	local ins = {}
	for key, var in pairs(tab) do
		ins[key] = var
	end
	return ins
end

function copy(dist, tab)
	for key, var in pairs(tab) do
		dist[key]=var
	end
end

People = {}

--function People.sayHi(self)
--	print("People say Hi")
--end

--People.sayHi = function ()
--  print("People say Hi")
--end

--self������һ������Ķ���
People.sayHi = function (self)
--..�����ӷ� 
	print("People say Hi:"..self.name)
end

People.new = function (name)
	local self = clone(People)
	self.name = name
	return self
end

local p = People.new("zhangsan")
p.sayHi(p)
--���ַ�ʽ�����ԣ����Ƽ�����ķ�ʽ�������ڴ�self�ĺ���
--p:sayHi()

for key, var in pairs(p) do
	print(key, var)
end

Man = {}
--Man.sayHello = function ()
--  print("Man sayHello")
--end

Man.sayHello = function (self)
  print("Man sayHello:"..self.name)
end

--�ﵽ��д������Ŀ��
Man.sayHi = function (self)
  print("Man sayHi:"..self.name)
end

Man.new = function (name)
	local self = People.new(name)
	copy(self, Man)
	return self
end

local m = Man.new("LiSi")
m.sayHello(m)
m:sayHello()
m:sayHi()
