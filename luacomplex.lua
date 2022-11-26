local path = "./luacomplex.so"
local func = "l_loadcomplex"
local complex = package.loadlib(path,func)()

local csum = complex.csum
local csub = complex.csub

c = {
   real = 1.0,
   imag = 2.3}
d = csum(c,c)
e = csub({real = 1.22, imag = 4.3},
   {real = 0.4, imag = 2.22})

print(e.real,e.imag)
print(d.real,d.imag)

