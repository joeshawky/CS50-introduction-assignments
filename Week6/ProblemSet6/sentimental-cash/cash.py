# TODO
while True:
    try:
        change = float(input("Change owed: "))
        if change >= 0:
            break
    except ValueError:
        continue

quarters = int(change / 0.25)
change %= 0.25
change = round(change, 2)
dimes = int(change / 0.10)
change %= 0.1
change = round(change, 2)
nickels = int(change / 0.05)
change %= 0.05
change = round(change, 2)
pennies = int(change / 0.01)
print(quarters + dimes + nickels + pennies)
