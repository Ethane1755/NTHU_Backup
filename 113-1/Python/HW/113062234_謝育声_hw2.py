import sys

#initialize function
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
        try:
            sys.stderr.write("Error reading records, initializing...\n")
            balance = int(input('How much money do you have? '))
        except ValueError:
            sys.stderr.write("Invalid input for balance. Setting balance to 0.\n")
            balance = 0
        record = []  # Initialize an empty record list

# add function 
def add(change,record,balance):
    # split the diffrent entries
    change = str.split(change,',')
    # split the description and money in each entry
    for entry in change:
        try:
            cat, task, num = entry.split()
            num = int(num)
            balance += num
            record.append((cat, task, num))  # Append task and amount as a tuple
            print(f"Record \'{task} {num}\' added.")
        except ValueError:
            sys.stderr.write(f"Invalid format in entry: '{entry}'. Input should be in this format: \'breakfast -50\'\nFailed to add record.")
    return balance, record
    
#view function
def view(record, balance):
    i = 0
    print('\nDescription                Amount')
    print('======================     ======')
    for rec in record:
        print(f"{i+1}. {rec[0]:<23} {rec[1]}") #rec[0] appends blanks to fill 23 spaces
        i+=1
    print('======================     ======')
    print(f"Now you have {balance} dollars.\n")

#delete function
def delete(de, record, balance):
    """
    Deletes a record based on user input.
    """
    try:
        category_to_delete = de[0]
        description_to_delete = de[1]
        amount_to_delete = int(de[2])

        # Find all matching records
        matching_indices = [
            idx for idx, rec in enumerate(record)
            if rec == (category_to_delete, description_to_delete, amount_to_delete)
        ]

        if not matching_indices:
            print(f"No record found for '{category_to_delete} {description_to_delete} {amount_to_delete}'.")
            return balance, record

        if len(matching_indices) > 1:
            print(f"There are {len(matching_indices)} instances of this record!")
            for i, idx in enumerate(matching_indices, 1):
                print(f"{i}. {record[idx][0]} {record[idx][1]} {record[idx][2]}")
            ask = int(input('Which one do you want to remove (enter the number)? '))

            if 1 <= ask <= len(matching_indices):
                index_to_remove = matching_indices[ask - 1]
                removed_record = record.pop(index_to_remove)
                balance -= removed_record[2]
                print(f"Record '{removed_record[0]} {removed_record[1]} {removed_record[2]}' deleted.")
            else:
                print("Invalid index selection.")
        else:
            index_to_remove = matching_indices[0]
            removed_record = record.pop(index_to_remove)
            balance -= removed_record[2]
            print(f"Record '{removed_record[0]} {removed_record[1]} {removed_record[2]}' deleted.")

    except (IndexError, ValueError) as e:
        print(f"Error: {e}. Invalid input '{de}'. Please try again.")
    
    return balance, record

#exit function
def exit_me(): #use '_me' to diffrentiate from Python's original function 
    # Saving the records to 'records.txt' before exiting
    with open('records.txt', 'w') as f:
        f.write(f"{balance}\n")  # Write the balance
        record_strings = [f"{task} {amount}\n" for task, amount in record]
        f.writelines(record_strings)  # Write the records
    print('Thank you. Data saved to records.txt.')

#clear function
def clear(balance, record): 
    tf = input('Are you sure? Please type \'YES\' if you\'re sure to delete your record. ')
    if tf == 'YES':
        balance = 0
        record.clear()
        open("records.txt", "w").close()
        print('Processing...')
        print('Successfully cleared your record, please start again. ')
    else:
        print('Thank you for your consideration. ')
    return balance, record


#main code
init()
while True:
    move = input('What do you want to do (add/view/delete/clear/exit)? ')
    if move == 'add':
        change = str(input('Add some expense or income records with description and amount: ')) 
        balance, record = add(change, record, balance)
    elif move == 'view':
        view(record, balance)
    elif move == 'delete':
        de = input('Which record do you want to delete? ').split()
        balance, record = delete(de, record, balance)
    elif move == 'exit':
        exit_me()
        break
    elif move == 'clear':
        clear(balance, record)
        init()
    else:
        print('Undefined input, please try again.\n(add/view/delete/clear/exit) ')

