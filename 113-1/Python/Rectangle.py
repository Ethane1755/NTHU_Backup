class Rectangle:
    def __init__(self, w, h):
        self.w = w
        self.h = h

    @property
    def area(self):
        return self.w * self.h
    
    def fit(self, other):
        s1 = (self.w ** 2 + self.h ** 2) ** 0.5
        s2 = (other.w ** 2 + other.h ** 2) ** 0.5
        return (s1 <= s2) 
    def fit1(self, other):
        s1 = (self.w ** 2 + self.h ** 2) ** 0.5
        s2 = (other.w ** 2 + other.h ** 2) ** 0.5
        return (s1 >= s2) 
    def __gt__(self, other):
        return (self.area > other.area) and self.fit(other)
    def __lt__(self, other):
        return (self.area < other.area) and self.fit1(other)
    def __eq__(self, other):
        return (self.area == other.area) and self.fit(other) and self.fit1(other)

T = int(input())
for t in range(T):
    s = input()
    print(eval(s))