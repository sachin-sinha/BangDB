
#################################
# 505 - General  Errors
# 513 - Input error
#################################


class BaseException(Exception):
    status_code = 500

    def __init__(self, message="Message", description="description", status_code=None):
        self.message = message
        self.description = description
        if status_code is not None:
            self.status_code = status_code
        super(BaseException, self).__init__(message, description, status_code)
        # super(BaseException, self).__init__()

    def get_error_message(self):
        print ({"status_code": self.status_code, "message": self.message, "details": self.description})


class InvalidInputException(BaseException):

    def __init__(self, message="Invalid Input", description="Input is invalid.", status_code=513):
        super(InvalidInputException, self).__init__(message, description, status_code)

# class ApiError(ApiBase):
#     print "raise error"
#     status_code = 505
