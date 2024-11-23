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
