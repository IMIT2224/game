import random
import time
from sys import argv

def min_r_h(y, r):
    if(y == 0): return True
    global horizontal
    global HEIGHT
    if(y == 0 or y == 1 or y == HEIGHT-1 or y == HEIGHT-2): return True
    for i in horizontal:
        if (abs(i[0] - y) < r or abs(0-y)<r or abs(HEIGHT-y) < r): return True
    return False

def min_r_v(x, r):
    global vertical
    global WIDTH
    if(x == 0 or x == 1 or x == WIDTH-1 or x == WIDTH-2): return True
    for i in vertical:
        if (abs(i[0] - x) < r or abs(0-x)<r or abs(WIDTH-x) < r): return True
    return False


def check_ground(x, y):
    global horizontal
    global vertical

    for i in horizontal:
        if (i[0] == x and y >= i[1] and y <= i[2] and y != i[3]):
            return True

    for i in vertical:
        if (i[0] == y and x >= i[1] and x <= i[2] and x != i[3]):
            return True

    return False

def gen(x_begin, x_end, y_begin, y_end):
    global horizontal
    global vertical
    global stack
    global begin_time
    global MAX_REQ
    stack += 1
    if (stack == MAX_REQ): return 1
    point = [0, 0]
    IsHorizontal = random.randint(0,1)
    chet = 0
    if(IsHorizontal):
        while(min_r_h(point[1], 3)):
            chet += 1
            if(chet > 50): return 2
            point[0] = random.randint(x_begin, x_end)
            point[1] = random.randint(y_begin, y_end)
        horizontal.append([point[1], x_begin, x_end, point[0]])
        if((x_end - x_begin) * (point[1] - y_begin) > (x_end - x_begin) * (y_end - point[1])):
            gen(x_begin, x_end, y_begin, point[1])
        else:
            gen(x_begin, x_end, point[1], y_end)
    else:
        while(min_r_v(point[0], 3)):
            point[0] = random.randint(x_begin, x_end)
            point[1] = random.randint(y_begin, y_end)
        vertical.append([point[0], y_begin, y_end, point[1]])
        if((y_end - y_begin) * (point[0] - x_begin) > (y_end - y_begin) * (x_end - point[0])):
            gen(x_begin, point[0], y_begin, y_end)
        else:
            gen(point[0], x_end, y_begin, y_end)

def check_rand(n):
    temp_b = -1
    for i in n:
        temp_a = i
        if(temp_a == temp_b): return True
        temp_b = i
    return False

def check_rand_x(n):
    temp_b = -1
    for i in n:
        temp_a = i
        if(abs(temp_a - temp_b) < 4): return True
        temp_b = i
    return False

def gen_str_zero(n, m):
    temp_str = "                                                                              "
    temp_str = temp_str[:n] + '@' + temp_str[n+1:]
    temp_str = temp_str[:m] + '>' + temp_str[m+1:]
    temp_str = temp_str[:m+1] + '0' + temp_str[m+2:]
    for i in range(len(temp_str)):
        if(temp_str[i] == ' '):
            if(random.randint(0, 70) == 0):  temp_str = temp_str[:i] + '$' + temp_str[i+1:]
            elif(random.randint(0, 80) == 0):temp_str = temp_str[:i] + '%' + temp_str[i+1:]
            elif(random.randint(0, 50) == 0):temp_str = temp_str[:i] + '#' + temp_str[i+1:]
    return temp_str

def gen_str_person(m):
    temp_str = "                                                                              "
    temp_str = temp_str[:m] + '<' + temp_str[m+1:]
    temp_str = temp_str[:m+1] + '@' + temp_str[m+2:]
    for i in range(len(temp_str)):
        if(temp_str[i] == ' '):
            if(random.randint(0, 70) == 0):  temp_str = temp_str[:i] + '$' + temp_str[i+1:]
            elif(random.randint(0, 80) == 0):temp_str = temp_str[:i] + '%' + temp_str[i+1:]
            elif(random.randint(0, 50) == 0):temp_str = temp_str[:i] + '#' + temp_str[i+1:]
    return temp_str

