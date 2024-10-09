import sys

# Function to check for duplicates in the list
def check_duplicate(items, a):
    count = 0
    indices = []  # To store the indices of the matching records
    for i, c in enumerate(items):
        if c == a:
            count += 1
            indices.append(i)  # Store the index of the duplicate
    if count > 1:
        return True, count, indices
    elif count == 1:
        return True, count, indices
    else:
        return False, count, indices


# Load data from records.txt if available
try:
    with open('records.txt', 'r') as f:
        balance = int(f.readline().strip())  # Read the first line (balance)
        record_lines = f.readlines()  # Read remaining lines (records)
        record = [tuple(line.strip().split()) for line in record_lines]  # Convert lines to tuples
        record = [(task, int(amount)) for task, amount in record]  # Convert amounts to integers
except FileNotFoundError:
    # If the file doesn't exist, prompt the user for the initial balance
    try:
        balance = int(input('How much money do you have? '))
    except ValueError:
        sys.stderr.write("Invalid input for balance. Setting balance to 0.\n")
        balance = 0
    record = []  # Initialize an empty record list
except ValueError:
    sys.stderr.write("Error reading records. Starting with a clean record.\n")
    balance = 0
    record = []

# Main program loop
while True:
    try:
        move = input('What do you want to do (add/ delete/ view/ exit)? ').strip().lower()

        if move == 'add':
            # Adding new records
            change = input('Add some expense or income records with description and amount (e.g., breakfast -50, salary 1000): ')
            change = change.split(',')  # Split different entries
            for entry in change:
                try:
                    task, num = entry.split()
                    num = int(num)
                    balance += num
                    record.append((task, num))  # Append task and amount as a tuple
                except ValueError:
                    sys.stderr.write(f"Invalid format in entry: '{entry}'. Please enter description and amount correctly.\n")

        elif move == 'view':
            # Viewing records
            print(record)
            print('Description                Amount')
            print('======================     ======')
            for i, rec in enumerate(record, start=1):  # Start numbering from 1
                print(f"{i}. {rec[0]:<26} {rec[1]:>6}")
            print('======================     ======')
            print(f"Now you have {balance} dollars.")

        elif move == 'delete':
            # Deleting a record
            try:
                de = input('Which record do you want to delete (e.g., breakfast -50)? ').split()
                if len(de) != 2:
                    raise ValueError("Please provide both description and amount.")
                
                task_to_delete = de[0]
                amount_to_delete = int(de[1])
                duplicate_check, count, indices = check_duplicate(record, (task_to_delete, amount_to_delete))

                if duplicate_check:
                    if count > 1:  # Multiple records found
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
                            raise IndexError("Invalid selection.")
                    else:
                        record.remove((task_to_delete, amount_to_delete))
                        balance -= amount_to_delete
                        print(f"Record '{task_to_delete} {amount_to_delete}' deleted.")
                else:
                    print("Record not found.")
            except ValueError as ve:
                sys.stderr.write(f"Error: {ve}\n")
            except IndexError as ie:
                sys.stderr.write(f"Error: {ie}\n")

        elif move == 'exit':
            # Saving the records to 'records.txt' before exiting
            with open('records.txt', 'w') as f:
                f.write(f"{balance}\n")  # Write the balance
                record_strings = [f"{task} {amount}\n" for task, amount in record]
                f.writelines(record_strings)  # Write the records
            print('Thank you. Data saved to records.txt.')
            break

        else:
            print('Undefined input, please try again.')

    except Exception as e:
        sys.stderr.write(f"An unexpected error occurred: {e}\n")