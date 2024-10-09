balance = int(input('How much money do you have?')) 
record = []

def check_duplicate(items, a):
    count = 0
    indices = []  # To store the indices of the matching records
    for i, c in enumerate(items):
        if c == a:
            count += 1
            indices.append(i)  # Store the index of the duplicate
    if count > 1:  
        return True, count, indices

while True:
    move = input('What do you want to do(add/ delete/ view/ exit).')
    if move == 'add':
        change = str(input('Add some expense or income records with description and amount:')) 
        # split the diffrent entries
        change = str.split(change,',')
        # split the description and money in each entry
        for entry in change:
            task, num = str.split(entry)
            num = int(num)
            balance += num
            record.append((task,num))
    elif move == 'view':
        print('Description                Amount')
        print('======================     ======')
        for rec in record:
            print(f"{rec[0]:<26} {rec[1]}")
        print('======================     ======')
        print(f"Now you have {balance} dollars.")
    elif move == 'delete':
        de = input('Which record do you want to delete?').split()
        task_to_delete = de[0]
        amount_to_delete = int(de[1])
        duplicate_check, count, indices = check_duplicate(record, (task_to_delete, amount_to_delete))
        
        if duplicate_check:
            print(f"There are {count} instances of this record!")
            for i, idx in enumerate(indices, 1):
                print(f"{i}. on line {idx+1}, {record[idx][0]} {record[idx][1]}")
            ask = int(input('Which one do you want to remove (enter the number)? '))
            
            if 1 <= ask <= count:
                index_to_remove = indices[ask - 1]
                removed_record = record.pop(index_to_remove)
                balance -= removed_record[1]
                print(f"Record '{removed_record[0]} {removed_record[1]}' deleted.")
            else:
                print("Invalid selection.")
        else:
            try:
                record.remove((task_to_delete, amount_to_delete))
                balance -= amount_to_delete
                print(f"Record '{task_to_delete} {amount_to_delete}' deleted.")
            except ValueError:
                print("Record not found.")
    elif move == 'exit':
        print('Thank you.')
        break
    else:
        print('Undefined input, please try again.')

