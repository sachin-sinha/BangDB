import sys
import getopt
import warnings
import requests
import json

if not sys.warnoptions:
    warnings.simplefilter("ignore")

end_point = "https://hl7.bangdb.com:18080"
headers = {"Content-Type": "application/json", "Accept": "text/plain"}

# a sample get request
def get_call(uri):
    url = end_point+uri
    r = requests.get(url,verify=False)
    #assert r.status_code == 200
    print(r.status_code);
    print(r.text)

# a sample post call
def post_call(uri,payload):
    url = end_point+uri
    data = ''
    try:
        data = json.loads(payload)
        r = requests.post(url, json=data, headers=headers,verify=False)
    except ValueError:
        print('payload is not json...')
        data = payload
        r = requests.post(url, data, headers=headers,verify=False)
    #assert r.status_code == 200
    print(r.status_code);
    print(r.text)

def main():
    method = ''
    uri = ''
    payload = ''
    argv = sys.argv[1:]
    if len(argv) < 3:
        print('bandb_rest_cli.py -m <method[GET | POST]> -u <uri> -p <payload [only for POST calls, input data]>')
        sys.exit()
    try:
        opts, args = getopt.getopt(argv,"hm:u:p:",["method=","uri=","payload="])
    except getopt.GetoptError:
        print('bandb_rest_cli.py -m <method[GET | POST]> -u <uri> -p <payload [only for POST calls, input data]>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print('bandb_rest_cli.py -m <method[GET | POST]> -u <uri> -p <payload [only for POST calls, input data]>')
            sys.exit()
        elif opt in ("-m", "--method"):
            method = arg
        elif opt in ("-u", "--uri"):
            uri = arg
        elif opt in ("-p", "--payload"):
            payload = arg

    if method == '' or uri == '':
        print('method and uri are required')
        sys.exit(2)
    if method == 'POST':
        if payload == '':
            print('for POST call, payload is necessary')
            sys.exit(2)

    print('rest call for method: [', method, '], uri: [' ,uri,']')

    if method == 'GET':
        get_call(uri)
    elif method == 'POST':
        post_call(uri,payload)

if __name__ == "__main__":
    main()
