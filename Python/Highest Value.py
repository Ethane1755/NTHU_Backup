class Player:
    def __init__(self):
        self.value = 0
        self.num = 0
    def add(self, val):
        self.value += val ** self.num
        self.num += 1
    def getval(self):
        return self.value
    def getpoly(self):
        return self.num

n = int(input())
p1 = Player()
p2 = Player()

for i in range(n):
    player, value = input().split()
    player = int(player)
    value = int(value)
    if int(player) == 1:
        p1.add(value)
    else:
        p2.add(value)

if p1.getval() > p2.getval():
    winner = 1
elif p1.getval() < p2.getval():
    winner = 2
else:
    if p1.getpoly() > p2.getpoly():
        winner = 1
    elif p1.getpoly() < p2.getpoly():
        winner = 2
    else:
        winner = 'DRAW'

print(winner)