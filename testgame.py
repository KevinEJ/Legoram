import pdb
import random
import time
import sys

if len(sys.argv) == 2:
    print "Single player "
    mode = "single"
elif len(sys.argv) == 3:
    print "Dual players"
    mode = "Dual"
else:
    print "Input error"
    print "python testgame.py <Players1's program> [Player2's program] "

#print 'Number of arguments:', len(sys.argv), 'arguments.'
#print 'Argument List:', str(sys.argv)

#            house , wall , connon , ifFinish
MyCastle    = [ 0 , 0 , 0 , False , "User"]
EnemyCastle = [ 0 , 0 , 0 , False , "Com1"]

My_stragedy = open( sys.argv[1] , "r")
Enemy_stragedy = 0 
if mode == "Dual":
    Enemy_stragedy = open( sys.argv[2] , "r")
count = 0
count_if = 0
#My_finish = False
#Enemy_finish = False

#pdb.set_trace()
    
    #E = Enemy_stragedy.readline()
    #E_comment = E.split(" ")

def myParse( Comment , my , enemy ):
    #global My_stragedy
    global count 
    global count_if 
    #M = My_stragedy.readline()
    if my[3] == True:
        return
    M = Comment.readline()
    if len(M)==0:
        #pdb.set_trace()
        my[3] = True
        return
    M = M[:-1]
    M_comment = M.split(" ")
    while M_comment[0] == "":
        M_comment.remove("")
    print "[" , count , "]" , my[4] , " -> " , M_comment 
    if M_comment[0] == "build":
        if M_comment[1] == "house":
            #MyCastle[0] += 1
            my[0] += 1
        elif M_comment[1] == "wall":
            #MyCastle[1] += 1
            my[1] += my[0]
        elif M_comment[1] == "cannon":
            #MyCastle[2] += 1
            my[2] += my[0]
        else:
            print "comment "  , count , " input error : " , M_comment[1] 
    elif M_comment[0] == "e_if":
        Answer = getcondition( M_comment  , my , enemy)
        if Answer == True: 
            return #myParse()
        else:
            while True:
                #M = My_stragedy.readline()
                M = Comment.readline()
                M = M[:-1]
                if M.split(" ")[0] == "e_else" and count_if == 0:
                    count_if = 0
                    break
                elif M.split(" ")[0] == "e_else" and count_if != 0:
                    count_if -= 1
                elif M.split(" ")[0] == "e_if":
                    count_if += 1
                #else:
                    #print "if else count error"
            #myParse()
            return
    elif M_comment[0] == "m_if":
        Answer = getcondition( M_comment , my,enemy)
        if Answer == True: 
            #myParse()
            myParse(Comment , my , enemy)
        else:
            while True:
                #M = My_stragedy.readline()
                M = Comment.readline()
                M = M[:-1]
                if M.split(" ")[0] == "m_else" and count_if == 0:
                    count_if = 0
                    break
                elif M.split(" ")[0] == "m_else" and count_if != 0:
                    count_if -= 1
                elif M.split(" ")[0] == "m_if":
                    count_if += 1
                #else:
                    #print "if else count error"
            #myParse()
            myParse(Comment , my , enemy)
    elif M_comment[0] == "e_else":
        while True:
            #M = My_stragedy.readline()
            M = Comment.readline()
            M = M[:-1]
            if M.split(" ")[0] == "end":
                break
        #myParse()
        myParse(Comment , my , enemy)
    elif M_comment[0] == "m_else":
        while True:
            #M = My_stragedy.readline()
            M = Comment.readline()
            M = M[:-1]
            if M.split(" ")[0] == "end":
                break
        myParse(Comment , my , enemy)
    elif M_comment[0] == "fire":
        #EnemyCastle[1] -= MyCastle[2]
        enemy[1] -= my[2]
    elif M_comment[0] == "end":
        #myParse()
        myParse(Comment , my , enemy)
    else:
        print "comment "  , count , " input error : " , M_comment[0] 


def getcondition(M_comment , My , Enemy):
    global EnemyCastle 
    global MyCastle 
    left ,right = True , True
    if M_comment[1] == "e_house":
        left = Enemy[0]
    elif M_comment[1] == "e_wall":
        left = Enemy[1]
    elif M_comment[1] == "e_cannon":
        left = Enemy[2]
    elif M_comment[1] == "m_house":
        left = My[0]
    elif M_comment[1] == "m_wall":
        left = My[1]
    elif M_comment[1] == "m_cannon":
        left = My[2]
    else:
        print "comment "  , count , " input error" 
    if M_comment[3] == "e_house":
        right = Enemy[0]
    elif M_comment[3] == "e_wall":
        right = Enemy[1]
    elif M_comment[3] == "e_cannon":
        right = Enemy[2]
    elif M_comment[3] == "m_house":
        right = My[0]
    elif M_comment[3] == "m_wall":
        right = My[1]
    elif M_comment[3] == "m_cannon":
        right = My[2]
    else:
        print "comment "  , count , " input error" 
    if M_comment[2] == ">":
        Condi = (left > right)
        #pdb.set_trace()
        return Condi
    elif M_comment[2] == "=":
        Condi = (left == right)
        #pdb.set_trace()
        return Condi
    else:
        print "comment "  , count , " input error"


while MyCastle[3] == False :#or EnemyCastle[3] == False  :
    print "=============  " , count , "round  =========================="
    myParse(My_stragedy , MyCastle , EnemyCastle)
    if mode == "Dual":
        myParse(Enemy_stragedy , EnemyCastle , MyCastle)
    elif mode == "single":
        move = random.randint(0,3)
        if move == 0 :
            EnemyCastle[0] += 1
        elif move == 1 :
            EnemyCastle[1] += EnemyCastle[0]
        elif move == 2 :
            EnemyCastle[2] += EnemyCastle[0]
        elif move == 3 :
            MyCastle[1] -= EnemyCastle[2] 
    else:
        print "mode error"
    count += 1          
    print MyCastle
    print EnemyCastle
    print " " 
