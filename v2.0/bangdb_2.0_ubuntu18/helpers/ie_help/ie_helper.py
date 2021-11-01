"""
Author: Ravi Mula
Description: Helper for MITIE which does the job of extracting the tokens, annotating them and findout relations between the annotated tokens
Email: ravi@iqlect.com
Date: 25-September-2017
"""

import sys
# import pandas as pd
import json
import urllib
import re
import os
import html2text
from subprocess import Popen, PIPE, STDOUT
import time
import configparser
import csv

# Load the variables from CONFIG File
Config = configparser.ConfigParser()
Config.read("config.ini")
debug = Config.get("APP", "DEBUG")

# List of Pronouns
pronouns = ["i", "we", "me", "us", "you", "she", "her", "he", "him", "them", "they",  "that", "which", "who", "whom", "whose", "whichever", "whoever", "whomever", "this", "these", "those", "anybody", "anyone", "anything", "each", "either", "everybody", "everyone", "everything", "neither", "nobody", "no one", "nothing", "one", "somebody", "someone", "something", "both", "few", "many", "several",  "all", "any", "most", "none", "some", "myself", "ourselves", "yourself", "yourselves", "himself", "herself", "itself", "themselves",  "what", "who", "which", "whom", "whose", "my", "your", "his", "her", "its", "our", "your", "their", "mine", "yours", "hers", "ours", "it"]

# List of Determiners
determiners = ["a", "an", "the"]

def printStr(string):
	if debug:
		print (string)

