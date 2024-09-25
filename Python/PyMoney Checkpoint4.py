balance = int(input('How much money do you have?')) 

while True:
    change = str(input('Add an expense or income record with description and amount:'))
    if change == 'q':
        print('Thank you.')
        break
    money = int(str.split(change)[1])
    balance += money
    print('Now you have', balance, 'dollars.')

