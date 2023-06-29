#!/usr/bin/env python3

FLAG = "thisstringisimpossibletoguessyouwillneverguessitmanually"

while 1:
    try:
        print(
            "The aliens have stolen our flag! You know that it is wrapped in 'BEGINNER{}', but you don't know what is inside the curly braces!"
        )
        print(
            "The aliens however will allow you to take a guess of a piece of text that may or may not be inside the curly braces."
        )
        print(
            "For example, if the curly braces contained 'flag', and your guess was 'la', that would be inside the flag as 'la' is in 'flag'."
        )
        print("What's your guess?\n> ", end="")

        data = input().strip()

        if data == FLAG:
            print("That's the flag! How did you know?")
            exit()
        if data in FLAG:
            print("Yes, that is inside the flag.\n")
        else:
            print("No, that is not inside the flag!\n")

    except Exception as e:
        print("Error occurred", e)
