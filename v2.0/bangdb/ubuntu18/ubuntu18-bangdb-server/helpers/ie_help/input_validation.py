#from exceptions import *
import os


def input_format_check(total_args):
    print (os.getcwd())
    if len(total_args) < 3:
        print ("Invalid number of arguments You provided invalid number of arguments. Please provide 3 arguments.", len(total_args))
    if total_args[1] not in ['urls', 'query']:
        print ("Invalid arguments Input type can be either 'url' or 'query': ", total_args[1])
    if total_args[1] == 'urls':
        # TODO: handle it in more better way
        try:
            fhandle = open(total_args[2])
        except Exception as e:
            print ("Invalid Input File Unable to open the file.Please")
