import sys

def init():
    global balance, record
    # Load data from records.txt if available
    try:
        with open('records.txt', 'r') as f:
            print('Found records.txt, importing...')
            balance = int(f.readline().strip())  # Read the first line (balance)
            try:
                record_lines = f.readlines()  # Read remaining lines (records)
                record = [tuple(line.strip().split()) for line in record_lines]  # Convert lines to tuples
                record = [(task, int(amount)) for task, amount in record]  # Convert amounts to integers
            except ValueError:
                print('Record can\'t be reached! Please inspect records.txt.')
                exit()

    except FileNotFoundError:
    # If the file doesn't exist, prompt the user for the initial balance
        try:
            print('records.txt not found, initializing...')
            balance = int(input('How much money do you have? '))
        except ValueError:
            sys.stderr.write("Invalid input for balance. Setting balance to 0.\n")
            balance = 0
        record = []  # Initialize an empty record list
    except ValueError:
        sys.stderr.write("Error reading records. Starting with a clean record.\n")
        balance = 0
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
    else:
        return False, count, indices
    

def add(change,record,balance):
    # split the diffrent entries
    change = str.split(change,',')
    # split the description and money in each entry
    for entry in change:
        try:
            task, num = entry.split()
            num = int(num)
            balance += num
            record.append((task, num))  # Append task and amount as a tuple
            print(f"Record \'{task} {num}\' added.")
        except ValueError:
            sys.stderr.write(f"Invalid format in entry: '{entry}'. Input should be in this format: \'breakfast -50\'\nFailed to add record.")
    return balance, record


def view(record, balance):
    print('Description                Amount')
    print('======================     ======')
    for rec in record:
        print(f"{rec[0]:<26} {rec[1]}")
    print('======================     ======')
    print(f"Now you have {balance} dollars.")


def delete(de, record, balance):
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
            print("Record not found, please try again.")
    return balance, record

def exit():
    # Saving the records to 'records.txt' before exiting
    with open('records.txt', 'w') as f:
        f.write(f"{balance}\n")  # Write the balance
        record_strings = [f"{task} {amount}\n" for task, amount in record]
        f.writelines(record_strings)  # Write the records
    print('Thank you. Data saved to records.txt.')

record = []
balance = 0
init()

while True:
    move = input('What do you want to do (add/view/delete/exit)? ')
    if move == 'add':
        change = str(input('Add some expense or income records with description and amount: ')) 
        balance, record = add(change, record, balance)
    elif move == 'view':
        view(record, balance)
    elif move == 'delete':
        de = input('Which record do you want to delete? ').split()
        balance, record = delete(de, record, balance)
    elif move == 'exit':
        exit()
        break
    else:
        print('Undefined input, please try again.')

