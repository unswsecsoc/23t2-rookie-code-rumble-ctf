import ast

FLAG = "BEGINNER{REDACTED}"

def matches(path: str | bytes) -> bool:
    try:
        with open(path) as file:
            return file.read() == FLAG
    except OSError as exception:
        print(exception)

    return False

if __name__ == "__main__":
    print("Good luck: ", end="")

    try:
        literal = ast.literal_eval(input())
        assert isinstance(literal, (str, bytes))
    except:
        print("Not a valid Python string or bytes object.")
    else:
        try:
            matches = matches(literal)
        except:
            print("Something went wrong!")
        finally:
            if matches:
                print(FLAG)
