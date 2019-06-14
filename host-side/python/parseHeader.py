#! /usr/bin python

"""
    Author: Kristoffer Robin Stokke
            Institute of Informatics, University of Oslo

    This script parses one header file for other includes and function 
    definitions. Function implementations for the function definitions found is 
    generated and inserted in <outfile>.

    A recursive function is used to parse a single header. 
    
    ** On encounter with an #include directive, the recursive function is 
    called on that header.  
    ** The directories searched for that header depends on the enclosing 
    symbols (" or </>). This program skips any </> wrapped header includes to 
    avoid a large search tree - we are also only interested in Cuda libraries.  
    (This might need to be changed later.) 
    ** To avoid #include loops, which happens when two header files references 
    one another, a list (opened_files) is used to keep track of visited files.

"""

"""
    C keywords

    auto
    break
    case
    char
    const
    continue
    default
    do
    double
    else
    enum
    extern
    float
    for
    goto
    if
    int
    long
    register
    return
    short
    signed
    sizeof
    static
    struct
    switch
    typedef
    union
    unsigned
    void
    volatile
    while
"""

includepath =   ['/usr/local/cuda/include', '.']
outfile     =   'output.c'

output = open(outfile, 'w')

# Contains the opened headers, to avoid include loops
opened_files = []

# Contains whatever type definitions made plus the standard ones
declaration_specifiers = ['void', 'short', 'long', 'int', 'double', 'float', 'char', 'CUresult']
rest = ""
"""
def getNextStatement(sourcefile):

    if rest == "":
        while True:
            curLine = sourcefile.readline()
            if len(curLine) == "":
                return ""
            else if len(curLine) == 1:
                curLine = sourcefile.readline()
            else:
                break
    else:
        curLine = rest
    
    nextStmnt = ""

     #   Ignore leading whitespace characters

    for i in range(0, len(curLine)):
        if curLine[i] != ' ':
            curLine = curLine[i:]
            break;

    if curLine.startswith("/*"):
        while True:
            if "*/" in curLine:
                parts = curLine.partition("*/")
                nextStmnt += parts[0] + parts[1]
                break;
            else:
                nextStmnt += curLine
                curLine = sourcefile.readline
    
    return foundHeaders
"""
# Recursive function, searching for a header file (must have .h suffix)
def processHeader(filename, filepath, includetree):
    f = "" 
    try:
        temp = opened_files.index(filename)
        return None
    except ValueError:
        opened_files.append(filename)

    if(not includetree):
        print 'In file %s.' % (filename)
    else:
        print 'In file %s.' % (includetree + '/' + filename)

    if(not filepath):
        for path in includepath:
            try:
                f = open(path + '/' + filename, 'r')
            except IOError:
                continue
            #print 'Found %s in %s' % (filename, path)
            break
    else:
        # This should also search through includepath. "" headers are
        # first searched in current directory, then in standard include
        # path. 
        try:
            f = open(filepath + '/' + filename, 'r')
        except IOError:
            print "Couldn't find %s in %s!" % (filename, filepath)
            return None

    # We store all includes in a local variable, which are then processed
    # in the end.
    found_headers = []

    output.write("/* Declared from header %s (included from %s)*/\n" % (filename, includetree))

    # Processes lines in a header, looking for includes and function 
    # declarations.
    #
    # Reads the input file until EOF is reached. 
    while True:
        curLine = f.readline()

        if curLine == '':
            break
        """
            Ignore leading whitespace characters
        """
        #print "Removing whitespace of %s" % curLine
        for i in range(0, len(curLine)):
            if curLine[i] != ' ':
                curLine = curLine[i:]
                
                #print "Removed whitespace to: %s" % curLine
                break;

        """
            Just ignore the comments
        """
        if "/*" in curLine:
            while(True):
                if "*/" in curLine:
                    break;
                curLine = f.readline()

        """
            Check for macros
        """
        # Ignore standard header includes
        if curLine.startswith("#include <"):
            pass
        
        if curLine.startswith('#include "'):
            part = curLine.partition('"')
            part = part[2].partition('"')

            found_headers.append(part[0])

            processHeader(part[0], filepath, includetree + '/' + filename)
            output.write("/* Declared from header %s (included from %s)*/\n" % (filename, includetree))

        if curLine.startswith('#ifndef'):
            pass;

        if curLine.startswith('#if'):
            pass

        if curLine.startswith('#define'):
            pass

        if curLine.startswith('#undef'):
            pass

        if curLine.startswith('#else'):
            pass

        if curLine.startswith('#endif'):
            pass

        if curLine.startswith('#warning'):
            pass

        if curLine.startswith('#error'):
            pass

        if curLine.startswith('#line'):
            pass
        """
        if curLine.startswith('typedef '):
            wordsInLine = curLine.split()

            declSpec = wordsInLine[len(wordsInLine)-1]

            declSpec = declSpec[:len(declSpec) - 1]

            if declSpec.startswith('*'):
                declSpec = declSpec[1:]

            print "Adding %s to types." % declSpec
            declaration_specifiers.append(declSpec)
        """
        """
            Check for enclosing brackets
        """

        """
            Check for function signatures
        """

        if curLine.count('(', 0, len(curLine)) == 1 and curLine.count(')', 0, len(curLine)) == 1 and curLine.endswith(';\n', 0, len(curLine)):
    
            # Any function must have a return type. We search for it first
            found = False
            for ret_type in declaration_specifiers:
                if ret_type in curLine:
                    found = True
                    break
            if found == False:
                break

 #           print "Found function in line %s" % curLine
            toInsert = curLine[:(len(curLine) - 2)]
            toInsert += "{\n\n}"
            
            if toInsert.find("extern ") != -1:
                parts = toInsert.partition("extern ")
                toInsert = parts[0]
                toInsert += parts[2]

            output.write("\n%s\n" % toInsert)




#processHeader("cuda_runtime.h", '', '')
processHeader("cuda.h", '', '')
