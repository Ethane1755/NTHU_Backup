import sys

class Record:
    """Represent a record with category, description, and amount."""
    def __init__(self, category, description, amount):
        self._category = category
        self._description = description
        self._amount = amount

    @property
    def category(self):
        return self._category

    @property
    def description(self):
        return self._description

    @property
    def amount(self):
        return self._amount

class Records:
    """Maintain a list of all the records and the initial amount of money."""
    def __init__(self):
        self._records = []
        try:
            with open('records.txt', 'r') as file:
                print('Found records.txt, importing...')
                self._balance = int(file.readline().strip())
                for line in file:
                    category, description, amount = line.strip().split()
                    self._records.append(Record(category, description, int(amount)))
        except (FileNotFoundError, ValueError):
            print('records.txt not found or invalid, initializing...')
            try:
                self._balance = int(input('How much money do you have? '))
            except ValueError:
                sys.stderr.write("Invalid input for balance. Setting balance to 0.\n")
                self._balance = 0

    def view(self):
        """Print all records and the balance."""
        print('   Category   Description   Amount')
        print('  ========== ============= ========')
        for i, record in enumerate(self._records, 1):
            print(f"{i}. {record.category:<11}{record.description:<13} {record.amount}")
        print('====================================')
        print(f"Now you have {self._balance} dollars.\n")

    def add(self, change, categories):
        """Add a record after validating its category."""
        change = change.split(',')
        for entry in change:
            try:
                cat, task, num = entry.split()
                num = int(num)
                if categories.is_category_valid(cat):
                    self._records.append(Record(cat, task, num))
                    self._balance += num
                    print(f"Record '{task} {num}' added.")
                else:
                    print(f"Invalid category '{cat}'.")
            except ValueError:
                sys.stderr.write(f"Invalid format in entry: '{entry}'. Use 'category description amount'.\n")

    def delete(self, delete_input):
        """Delete a specified record."""
        try:
            category, description, amount = delete_input.split()
            amount = int(amount)
            matching_records = [
                (i, record) for i, record in enumerate(self._records)
                if record.category == category and record.description == description and record.amount == amount
            ]

            if not matching_records:
                print(f"No record found for '{category} {description} {amount}'.")
                return

            if len(matching_records) > 1:
                print(f"There are {len(matching_records)} matching records:")
                for idx, (_, record) in enumerate(matching_records, 1):
                    print(f"{idx}. {record.category} {record.description} {record.amount}")
                choice = int(input('Which one do you want to remove (enter the number)? '))
                if 1 <= choice <= len(matching_records):
                    index_to_remove = matching_records[choice - 1][0]
                else:
                    print("Invalid selection.")
                    return
            else:
                index_to_remove = matching_records[0][0]

            removed_record = self._records.pop(index_to_remove)
            self._balance -= removed_record.amount
            print(f"Record '{removed_record.description} {removed_record.amount}' deleted.")

        except (ValueError, IndexError):
            print("Invalid input. Use 'category description amount'.")

    def save(self):
        """Save all records to records.txt."""
        with open('records.txt', 'w') as file:
            file.write(f"{self._balance}\n")
            for record in self._records:
                file.write(f"{record.category} {record.description} {record.amount}\n")
        print("Records saved to records.txt.")

    def clear(self):
        """Clear all records and reset balance."""
        confirmation = input("Are you sure? Type 'YES' to confirm: ")
        if confirmation == 'YES':
            self._records.clear()
            self._balance = 0
            print("All records cleared. Balance reset to 0.")
        else:
            print("Operation canceled.")

    def flatten(nested):
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

    def find(self, inp, categories):
        """
        Find all records under a specific category or description (e.g., 'meal', 'breakfast').
        """
        found_records = []
        total_amount = 0

        # First, check if the input matches 'expense' or 'income'
        if inp == 'expense':
            found_records = [record for record in self._records if record.amount < 0]
        elif inp == 'income':
            found_records = [record for record in self._records if record.amount > 0]

        # If it's neither 'expense' nor 'income', check if the input matches a valid category
        if not found_records:  # Only check categories if no records have been found for 'expense' or 'income'
            valid_categories = [cat for cat in categories._flatten(categories._categories) if inp == cat]
            
            if valid_categories:
                # If the input is a valid category, find all records under that category or subcategories
                found_records = [
                    record for record in self._records if record.category == inp or 
                    (inp in categories._flatten([record.category]))  # Check if inp is part of any nested category
                ]
            
            # If no category records are found, check for description matches
            if not found_records:
                found_records = [record for record in self._records if record.description == inp]

        # If records are found, calculate the total amount
        if found_records:
            total_amount = sum(record.amount for record in found_records)

            # Print the results
            print(f"Records under the category or description '{inp}':")
            print('   Category   Description   Amount')
            print('  ========== ============= ========')
            for i, record in enumerate(found_records, 1):
                print(f"{i}. {record.category:<11}{record.description:<13} {record.amount}")
            print('====================================')
            print(f"Total amount: {total_amount} dollars.\n")
        else:
            print(f"No records found for category or description '{inp}'.\n")


class Categories:
    """Maintain the category list and provide related methods."""
    def __init__(self):
        self._categories = [
            'expense',
            ['food', ['meal', 'snack', 'drink'], 'transportation', ['bus', 'railway']],
            'income', ['salary', 'bonus']
        ]

    def view(self, items=None, level=0):
        """Recursively print the categories."""
        if items is None:
            items = self._categories
        for item in items:
            if isinstance(item, list):
                self.view(item, level + 1)
            else:
                print(" " * level * 2 + f"- {item}")

    def is_category_valid(self, category):
        """Check if a category is valid."""
        return category in self._flatten(self._categories)

    def _flatten(self, items):
        """Flatten a nested list into a single-level list."""
        flat_list = []
        for item in items:
            if isinstance(item, list):
                flat_list.extend(self._flatten(item))
            else:
                flat_list.append(item)
        return flat_list
    


# Main Program
categories = Categories()
records = Records()

while True:
    action = input("What do you want to do (add/view/delete/view categories/find/clear/exit)? ").strip().lower()
    if action == 'add':
        change = input("Enter records (category description amount, ...): ")
        records.add(change, categories)
    elif action == 'view':
        records.view()
    elif action == 'delete':
        delete_input = input("Which record do you want to delete? (category description amount): ")
        records.delete(delete_input)
    elif action == 'view categories':
        categories.view()
    elif action == 'find':
        inp = input("Which category do you want to find? ").strip()
        records.find(inp, categories)  # Pass the categories object
    elif action == 'clear':
        records.clear()
    elif action == 'exit':
        records.save()
        break
    else:
        print("Invalid command. Try again.")