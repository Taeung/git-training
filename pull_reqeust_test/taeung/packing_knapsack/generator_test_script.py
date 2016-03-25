#!/bin/python
import random

test_script = open("test.sh","w")

test_script.write("#!/bin/bash\n")
test_script.write("echo -e \"")

nr = random.randrange(1,1000)
w = random.randrange(1,10000)

test_script.write(str(nr)+" "+str(w)+"\\n\\\n")


for i in range(1,nr-1):
    j_p = random.randrange(1,w)
    j_w = random.randrange(1,w)
    test_script.write(str(j_p)+" "+str(j_w)+"\\n\\\n")

j_p = random.randrange(1,w)
j_w = random.randrange(1,w)
test_script.write(str(j_p)+" "+str(j_w)+"\\n\" | ./a.out")
