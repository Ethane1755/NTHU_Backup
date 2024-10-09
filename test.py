def check_duplicate_distinct(items,a,count):
    for c in items:
        if c == a:
            count += 1
    if count != 1:
        return True
count = 0
print(check_duplicate_distinct([1,1,2,3,4],1,count))