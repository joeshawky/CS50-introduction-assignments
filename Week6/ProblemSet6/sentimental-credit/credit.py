def main():
    card_number = input("Number: ").lstrip().rstrip()

    if valid(card_number) == False:
        print("INVALID")
    else:
        type = card_type(card_number)
        print(f"{type}")


def valid(card_number):
    total_number = 0
    for index, number in enumerate(reversed(card_number)):
        if index % 2 == 0:
            total_number += int(number)
            continue
        twoDigits = int(number) * 2
        for digit in str(twoDigits):
            total_number += int(digit)

    return total_number % 10 == 0


def card_type(card_number):
    card_length = len(card_number)
    isAmex = card_length == 15 and card_number[0:2] in ["34", "37"]
    isMastercard = card_length == 16 and card_number[0:2] in ["51", "55"]
    isVisa = (card_length == 16 and card_number[0] == '4') or card_length == 13
    if isAmex:
        return "AMEX"

    elif isMastercard:
        return "MASTERCARD"

    elif isVisa:
        return "VISA"

    else:
        return "INVALID"


if __name__ == "__main__":
    main()