def main(argv):
	if (len(argv) < 3):
		printStr ("Arguments: [<brs_key> <path_to_classes_csv_file> <path_to_urls_file>]")
		exit (1)

	printStr ("\n\n")
	#printStr ("Arguments, arg1 = " + argv[0] + ", arg2 = " + argv[1] + ", arg3 = " + argv[2] + ", arg4 = " + argv[3])
	printStr ("Initializing.......")
	# Create working directory for the new model
	workBaseDir = Config.get("APP", "WORK_FOLDER") + "/"
	workDir = workBaseDir + argv[0] + "/"
	try:
		os.mkdir(workDir)
	except Exception as e:
		pass
	printStr ("Files for this output will be written to the folder '" + workDir +"'\n")

	# Generating Output Filenames
	output_tokens = workDir + argv[0] + ".tokens"
	output_annotations = workDir + argv[0] + ".annotations"
	output_relation = workDir + argv[0] + ".relations"

	start = 0
	if debug:
		start = time.clock()
	printStr ("========= PROFILING (time in seconds) =========")

	printStr ("Reading the tags from CSV file .....")
	# classes = json.loads(pd.read_csv(argv[1]).to_json(orient = "records"))
	try:
		csv_file = csv.DictReader(open(argv[1], 'r'))
	except:
		printStr("Error Reading Classes File = " + argv[1])
		return ("ERROR_READ_CLASSES_FILE")
	classes = []
	for row in csv_file:
		classes.append(row)
	# printStr (json.dumps(classes, indent=4, sort_keys=True))
	classesLo = [x["Name"].lower() for x in classes]
	printStr ("Time taken to read CSV: " + str(time.clock()-start))

	# Reading URLs from File
	urls = []
	try:
		with open(argv[2], "r") as urlsFile:
			for line in urlsFile:
				if(len(line) > 1):
					urls.append(line)
	except:
		printStr("Issue reading the URLs File")
		return ("ERROR_READ_URL_FILE")

	# URL Parser
	try:
		os.mkdir(workDir+"texts")
	except Exception as e:
		pass
	printStr ("\n\nFetching Content for the URLs specified\n")
	printStr ("Texts will be downloaded to the folder '" + workDir +"texts'\n")

	files = []
	flagURLERR = 0
	for url in urls:
		url = url.replace("\n", "")
		try:
			f = urllib.request.urlopen(url)
			text = str(f.read())
			m = re.search('<title>(.*?)</title>', text)
			# title = m.group(1).replace(" ", "_") if m else url.replace(" ", "_")
			title = m.group(1) if m else url.replace(" ", "_")
			text = html2text.html2text(text)
			text = text.replace("\\n", "")
			text = re.sub(r'^\s*$', '', text)
			fileToWrite = workDir+"texts/"+title+".txt"
			try:
				with open(fileToWrite, 'w') as out_file:
					out_file.write(text)
				printStr (" ==>  URL `" + url + "` is written to the file `" + fileToWrite + "`")
				files.append(fileToWrite)
			except:
				pass
		except urllib.error.HTTPError:
			print ("ERROR: `" + url + "` NOT FOUND")
			flagURLERR = 1
			pass
		except urllib.error.URLError:
			print ("ERROR: Some error occured when accessing the URL `" + url + "`")
			flagURLERR = 1
			pass
		except urllib.error.ContentTooShortError:
			print ("ERROR: Content Length doesn't match the retrieved content for URL `" + url + "`")
			flagURLERR = 1
			pass

	printStr ("\nParsing HTML Contents is complete")
	printStr ("Time taken to parse HTML: " + str(time.clock()-start))

	if len(files) == 0:
		printStr("No Files to process input")
		return ("ERROR_NOT_VALID_URLS")

	## Token Extraction
	printStr ("\nGenerating the tokens .....")
	tokens = []
	with open(output_tokens, "w") as tokens_file:
		for file in files:
			with open(file, 'r') as in_file:
				for line in in_file:
					for c in re.split('(\W+)', line):
						if c.strip() != '':
							if " " not in c.strip():
								tokens.append(re.escape(c.strip()))
								tokens_file.write(re.escape(c.strip())+"\n")
							else:
								for word in c.strip():
									if word != " ":
										tokens.append(re.escape(word))
										tokens_file.write(re.escape(word)+"\n")

	# printStr (tokens)
	printStr ("Tokens written to the output file.")
	printStr ("Time taken till generation of tokens: " + str(time.clock()-start))
	allTokens = " ".join(tokens)

	## Index Extraction
	printStr ("\nGenerating the annotations .....")
	indexes = []
	tmp = [] # To Remove duplicate indexes
	tags = {}
	with open(output_annotations, "w") as annotations_file:
		for tag in classes:
			tags[tag["Name"].lower()] = tag["Entity"]
			l = [re.escape(c.strip()) for c in re.split('(\W+)', tag["Name"]) if c.strip() != '']
			stringToSearch = " ".join(l)
			for m in re.finditer(stringToSearch, allTokens,  re.IGNORECASE):
				index = allTokens[0:m.start()+1].count(' ')
				if index not in tmp:
					tmp.append(index)
					t = {"s": index, "e": len(l), "c": tag["Entity"]}
					# printStr (t)
					annotations_file.write(json.dumps(t))
					annotations_file.write("\n")

	printStr ("Annotations written to the output file.")
	printStr ("Time taken till generation of annotations: " + str(time.clock()-start))

	## RelationShip Extraction
	printStr ("\nGenerating the relations .....")
	rels = {}
	rels["relations"] = []
	for file in files:
		p = Popen(['java', '-jar', 'jars/reverb.jar', '-q', '-s', file], stdout=PIPE, stderr=STDOUT)
		for line in p.stdout:
			addFlag = 0
			rel = str(line).split('\\t')
			subA = rel[2].split()
			objA = rel[4].split()
			sub = [i for i in subA if i.lower() in classesLo]
			pred = [i for i in rel[3].split() if i.lower() in classesLo]
			obj = [i for i in objA if i.lower() in classesLo]
			if (len(sub)>0 and len(obj)>0):
				stringToSearch = " ".join(rel[2:4])
				if ( (len([j for j in sub if j.lower() not in pronouns])>0)):
					for m in re.finditer(stringToSearch, allTokens,  re.IGNORECASE):
						r = rel[16].lower().replace(" ", "_")
						if r not in rels["relations"]:
							rels["relations"].append(r)
							rels[r] = []

						# Computing start and end indexes of 'sub' and 'obj'
						t1_s = allTokens[0:m.start()+1].count(' ')
						t2_s = t1_s+len(rel[2].split())+len(rel[3].split())
						t1_e = t1_s+len(rel[2].split())
						t2_e = t2_s+len(rel[4].split())

						if addFlag == 0:
							# Cleaning up "sub" and "obj"
							if (subA[0].lower() in determiners):
								t1_s = t1_s + 1
								rel[2] = " ".join(subA[1:])
							if (objA[0].lower() in determiners):
								t2_s = t2_s + 1
								rel[4] = " ".join(objA[1:])

							# Computing Class Info
							subC = ""
							objC = ""
							for w in subA:
								if w.lower() in tags:
									subC = tags[w.lower()]
							for w in objA:
								if w.lower() in tags:
									objC = tags[w.lower()]

							t = {"t1": {"s": t1_s, "e": t1_e, "v": rel[2], "c" : subC}, "t2": {"s": t2_s, "e": t2_e, "v": rel[4], "c" : objC}, "r":{"c": r, "s":1, "v": r}}
							if t not in rels[r]:
								rels[r].append(t)
							addFlag=1


	# printStr (json.dumps(rels, indent=4, sort_keys=True))
	printStr ("Relations written to the output file.")
	printStr ("Time taken till generation of relations: " + str(time.clock()-start))
	with open(output_relation, "w") as relation_file:
		# relation_file.write(json.dumps(rels))
		relation_file.write(json.dumps({"relations": rels["relations"]}))
		relation_file.write("\n")
		for relation in rels["relations"]:
			for item in rels[relation]:
				relation_file.write(json.dumps(item))
				relation_file.write("\n")

	if flagURLERR > 0:
		return ("SUCCESS_WERR")
	else:
		return ("SUCCESS")

if __name__ == "__main__":
	try:
		if (len(sys.argv) < 4):
			printStr ("Usage: python3 %s <brs_key> <path_to_classes_csv_file> <path_to_urls_file>"%argv[0])
			exit (1)
		main(sys.argv[1:])
	except KeyboardInterrupt:
		printStr ("Interrupt Received.. Shutting Down..")
		exit(1)


"""
TODO:

* Use NLP Techniques to make the relationship extraction better

* Things to improve:
	1. As of now the relations that are written are too minimal, word referencing has to happen lack of which many were removed
	2. Why remove - since MITIE needs classes for both "SUBJECT" and "OBJECT", we are only considering a RDF tuple if both belong to some CLASS that was annotated earlier

"""
