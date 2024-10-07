balance = int(input('How much money do you have?')) 
record = []

while True:
    change = input('Add some expense or income records with description and amount (or type "quit" to exit): ')
    
    if change == 'quit':
        print('Thank you.')
        break

    change = change.split(',')

    for entry in change:
        desc, amount = entry.split()  # Split each entry into description and amount
        amount = int(amount)
        record.append((desc, amount))  # Append to the record list
        balance += amount  # Update the balance based on the amount
    
    print('Now you have', balance, 'dollars.')

# Print final records
print("Your records:")
for desc, amount in record:
    print(f"{desc}: {amount} dollars")