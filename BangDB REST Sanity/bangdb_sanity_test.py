import os
import pandas as pd
from pathlib import Path
import sys
import getopt
import warnings
import requests

if not sys.warnoptions:
    warnings.simplefilter("ignore")

headers = {"Content-Type": "application/json", "Accept": "text/plain", "x-bang-api-key": "6709188284852932043"}

def post_call(url, data):
    r = requests.post(url, data, headers=headers,verify=False)
    response = r.text
    status = r.status_code
    return response, status

def main():
    _help = 'BangDB Auto Sanity Rest CLI\n\t-g <graph> (Required) \n\t-f <filepath [Input CSV file path]> (Required) \n\t-e <endpoint [Endpoint with Port (Default: https://testbe.bangdb.com:18080)]> (Optional)'
    graph = ''
    file_path = ''
    end_point = ''
    argv = sys.argv[1:]
    if len(argv) < 2:
        print(_help)
        sys.exit()
    try:
        opts, args = getopt.getopt(argv,"g:f:e:",["graph=","filepath=", "endpoint="])
    except getopt.GetoptError:
        print(_help)
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print(_help)
            sys.exit()
        elif opt in ("-g", "--graph"):
            graph = arg
        elif opt in ("-f", "--filepath"):
            file_path = arg
        elif opt in ("-e", "--endpoint"):
            end_point = arg

    if graph == '' or file_path == '':
        print('Graph Name & File Path both are required')
        sys.exit(2)

    if os.path.isfile(file_path) == False:
        print("Please provide a valid Input File Path.")
        sys.exit(2)

    name, extension = os.path.splitext(file_path)
    if extension != ".csv":
        print("Please provide Input File in CSV.")
        sys.exit(2)

    if end_point == "":
        end_point = "https://testbe.bangdb.com:18080"

    df = pd.read_csv(file_path)
    print("There are {} queries for Sanity Test.\n".format(df.shape[0]))

    uri = "/graph/{}/query".format(graph)
    url = end_point + uri
    actual_output_lst = list()
    status_lst = list()
    sanity_check_lst = list()

    for i in range(df.shape[0]):
        response, status = post_call(url, df["query"][i])
        if response == '{"msg":"table doesn\'t exist, can\'t open"}':
            print("Invalid Graph Name provided.")
            sys.exit(2)
        actual_output_lst.append(response)
        status_lst.append(status)

        if response == df["expected_output"][i]:
            print("Server Response for Query {} matched successfully with Expected Output.\n".format(i))
            sanity_check_lst.append("Valid")
        else:
            print("For Query at index {}, actual output didn't match with the expected output.\n".format(i))
            sanity_check_lst.append("Invalid")

    df = pd.concat([df, pd.Series(actual_output_lst, name="actual_output"), pd.Series(status_lst, name="status_code"), pd.Series(sanity_check_lst, name="sanity_check")], axis=1)
    df.to_csv("BangDB Sanity Output.csv", index=False)
    print("BangDB Sanity Test Output is stored in your local machine.\n")

    if len(df[df["sanity_check"] == "Invalid"]) > 0:
        invalid_df = df[df["sanity_check"] == "Invalid"]
        invalid_df.reset_index(drop=True, inplace=True)
        invalid_df.to_csv("BangDB Sanity Test Invalid Output.csv", index=False)
        print("BangDB Sanity Test Invalid Output is also stored in your local machine.\n")

if __name__ == "__main__":
    main()