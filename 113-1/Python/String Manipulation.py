class csstr(str):
    def __lshift__(self, x):
        l = len(self)
        b = list(self)  # Convert string to list to allow mutation
        shift = x % l  # Correct shift amount using modulo
        for i in range(l):
            b[i] = self[(i + shift) % l]  # Wrap around correctly using modulo
        return ''.join(b)

    def __rshift__(self, x):
        l = len(self)
        b = list(self)  # Convert string to list to allow mutation
        shift = x % l  # Correct shift amount using modulo
        for i in range(l):
            b[i] = self[(i - shift) % l]  # Wrap around correctly using modulo
        return ''.join(b)

T = int(input())
for t in range(T):
    print(eval(input()))