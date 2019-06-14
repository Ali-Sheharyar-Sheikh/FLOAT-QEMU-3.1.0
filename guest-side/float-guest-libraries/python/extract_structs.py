
fp  = open("structs.h", "r")
out = open("structsize.c", "w+")

while True:
    curLine = fp.readline()

    if curLine == '':
        break
    
    if curLine.startswith("struct"):

        out.write('fprintf(stdout, "sizeof(%s)=%s\\n", %s);' % (curLine.strip('{\n'), "%d",  "sizeof(%s)" % (curLine.strip("{\n"))))
        out.write("\n\n")
