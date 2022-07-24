import csv
import sys
import pdb

def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)


sequences = []

with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        sequences = next(reader)
        sequences.pop(0)
        
clients = []

with open(sys.argv[1], "r") as file2:
    reader2 = csv.reader(file2)
    header = next(reader2)
    for person in reader2:
        for i in range(len(person)):
            if i > 0:
                person[i] = int(person[i])
        clients.append(person)
    
#print(clients)
    
        
p = 0
high = 0
max_loop = []

with open(sys.argv[2], "r") as DNA:
    reader = DNA.read()
    for sequence in range(len(sequences)):
        max_loop.append(0)
        for i in range(len(reader) - 1):
            if reader[i] == sequences[sequence][0]:
                #pdb.set_trace()
                while reader[i:(i+len(sequences[sequence]))] == sequences[sequence]:
                    p += 1
                    i = i + len(sequences[sequence])
                    if p >= high:
                        high = p
                        max_loop[sequence] = high
                p = 0
        high = 0



#print(max_loop)

somme = 0
final = []
dna = False

for numbers in clients:
    for i in range(len(numbers)):
        if i > 0:
            if numbers[i] == max_loop[i-1]:
                somme += 1
    if somme == len(numbers) - 1:
        final.append(numbers[0])
    else:
        final.append("No match")
    somme = 0
    
for i in final:
    if i != "No match":
        print(i)
        dna = True
if dna is False:
    print("No match")
        


file.close()