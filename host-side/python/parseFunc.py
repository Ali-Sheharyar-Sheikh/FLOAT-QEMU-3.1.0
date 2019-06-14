#! /usr/bin python

"""
    Author: Kristoffer Robin Stokke
            Institute of Informatics, University of Oslo

"""

spaceString     =   ' '

includepath     =   ['.', '/usr/local/cuda/inlude']
fakeFunc_file   =   open('autogen/fake_functions.cpp', 'w')
forwFunc_file   =   open('autogen/forwarding_functions.cpp', 'w')
structure_file  =   open('autogen/structs.h', 'w')
callID_file     =   open('autogen/callID.h', 'w')

# Contains symbols that have been used. E.g., the free() function 
# will generate a compiler error if "free" has always been used
# as a function parameter. Inserting such symbols here will redefine
# those function parameter names.
used_symbols = ['free']

# Contains the opened headers, to avoid include loops
opened_files = []

# function symbols listed will not be virtualized
funcWhitelist = ''

# Contains return types of the functions we are looking for
declaration_specifiers = ['cudaError_t', 'CUresult']

# Recursive function, searching for a header file (must have .h suffix)
def processHeader(filename, filepath, includetree):
    f = "" 
    print "In file %s with filepath %s, includetree %s" % (filename, filepath, includetree)
    try:
        temp = opened_files.index(filename)
        return None
    except ValueError:
        opened_files.append(filename)

    found   =   False
    if(not filepath):
        for path in includepath:
            try:
                f       =   open(path + '/' + filename, 'r')
                found   =   True
            except IOError:
                continue
            #print 'Found %s in %s' % (filename, path)

        if not found:
            return None
    else:
        # This should also search through includepath. "" headers are
        # first searched in current directory, then in standard include
        # path. 
        try:
            f = open(filepath + '/' + filename, 'r')
        except IOError:
            print "Couldn't find %s in %s!" % (filename, filepath)
            return None

    structure_file.write("/* Data structures from header %s (included from %s)*/\n" % (filename, includetree))
    fakeFunc_file.write("/* Fake functions from header %s (included from %s)*/\n" % (filename, includetree))
    forwFunc_file.write("/* Forwarding functions from header %s (included from %s)*/\n" % (filename, includetree))
    # Processes lines in a header, looking for includes and function 
    # declarations.
    #
    # Reads the input file until EOF is reached. 
    while True:
        curLine = f.readline()

        if curLine == '':
            break
    
        # Remove leading and trailing whitespace
        curLine     =   curLine.strip()
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

            print "include %s" % part[0]
            processHeader(part[0], filepath, includetree + '/' + filename)
            structure_file.write("/* Data structures from header %s (included from %s)*/\n" % (filename, includetree))
            fakeFunc_file.write("/* Fake functions from header %s (included from %s)*/\n" % (filename, includetree))
            forwFunc_file.write("/* Forwarding functions from header %s (included from %s)*/\n" % (filename, includetree))

        if curLine.startswith('#ifndef'):
            pass

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

        if curLine.count('(', 0, len(curLine)) == 1 and curLine.count(')', 0, len(curLine)) == 1:
    
            # Filter out unwanted stuff...
            found = False
            for ret_type in declaration_specifiers:
                if ret_type in curLine:
                    found = True
                    break
            if found == False:
                continue
            
            if curLine.endswith(';'):
                curLine     =   curLine[:len(curLine) - 1]

            if curLine.endswith('{'):
                curLine     =   curLine[:len(curLine) - 1]

            # Process function in curLine
            parts       =   curLine.partition('(')
            funcName    =   parts[0]
            funcName    =   funcName.split()
            funcName    =   funcName[len(funcName) - 1]
            funcName    =   funcName.strip()

            funcParams  =   parts[2].partition(')')
            funcParams  =   funcParams[0]
            funcParams  =   funcParams.split(',')

            # Replace used symbol names in function parameters
            counter = 0
            for parameter in funcParams:
                for usedSym in used_symbols:
                    if usedSym in parameter:
                        funcParams[counter] = funcParams[counter].replace(usedSym, usedSym + '_')
                        curLine = curLine.replace(usedSym, usedSym + '_')

                counter += 1
            # Construct function signature data structure
            #
            # The gerenic routine for doing this is to regard any pointer type as output,
            # while non-pointer parameters are regarded as input. Special cases exists, e.g.
            # for strings and certain driver data types, like 'struct cudaArray'.
            structName  =   funcName + "Struct"
            structure_file.write("struct %s{\nstruct callHeader callheader;\n\n" % structName)

            for parameter in funcParams:
                parameter   =   parameter.strip()
                paramSymb   =   parameter.split()
                paramSymb   =   paramSymb[len(paramSymb) - 1]
                paramSymb   =   paramSymb.replace("*", '')

                # Special cases #
                # ************* #
                if parameter == "void":
                    continue

                if "const" in parameter:
                    parameter   =   parameter.replace("const", "")

                if "void" in parameter:
                    passParam   =   parameter.replace("**", '*')
                    structure_file.write("%s;\n" % (passParam))
                    continue

                if "char" in parameter:
                    if "**" in parameter:
                        structure_file.write("// Character double-pointer!\n")
                        continue
                    if "*" in parameter:
                        structure_file.write("char %s[CFWD_BUFSZ];\n" % paramSymb.replace("*", ""))
                        continue

                if "struct cudaArray" in parameter:
                    structure_file.write("struct cudaArray *%s;\n" % paramSymb.replace("*", ''))
                    continue

                # ************* #
                
                # A double-pointer 'int **pp' passed through a function is done when the function needs
                # to alter the "pointer that is being pointed to by 'pp', or in other words *pp = "new 
                # pointer value to int". It might also signify that the actual data that is being pointed 
                # to by the double pointer (**pp) has been allocated or changed.
                #
                # A single-pointer 'int *p' passed through a function signifies a need to change the data
                # pointed to by the pointer.

                #if "**" in parameter:
                #    passParam   =   parameter.replace('*', '')
                if "*" in parameter and not "void" in parameter:
                    passParam   =   parameter.replace('*', '')
                else:
                    passParam   =   parameter

                structure_file.write("%s;\n" % passParam)

            structure_file.write("};\n\n")

            # Generate fake function call
            fakeFunc_file.write(("%s" % curLine) + '{\n\n')

            """
                If the function name starts with "cuda", we should be able to assume 
                that it is from the runtime API. If it starts with "cu", it should be
                the driver API.
            """
            if funcName.startswith("cuda"):
                fakeFunc_file.write("cudaError_t respError = cudaErrorApiFailureBase;\n\n")

            elif funcName.startswith("cu"):
                fakeFunc_file.write("CUresult respError = CUDA_ERROR_UNKNOWN;\n\n")

            else:
                print "Unknown function (%s)!" % funcName
                continue
            
            # Might need to sort out callType
            callID = "fa" + funcName
            # Store a symbol identifier
            callID_file.write("%s,\n" % callID)
            #callType    = 

            fakeFunc_file.write("struct %s *msg_p = (struct %s*) malloc(sizeof(struct %s));\n\n" % (structName, structName, structName))
            fakeFunc_file.write("msg_p->callheader.head.cmdType = normCall;\n")
            fakeFunc_file.write("msg_p->callheader.callID = %s;\n\n" % callID)
            #fake_functions.write("msg_p->callheader.callType = %s\n" % callType)

            # [IN] parameters (not marked with '*' in signature)
            
            for parameter in funcParams:
                parameter   =   parameter.strip()
                paramSymb   =   parameter.split()
                paramSymb   =   paramSymb[len(paramSymb) - 1]
                paramSymb   =   paramSymb.replace("*", '')

                # Special cases #
                # ************* #
                if parameter == "void":
                    continue

                if "const" in parameter:
                    parameter   =   parameter.replace("const", "")

                if "void" in parameter:
                    if "**" in parameter:
                        fakeFunc_file.write("msg_p->%s = (void*) *%s;\n" % (paramSymb, paramSymb))
                        continue
                    elif '*' in parameter:
                        fakeFunc_file.write("msg_p->%s = (void*) %s;\n" % (paramSymb, paramSymb))
                        continue

                if "char" in parameter:
                    if "*" in parameter:
                        fakeFunc_file.write("char* src = (char*) %s;\nchar* dst = msg_p->%s;\nwhile(*src != '\\0'){\n*dst = *src;\ndst++;\nsrc++;\n}\n*dst = '\\0';\n" % (paramSymb, paramSymb))
                        continue
                                
                if "struct cudaArray" in parameter:
                    if "**" in parameter:       # output parameter
                        #fakeFunc_file.write("struct cudaArray double-pointer!\n")
                        continue
                    elif "*" in parameter:
                        passParam   =   parameter.replace("*", "")
                        fakeFunc_file.write("msg_p->%s = (struct cudaArray*) %s;\n" % (paramSymb, paramSymb))
                        continue
                # ************* #
                if not '*' in parameter:
                    fakeFunc_file.write("msg_p->%s = %s;\n" % (paramSymb, paramSymb))
                elif "**" in parameter:
                    pass
                elif '*' in parameter:
                    fakeFunc_file.write("msg_p->%s = *%s;\n" % (paramSymb, paramSymb))

            fakeFunc_file.write("\nif(sendMessage((void*) msg_p, sizeof(struct %s)) == FACUDA_ERROR)\nreturn respError;\n\n" %structName)
            fakeFunc_file.write("free((void*) msg_p);\n\n")
            fakeFunc_file.write("if(recvMessage((void**) &msg_p) == FACUDA_ERROR)\nreturn respError;\n\n")

            # [OUT] parameters (marked with '*' in signature)
             
            for parameter in funcParams:
                parameter   =   parameter.strip()
                paramSymb   =   parameter.split()
                typeSymb    =   paramSymb[:len(paramSymb) - 1]
                typeSymb    =   spaceString.join(typeSymb)
                typeSymb    =   typeSymb.replace("const", '')
                typeSymb    =   typeSymb.strip()
                paramSymb   =   paramSymb[len(paramSymb) - 1]
                paramSymb   =   paramSymb.replace("*", '')

                # Special cases #
                # ************* #
                if parameter == "void":
                    continue

                #if "const" in parameter and not '*' in parameter:
                if "const" in parameter:
                    continue

                if "void" in parameter:
                    if "**" in parameter:
                        fakeFunc_file.write("*%s = msg_p->%s;\n" % (paramSymb, paramSymb))
                        continue
                    elif '*' in parameter:
                        fakeFunc_file.write("%s = msg_p->%s;\n" % (paramSymb, paramSymb))
                        continue

                if "char" in parameter:
                    if "*" in parameter:
                        fakeFunc_file.write("dst = %s;\nsrc = msg_p->%s;\nwhile(*src != '\\0'){\n*dst = *src;\ndst++;\nsrc++;\n}\n*dst = '\\0';\n" % (paramSymb, paramSymb))
                        continue
                                
                if "struct cudaArray" in parameter:
                    if "**" in parameter:       # output parameter
                        fakeFunc_file.write("*%s = msg_p->%s;\n" % (paramSymb, paramSymb))
                        continue
                    elif "*" in parameter:
                        continue
                # ************* #
                if "**" in parameter:
                    fakeFunc_file.write("*%s = (%s*) malloc(sizeof(%s));\n" % (paramSymb, typeSymb, typeSymb))
                    fakeFunc_file.write("**%s = msg_p->%s;\n" % (paramSymb, paramSymb))
                elif '*' in parameter:
                    paramSymb   =   parameter.split()
                    paramSymb   =   paramSymb[len(paramSymb) - 1]
                    passParam   =   paramSymb.replace('*', '')
                    fakeFunc_file.write("*%s = msg_p->%s;\n\n" % (passParam, passParam))

            if funcName.startswith('cuda'):
                fakeFunc_file.write("respError = msg_p->callheader.respError;\n\n")

            elif funcName.startswith('cu'):
                fakeFunc_file.write("respError = msg_p->callheader.drvRespErr;\n\n")

            fakeFunc_file.write("free((void*) msg_p);\n\nreturn respError;\n")

            fakeFunc_file.write("}\n\n")

            # Now, need to sort out forwarding mechanism
            forwFunc_file.write("if(recCallHdr->callID == %s){\n\n" % callID)
            
            varName = structName + "Var"
            forwFunc_file.write("struct %s *%s = (struct %s*) msg;\n\n" % (structName, varName, structName))

            callLine = ''
            if funcName.startswith('cuda'):
                callLine = ("%s->callheader.respError = %s(" % (varName, funcName))
                #forwFunc_file.write("%s->callheader.respError = %s(" % (varName, funcName))

            elif funcName.startswith('cu'):
                callLine = ("%s->callheader.drvRespErr = %s(" % (varName, funcName))
                #forwFunc_file.write("%s->callheader.drvRespErr = %s(" % (varName, funcName))

            for parameter in funcParams:
                
                paramSymb   =   parameter.split()
                typeSymb    =   paramSymb[:len(paramSymb) - 1]
                typeSymb    =   spaceString.join(typeSymb)
                typeSymb    =   typeSymb.strip()
                typeSymb    =   typeSymb.replace('*', '')
                if "**" in parameter:
                    typeSymb += "**"
                elif '*' in parameter:
                    typeSymb += '*'
                paramSymb   =   paramSymb[len(paramSymb) - 1]
                paramSymb   =   paramSymb.replace("*", '')

                # Special cases #
                # ************* #
                if parameter == "void":
                    continue

                if "const" in parameter:
                    callLine += "(%s)" % (typeSymb)

                if "void" in parameter:
                    if "**" in parameter:
                        callLine += ("&%s->%s, " % (varName, paramSymb))
                        continue
                    if "*" in parameter:
                        callLine += ("%s->%s, " % (varName, paramSymb))
                        continue

                if "char" in parameter:
                    if "**" in parameter:
                        continue
                    if "*" in parameter:
                        callLine += ("%s->%s, " % (varName, paramSymb))
                        continue
                                
                if "struct cudaArray" in parameter:
                    if "**" in parameter:       # output parameter
                        callLine += ("&%s->%s, " % (varName, paramSymb))
                        continue
                    elif "*" in parameter:
                        callLine += ("%s->%s, " % (varName, paramSymb))
                        continue
                # ************* #

                if not '*' in parameter:
                    callLine += ("%s->%s, " % (varName, paramSymb))
                elif "**" in parameter:
                    forwFunc_file.write("%s *%s_p = &%s->%s;\n" % (typeSymb.replace('*', ''), paramSymb, varName, paramSymb))
                    callLine += ("&%s_p, " % (paramSymb))
                elif '*' in parameter:
                    callLine += ("&%s->%s, " % (varName, paramSymb))

            if callLine.endswith(", "):
                callLine = callLine[:len(callLine) - 2]

            forwFunc_file.write("%s);\n\n" % callLine)

            forwFunc_file.write("*respMsgSz = sizeof(struct %s);\n" % structName)
            forwFunc_file.write("*respMsg = malloc(*respMsgSz);\n")
            forwFunc_file.write("**(struct %s**) respMsg = *%s;\n" % (structName, varName))

            forwFunc_file.write("}\n\n")
            

callID_file.write("enum callID{\n")
processHeader("inputfile", '', '')
callID_file.write("};\n")

structure_file.close()
