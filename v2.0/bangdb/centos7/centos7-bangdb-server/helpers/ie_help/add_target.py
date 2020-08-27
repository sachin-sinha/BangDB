import json
import unicodedata
import sys
import ast
import os
from logic_add_target import *

def compute_target_value(record, logic_mapping_num):
	try:
		if logic_mapping_num not in function_mappings.keys():
			print('Wrong logic number')
			sys.exit(0)
		else:
			if logic_mapping_num == '1':
				target_val = logic_one(record)
			elif logic_mapping_num == '2':
				target_val = logic_two(record)
			return target_val
	except Exception as e:
		print(e)
		print('Unable to generate the target value')
		sys.exit(0)


def add_target_in_json_data(fhandler, target_var_name, logic_mapping_num):
	new_json_data = []
	for record_str in fhandler:
		record_dict = ast.literal_eval(record_str)
		target_val = compute_target_value(record_dict, logic_mapping_num)
		#record[target_var_name] = target_val
		target_str = '\"'+target_var_name+'\"'+':'+str(target_val)
		str2 = record_str.split('{')[-1]
		new_record_str = '{'+target_str+','+str2
		new_json_data.append(new_record_str)
		#new_json_data.append(ast.literal_eval(new_record))
	return new_json_data

def write_json_data_with_target(json_data_with_target, output_file_name, path):
	output_file = open(path+output_file_name, 'w')
	for data in json_data_with_target:
		output_file.write(data)
	output_file.close()

# def read_in_chunks(file_object, chunk_size=500):
#     """Lazy function (generator) to read a file piece by piece.
#     Default chunk size: 1k."""
#     while True:
#         print("hello")
#         data = file_object.read(chunk_size)
#         if not data:
#             break
#         yield data

def main(argv):
	input_file_name = argv[0]
	output_file_name = argv[1]
	input_output_file_path = argv[2]
	target_var_name = argv[3]
	logic_mapping_num = argv[4]
	input_output_file_path = os.path.join(input_output_file_path, '')

	#print("path = ", input_output_file_path)	

	try:
		input_file_path = input_output_file_path + input_file_name
		fhandler = open(input_file_path,'r')
	except Exception as e:
		#print(e)
		print('Invalid input file or invalid path')
		sys.exit(0)

	try:
		json_data_with_target = add_target_in_json_data(fhandler, target_var_name, logic_mapping_num)
	except Exception as e:
		print(e)
		print('Unable to add the target')
		sys.exit(0)

	try:
		write_json_data_with_target(json_data_with_target, output_file_name, input_output_file_path)
	except Exception as e:
		print(e)
		print("Unable to write the data")
		sys.exit(0)

if __name__ == "__main__":
	try:
		if len(sys.argv)!=6:
			print("Usage:python3 add_target.py <input.txt> <output.txt> /path/to/input/output/file <target_var_name> <logic_mapping_number>")
			sys.exit(0)
		main(sys.argv[1:])
	except KeyboardInterrupt:
		printStr ("Interrupt Received.. Shutting Down..")
		exit(1)
