class GenerationException(Exception):
    pass

class TooMuchDataException(GenerationException):
    pass

class InvalidActionException(GenerationException):
    def __init__(self, type: str):
        self.type = type
        super().__init__(f"Invalid action type generated: {type}")