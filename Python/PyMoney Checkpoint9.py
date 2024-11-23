import sys

def initialize_category():
    """
    Initialize the categories
    """
    cat = ['expense', 
           ['food', 
            ['meal', 'snack', 'drink'], 
            'transportation', 
            ['bus', 'railway']], 
            'income', 
            ['salary', 'bonus']
            ]
    return cat

def init():
    """
    Read data from records.txt, or initialize all records if not found
    """
    global balance, record
    # Load data from records.txt if available
    try:
        with open('records.txt', 'r') as f:
            print('Found records.txt, importing...')
            balance = int(f.readline().strip())  # Read the first line (balance)
            try:
                record_lines = f.readlines()  # Read remaining lines (records)
                record = [tuple(line.strip().split()) for line in record_lines]  # Convert lines to tuples
                record = [(cat, task, int(amount)) for cat, task, amount in record]  # Convert amounts to integers
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

def flatten(nested):
    """
    Flatten nested lists to a simple list
    """
    flat = []
    def helper(nested):
        for e in nested:
            if isinstance(e, list):
                helper(e)
            else:
                k = e
                flat.append(k)
    helper(nested)
    return flat

def is_category_valid(a, b) :
    """
    Check if the input category is in the global Categories
    """
    cnt = 0
    categories = flatten(b)
    for i in categories:
        if a == i:
            cnt += 1
    if cnt == 0:
        print("Category not in list, please try again.")
        return 0
    else:
        return 1

def add(change,record,balance):
    """
    split the input into category, description, and price, and allocate them to their lists
    """
    # split the diffrent entries
    change = str.split(change,',')
    # split the description and money in each entry
    for entry in change:
        try:
            cat, task, num = entry.split()
            num = int(num)
            balance += num
            if (is_category_valid(cat,category)):
                record.append((cat, task, num))  # Append task and amount as a tuple
                print(f"Record \'{task} {num}\' added.")
        except ValueError:
            sys.stderr.write(f"Invalid format in entry: '{entry}'. Input should be in this format: \'meal breakfast -50\'\nFailed to add record.")
    return balance, record

    
#view function
def view(record, balance):
    """
    print the records
    """
    i = 0
    print('   Category   Description   Amount')
    print('  ========== ============= ========')
    for rec in record:
        print(f"{i+1}. {rec[0]:<11}{rec[1]:<13} {rec[2]}") #rec[0] appends blanks to fill 23 spaces
        i+=1
    print('====================================')
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

def view_categories(items, level=0):
    """
    print the nested list using recursion
    """
    for item in items:
        if isinstance(item, list):
            view_categories(item, level + 1)
        else:
            indentation = ' ' * level * 2 + '- '
            print('%s%s' % (indentation, item))

def exit_me(): #use '_me' to diffrentiate from Python's original function 
    """
    Save the records to records.txt, and terminate the program
    """
    # Saving the records to 'records.txt' before exiting
    with open('records.txt', 'w') as f:
        f.write(f"{balance}\n")  # Write the balance
        record_strings = [f"{cat} {task} {amount}\n" for cat, task, amount in record]
        f.writelines(record_strings)  # Write the records
    print('Thank you. Data saved to records.txt.')

def clear(balance, record): 
    """
    Clear all records, will prompt the user to reconsider
    """
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

def find(rec, inp):
    """
    find all that are specified by input
    """
    fn = []
    bal = 0
    if inp == 'expense':
        for i in rec:
            if i[2] < 0:
                fn.append(i)
                bal += int(i[2])
    elif inp == 'income':
        for i in rec:
            if i[2] > 0:
                fn.append(i)
                bal += int(i[2])
    else:
        for i in rec:
            for j in i:
                if j == inp:
                    fn.append(i)
                    bal += int(i[2])
    return fn, bal


#main code
init()
category = initialize_category()
while True:
    move = input('What do you want to do (add/view/view categories/delete/clear/exit)? ')
    if move == 'add':
        change = str(input('Add some expense or income records with description and amount: ')) 
        balance, record = add(change, record, balance)
    elif move == 'view':
        view(record, balance)
    elif move == 'view categories':
        view_categories(category)
    elif move == 'find':
        inp = input('Which category do you want to find? ')
        fn, bal = find(record, inp)
        view(fn, bal)
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

