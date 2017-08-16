from z3 import *
x = Int('x')
y = Int('y')

print solve(x>2, y<10, x+2*y==7)