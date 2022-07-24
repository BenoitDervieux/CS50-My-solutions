#from cs50 import get_string

#s = get_string("Do you agree? ")

#if s.lower() in ["y", "yes"]:
#    print("Agreed.")
#elif s == "N" or s == "n":
#    print("Not agreed.")

#def main():
#        meow(10)

#def meow(n):
#    for i in range(n):
#        print("meow")
    
#main()

#from cs50 import get_int

#def main():
#    i = get_positive_int()
#    print(i)
    

#def get_positive_int():
#    while True: 
#        n = get_int("Positive Integer: ")
#        if n > 0:
#            break
#    return n

#main()

#for i in range(4):
#    print("?", end="")
#print()

#print("?" *4)

#for i in range(3):
#    for j in range(3):
#        print("#", end="")
#    print()

#from cs50 import get_int

#scores = []
#for i in range(3):
#    scores.append(get_int("Score: "))

#average = str(sum(scores) / len(scores))
#print(f"Average: {average}")

#from cs50 import get_string

#s = get_string("Before: ")
#print("After: ", end="")
#for c in s:
#    print(c.upper(), end="")
#print()

#from sys import argv

#if len(argv) == 2:
#    print(f"hello, {argv[1]}")
#else:
#    print("Hello, world")

#from sys import argv

#for arg in argv:
#    print(arg)

#import sys

#if len(sys.argv) != 2:
#    print("missing command-line argument")
#    sys.exit(1)

#print(f"hello, {sys.argv[1]}")
#sys.exit(0)

#import sys

#numbers = [4, 6, 8, 2, 7, 5, 0]

#if 0 in numbers:
#    print("Found")
#    sys.exit(0)
#else:
#    print("Not found")
#    sys.exit(1)

#names = ["Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"]

#if "Ron" in names:
#    print("Found")
#else:
#    print("Not found")

#from cs50 import get_string

#people = {
#    "Brian": "698 658 657",
#    "David": "568 658 654"
#}

#name = get_string("Name: ")
#if name in people:
#    print(f"Number: {people[name]}")

#x = 1
#y = 2

#print(f"x is {x}, y is {y}")
#x, y=y, x
#print(f"x is {x}, y is {y}")

import csv

from cs50 import get_string

with open("phonebook.csv", "a")

    name = get_string("Name: ")
    number = get_string("Number: ")

    writer = csv.writer(file)

    writer.writerow([name, number])
