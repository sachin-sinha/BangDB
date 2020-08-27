from extract_documents import ExtractDocuments
# from test_code.normalization import *
# from test_code.tfidf import *
from exceptions import *
from logging import getLogger
import sys
sys.dont_write_bytecode = True

LOG = getLogger(__name__)


def read_url_from_file(initial_inputs):
    try:
        urls = []
        fhandle = open(initial_inputs["input_form"], 'r')
        for line in fhandle:
            urls.append(line.strip())

        return urls
    except InvalidInputException as err:
        raise err

    except Exception as e:
        raise e


def extract_text_from_url_and_write_to_file(initial_inputs):
    try:
        LOG.debug("Working on text extraction from URL")
        print ("come under url")
        urls = read_url_from_file(initial_inputs)
        obj = ExtractDocuments('', urls)
        obj.output_path = initial_inputs["output_file_path"]
        obj.extract_from_url()

        return {"status_code": 200, "details": "Text extraction from URLs done successfully", "result": "SUCCESS"}

    except InvalidInputException as err:
        raise err

    except Exception as e:
        LOG.error(e.message)
        #raise e
        raise BaseException(message="Text extraction from URL failure", status_code=513)


def extract_text_from_domain_and_write_to_file(initial_inputs):
    try:
        print ("Working on text extraction from query")
        query = initial_inputs["input_form"]
        print ("query:", query)
        obj = ExtractDocuments(query, [])
        obj.output_path = initial_inputs["output_file_path"]
        obj.extract_from_wikipedia()

        # d = word_tokenize_all(all_text_data)
        # call_first(d,all_text_data)
        return {"status_code": 200, "details": "Text extraction from query done sucessfully", "result": "SUCCESS"}

    except InvalidInputException as err:
        raise err

    except Exception as e:
        LOG.error(e.message)
 	#raise e       
        raise BaseException(message="Text extraction from query failure", status_code=513)
