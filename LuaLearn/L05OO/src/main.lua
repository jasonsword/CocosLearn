--ͨ���հ��ķ�ʽ���д���
function People(name)
	local self = {}
	
	--�Ƽ�����ʹ�ô��෽ʽ���д������ֱ��
	--�ڲ�����ʹ�ô��ַ�ʽ��ֻ�бհ��ķ�ʽ����ʹ������
	local function init()
		self.name = name
	end
	
	--����������ʹ�ô��ַ�ʽ����
	self.sayHi = function()
		print("Hi "..self.name)
	end
	
	init()
	return self
end

local p = People("zhangsan")
p:sayHi()

--ͨ���հ��ķ�ʽ���д���
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
