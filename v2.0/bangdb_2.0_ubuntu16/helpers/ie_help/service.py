from application import extract_text_from_domain_and_write_to_file, extract_text_from_url_and_write_to_file
# from .validation.cmd_input_validation import input_format_check
from exceptions import *
from input_validation import *
import sys
import json

def create_input_form(inputs):
    initial_inputs = dict()
    initial_inputs["script_name"] = inputs[0]
    initial_inputs["input_type"] = inputs[1]
    initial_inputs["input_form"] = inputs[2]
    initial_inputs["output_file_path"] = os.path.join(inputs[3], '')
    return initial_inputs


def main(argv):
    if (len(argv) < 3):
         printStr ("Arguments: [<brs_key> <path_to_classes_csv_file> <path_to_urls_file>]")
         exit (1)
    try:
        inputs = argv
        input_format_check(inputs)
        initial_inputs = create_input_form(inputs)

        if initial_inputs["input_type"] == 'query':
            output = extract_text_from_domain_and_write_to_file(initial_inputs)
        elif initial_inputs["input_type"] == 'urls':
            output = extract_text_from_url_and_write_to_file(initial_inputs)

        print (output)
        return json.dumps(output['result'])
        
    except InvalidInputException as err:
        err.get_error_message()

    except Exception as e:
        print (BaseException("Input failure", "Internal Failure", 513), e)

    return "ERROR"

#input_checker(argv)

if __name__ == "__main__":
	try:
		if (len(sys.argv) < 3):
			printStr ("Usage: python3 %s <brs_key> <path_to_classes_csv_file> <path_to_urls_file>"%argv[0])
			exit (1)
		main(sys.argv[0:])
	except KeyboardInterrupt:
		printStr ("Interrupt Received.. Shutting Down..")
		exit(1)
