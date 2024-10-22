import math

def prime(x, y):
    prime_list = []
    for i in range(x, y+1):
        if i == 0 or i == 1:
            continue
        else:
            for j in range(2, int(math.sqrt(i))+1):
                if i % j == 0:
                    break
            else:
                prime_list.append(i)
    return prime_list

inp = input()
a = int(inp.split()[0])
b = int(inp.split()[1])
if a == b:
    print('[%d]'%a)
else:
    lst = prime(a,b)
    lst = sorted(lst, reverse = True)
    print(lst)