def gen_str_next(m):
    temp_str = "                                                                              "
    temp_str = temp_str[:m] + '>' + temp_str[m+1:]
    temp_str = temp_str[:m+1] + '0' + temp_str[m+2:]
    for i in range(len(temp_str)):
        if(temp_str[i] == ' '):
            if(random.randint(0, 70) == 0):  temp_str = temp_str[:i] + '$' + temp_str[i+1:]
            elif(random.randint(0, 80) == 0):temp_str = temp_str[:i] + '%' + temp_str[i+1:]
            elif(random.randint(0, 50) == 0):temp_str = temp_str[:i] + '#' + temp_str[i+1:]
    return temp_str
        
script, first = argv
first = int(first)
LEVELS = first

flag_rand_y = True
while(flag_rand_y):
    rand_y = []
    for i in range(LEVELS):
        rand_y.append(random.randint(5,23))
    flag_rand_y = check_rand(rand_y)

flag_rand_x = True
while(flag_rand_x):
    rand_x = []
    for i in range(LEVELS+1):
        rand_x.append(random.randint(5,75))
    flag_rand_x = check_rand_x(rand_x)

for number_level in range(LEVELS):
    key_flag = True
    my_file = open(f"scene/scene_{number_level+1}r.txt", "w")
    begin_time = time.time()
    WIDTH = 80
    HEIGHT = 22
    MAX_REQ = 8
    stack = -1

    PLAYER_CHAR = '@'
    NONE_CHAR = ' '
    MONEY_CHAR = '$'
    GROUND_CHAR = '#'
    HEALTH_CHAR = '%'
    ENEMY_CHAR = 'E'
    KEY_CHAR = 'K'

    horizontal = []
    vertical = []

    gen(1, WIDTH-1, 1, HEIGHT-1)

    # print(horizontal)
    # print(vertical)
    list_str = [" ", " ", " "]
    flag3 = True
    i_data = ">0"

    for i in range(HEIGHT):
        str_t = ""
        flag = True
        flag2 = True
        if(number_level == 0):
            if(i == rand_y[0]-4):
                list_str.append("#"+gen_str_zero(rand_x[0], rand_x[1])+"#")
                continue
        else: # OK
            if(i == rand_y[number_level-1]-4):
                list_str.append("#"+gen_str_person(rand_x[number_level])+"#")
                continue
            if(i == rand_y[number_level]-4):
                list_str.append("#"+gen_str_next(rand_x[number_level+1])+"#")
                continue
          
                
        for j in range(WIDTH):
            if(i*j == 0 or i == HEIGHT-1 or j == WIDTH-1):
                str_t += GROUND_CHAR
            elif(check_ground(i, j)):
                if(random.randint(0,9)%5!=0):
                    str_t += GROUND_CHAR
                else:
                    str_t += NONE_CHAR
            else:
                if(key_flag and i > 10 and j > 10):
                    str_t += KEY_CHAR
                    key_flag = False
                else:
                    if(random.randint(0,75)==0 and flag2):
                        str_t += MONEY_CHAR
                        flag = False
                    elif(random.randint(0,100)==0 and flag2):
                        str_t += HEALTH_CHAR
                        flag = False
                    elif(random.randint(0,250) == 0 and flag):
                        str_t += ENEMY_CHAR
                        flag = False
                        flag2 = False
                    elif(random.randint(0,250) == 0 and key_flag):
                        str_t += KEY_CHAR
                        key_flag = False
                    
                    else: str_t += NONE_CHAR
        list_str.append(str_t)

    #for i in range(3):
    #a    my_file.write("\n")
    for i in list_str:
        my_file.write(i)
        my_file.write("\n")

    my_file.close()