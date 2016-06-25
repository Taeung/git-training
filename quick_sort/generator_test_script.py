#!/bin/python
import random
import os
import platform

if platform.system() != 'Linux':
    print "Can't generate test script on OS other than Linux"
    exit()

def get_gcc_version():
    return os.popen('gcc --version').readline().rstrip()

def get_gcc_options():
    dirname = os.path.split(os.getcwd())[1]
    filename = dirname + ".c"
    return "gcc -ggdb " + filename + " -ansi -fno-asm -O2 -Wall -lm --static"

def get_os_info():
    return platform.platform()

def test_script__new():
    test_script = open("test.sh","w")
    test_script.write("#!/bin/bash\n")
    test_script.write("#\n# TEST ENVIRONMENT\n")
    test_script.write("# gcc version: " + get_gcc_version() + "\n")
    test_script.write("# gcc options: " + get_gcc_options() + "\n")
    test_script.write("# os: " + get_os_info() + "\n\n")
    return test_script

test_script = test_script__new()
test_script.write("echo -e \"")

nr = random.randrange(1, 50001)
order = random.randrange(0, 2)

test_script.write(str(nr)+"\\n\\\n")
test_script.write(str(order)+"\\n\\\n")

billion = 10 ** 9
for i in range(1,nr):
    num = random.randrange(0, billion)
    test_script.write(str(num)+"\\n\\\n")

num = random.randrange(1, billion)
test_script.write(str(num)+"\\n\" | ./$1")
