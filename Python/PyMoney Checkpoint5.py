balance = int(input('How much money do you have?')) 


while True:
    change = str(input('Add some expense or income records with description and amount:')) 
    #set breakpoint
    if change == 'quit':
        print('Thank you.')
        break
    #split the diffrent entries
    change = str.split(change,',')
    #split the description and money in each entry
    for entry in change:
        task, num = str.split(entry)
        num = int(num)
        balance += num
        print(task , num)


    print('Now you have', balance, 'dollars.')

