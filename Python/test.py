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




cat = ['expense', 
           ['food', 
            ['meal', 'snack', 'drink'], 
            'transportation', 
            ['bus', 'railway']], 
            'income', 
            ['salary', 'bonus']
            ]
print(flatten(cat))