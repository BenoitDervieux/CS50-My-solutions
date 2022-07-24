#from PIL import Image, ImageFilter

#before = Image.open("courtyard.bmp")

#after = before.filter(ImageFilter.BoxBlur(10))
#after.save("courtyardBlur.bmp")


#words = set()

#def check(word):
#    if word.lower() in words:
#        return True
#    else:
#        return False

#def load(dictionary):
#    file = open(dictionary, "r")
#    for line in file:
#        words.add(line.rstrip())
#    file.close()
#    return True
    
#def size():
#    return len(words)
    
#def unload():
#    return True

answer = input("What's your name? ")
print(f"Wesh {answer}, ça dit quoi ?")