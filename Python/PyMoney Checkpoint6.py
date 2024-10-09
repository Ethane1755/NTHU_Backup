balance = int(input('How much money do you have?')) 
record = []

while True:
    move = input('What do you want to do(add/ delete/ view/ exit).')
    if move == 'add':
        change = str(input('Add some expense or income records with description and amount:')) 
        #split the diffrent entries
        change = str.split(change,',')
        #split the description and money in each entry
        for entry in change:
            task, num = str.split(entry)
            num = int(num)
            balance += num
            record.append((task,num))
            print (record)
            #print(task , num)
        print('Now you have', balance, 'dollars.')
    elif move == 'view':
        print('Description                Amount')
        print('======================     =======')
        print()
    elif move == 'exit':
        print('Thank you.')
        break
    else:
        print('Undefined input.')


