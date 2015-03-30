Config = {hello="hellolua", woqu=123}
Config.name = "zhangsan"
Config["words"] = "test"
Config.age = 100
Config["num"] = 20

--print(Config.name)
--
--print(Config["age"])
--
--print(Config.num)
--
--print(Config.hello)

for key, var in pairs(Config) do
	print(key,var)
end