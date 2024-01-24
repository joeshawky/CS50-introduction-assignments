import sys
from pyfiglet import Figlet
import random


if len(sys.argv) != 1 and len(sys.argv) != 3:
    print(len(sys.argv))
    print("Invalid usage")
    sys.exit(1)

figlet = Figlet()
fontList = figlet.getFonts()



if len(sys.argv) == 1:
    inputText = input("Input: ")
    figlet.setFont(font=fontList[random.randint(0, len(fontList))])
    print(figlet.renderText(inputText))
    sys.exit(0)

if sys.argv[1] in ['-f', '--font'] and sys.argv[2] in fontList:
    inputText = input("Input: ")
    figlet.setFont(font=sys.argv[2])
    print(figlet.renderText(inputText))
    sys.exit(0)
else:
    sys.exit(1)
