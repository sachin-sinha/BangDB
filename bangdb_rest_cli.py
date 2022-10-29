import os
from pathlib import Path
import sys
import getopt
import warnings
import requests
import json

if not sys.warnoptions:
    warnings.simplefilter("ignore")

headers = {"Content-Type": "application/json", "Accept": "text/plain", "x-bang-api-key": "6709188284852932043"}

# a sample get request
def get_call(url):
    r = requests.get(url, verify=False)
    #assert r.status_code == 200
    print("Status - ", str(r.status_code));
    print("Response - {}\n".format(str(r.text)))

# a sample post call
def post_call(uri, url, payload):
    data = ''
    try:
        data = json.loads(payload)
        r = requests.post(url, json=data, headers=headers,verify=False)
    except ValueError:
        if "graph" not in uri and "query" not in uri:
            print('payload is not json...')
        data = payload
        r = requests.post(url, data, headers=headers,verify=False)
    #assert r.status_code == 200
    # print("Data: {}".format(str(data)))
    print("Status - ", str(r.status_code));
    print("Response - {}\n".format(str(r.text)))

def main():
    _help = 'BangDB Rest CLI \n\t-m <method [GET | POST]> (Required) \n\t-u <uri> (Required) \n\t-p <payload [Required only for POST calls, input data or file path]> \n\t-e <endpoint [Endpoint with Port]> (Optional) \n\t-z <Insert Event [True | False] [Required for inserting multiple records from specified file]>'
    method = ''
    uri = ''
    payload = ''
    end_point = ''
    insert_event = ''
    argv = sys.argv[1:]
    if len(argv) < 3:
        print(_help)
        sys.exit()
    try:
        opts, args = getopt.getopt(argv,"h:m:u:p:e:z:",["method=","uri=","payload=", "endpoint=", "insert_event="])
    except getopt.GetoptError:
        print(_help)
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print(_help)
            sys.exit()
        elif opt in ("-m", "--method"):
            method = arg
        elif opt in ("-u", "--uri"):
            uri = arg
        elif opt in ("-p", "--payload"):
            payload = str(arg)
        elif opt in ("-e", "--endpoint"):
            end_point = arg
        elif opt in ("-z", "--insert_event"):
            insert_event = str(arg)

    if method == '' or uri == '':
        print('method and uri are required')
        sys.exit(2)

    if "/" not in uri:
        print('Please provide a valid uri')
        sys.exit(2)

    if method not in ["GET", "POST"]:
        print("BangDB Rest CLI only supports [GET | POST] not {}".format(method))
        sys.exit(2)

    if method == 'POST':
        if payload == '':
            print('For POST call, payload is necessary')
            sys.exit(2)

    if end_point:
        print('rest call for method: [', method, '], uri: [', uri, '], endpoint: [', end_point, ']')
    else:
        end_point = "https://testbe.bangdb.com:18080"
        print('rest call for method: [', method, '], uri: [', uri, ']')

    if method == 'GET':
        url = end_point + uri
        print("URL - {}".format(url))
        get_call(url)

    elif method == 'POST':
        IsFile = os.path.isfile(payload)
        print("IsFile: " + str(IsFile))

        if IsFile == True:
            name, extension = os.path.splitext(payload)

            if extension not in [".json", ".txt"]:
                print("Please provide the path of a JSON or TEXT file in Payload.")
                sys.exit(2)
            else:
                with open(payload) as f:
                    payload = f.read()
                    print("Successfully loaded the file.")
        
        if insert_event.lower() == "true" and IsFile == True:
            data = payload.split("\n")
            url = end_point + uri
            print("URL - {}\n{} records found in Payload.\n".format(url, len(data)))
            for num in range(len(data)):
                post_call(uri, url, data[num])
        else:
            url = end_point + uri
            payload = payload.replace('"\\"', '"\\\\"')
            print("URL - {}".format(url))
            post_call(uri, url, payload)

if __name__ == "__main__":
    main()