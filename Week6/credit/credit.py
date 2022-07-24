gang = False
summ = 0
counter = 0
toAdd = 0
IsValid = False
counterInitial = 0
twoDigitStart = 0
firstDigitStart = 0


while gang is False:
    try:
        credit_card_number = int(input("Number: "))
        gang = True
    except ValueError:
        print("It's not a valid number")

print(len(str(credit_card_number)))

counter = len(str(credit_card_number))
counterInitial = counter
twoDigitStart = int(str(credit_card_number)[0] + str(credit_card_number)[1])
firstDigitStart = int(str(credit_card_number)[0])

while credit_card_number > 0 and counter > 0:
    if counter % 2 == 0:
        toAdd = int(credit_card_number) % 10
        summ += toAdd
    if counter % 2 == 1:
        toAdd = (int(credit_card_number) % 10)*2
        if toAdd > 9:
            toAdd = int(str(toAdd)[0]) + int(str(toAdd)[1])
            summ += toAdd
        else:
            summ += toAdd
    credit_card_number = credit_card_number / 10
    counter -= 1

print(summ)

if summ % 10 == 0:
    IsValid = True
else:
    IsValid = False
    
if IsValid == True and counterInitial == 15 and twoDigitStart == 34 or twoDigitStart == 37:
    print("AMEX")
elif IsValid == True and counterInitial == 16 and twoDigitStart > 50 and twoDigitStart < 56:
    print("MASTERCARD")
elif IsValid == True and counterInitial == 16 or counterInitial == 13 and firstDigitStart == 4:
    print("VISA")
else:
    print("INVALID")
    

