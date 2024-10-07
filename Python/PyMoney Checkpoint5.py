balance = int(input('How much money do you have?')) 
record = []
i = 0
j = 1


while True:
    change = str(input('Add some expense or income records with description and amount:'))
    if change == 'quit':
        print('Thank you.')
        break
    change = str.split(change,',')
    for entry in change:
        task, num = str.split(entry)
        num = int(num)
        balance += num
        print(task , num)


    print('Now you have', balance, 'dollars.')

