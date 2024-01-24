# TODO
def main():
    inputText = input("Text: ")

    sentenceCount = getSentenceCount(inputText)
    wordCount = len(inputText.split(' '))

    letterCount = getLetterCount(inputText)

    index = 0.0588 * (letterCount / wordCount * 100) - 0.296 * (sentenceCount / wordCount * 100) - 15.8
    index = int(round(index))

    if index > 16:
        print("Grade 16+")
    elif index > 1 and index < 17:
        print(f"Grade {index}")
    else:
        print("Before Grade 1")


def getSentenceCount(text):
    sentences = text.replace(' ', '').replace('!', '.').replace('?', '.').split('.')
    sentences.pop(-1)
    return len(sentences)


def getLetterCount(text):
    letterCount = 0
    for letter in text:
        if letter.isalpha():
            letterCount += 1

    return letterCount


main()
