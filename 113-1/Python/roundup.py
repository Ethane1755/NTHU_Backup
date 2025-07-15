inp = input().split()
a = float(inp[0])
b = float(inp[1])
c = int(inp[2])

ans = round(a*b,c)
print(a, "*", b, "equals to", ans)