width: int = 10
length: int = 10

list1: list[list[int]] = [[15 for y in range(0,length)] for x in range(0,width)] 

list1[0][0] = 14
list1[-1][-1] = 13

# 5º elemento da 3 lista
list1[2][4] = 0

# antepenultimo elemento da antepenultima lista
list1[-3][-3] = 0

for i in list1:
    print(i)
    
# Explorar DFS BFS

"""
N, E, S, W

N = 1, 0, 0, 0 = 8
E = 0, 1, 0, 0 = 4
S = 0, 0, 1, 0 = 2
W = 0, 0, 0, 1 = 1

"""