import unicodedata
from extract_from_wikipedia import *
from html_parser import HtmlParser
from exceptions import BaseException
from exceptions import InvalidInputException
from bs4 import BeautifulSoup
import sys
import os
sys.dont_write_bytecode = True
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

class ExtractDocuments(object):

    def __init__(self, query='', urls=None):
        self.query = query
        self.urls = urls or []
        self.output_path = ''

    def extract_from_google(self):
        pass

    def extract_from_twitter(self):
        pass

    def extract_from_wikipedia(self):
        try:
            print ("extratcing from wikipedia")
            page_ = extract_main_page(self.query)

            page_url = page_.url
            print ("page url: ", page_url)
            subdomain_names = extract_subdomain_names_from_dbpedia(page_url)
            print ("subdomain names")

            all_links = page_.links

            all_links = merge_subdomain_and_links(subdomain_names, all_links)
            print ("all links and subdomain")

            self.extract_text_from_wikipedia(all_links)
            print ("extracted from wikipedia")
            return

        except Exception as e:
            #print ("error in extraction")
            raise BaseException(message="", description="", status_code=513)

    def extract_text_from_wikipedia(self, all_links):
        for domain in all_links:
            try:
                print (domain)
                new_page = wikipedia.page(domain)
                title = new_page.title
                title = '_'.join([x for x in title.split()])
                text = unicodedata.normalize('NFKD', new_page.content).encode('ascii', 'ignore')
                if text:
                    self.saving_as_text_file(text, title)
            except Exception as _:
                continue

    def extract_from_url(self):
        for url in self.urls:
            try:
                print ("url: ", url)
                html = self.get_html_from_url(url)
                #print ("html: ",html)
                soup = BeautifulSoup(html, "html.parser")
                title = '_'.join([x for x in str(soup.title.string).split()])
                print ("got html")
                text = self.convert_from_html_to_text(html)
                print ("got text")
                if text:
                    self.saving_as_text_file(text, title)
                    print ("file saved")

            except InvalidInputException as e:
                raise e

            except Exception as _:
                continue

    @staticmethod
    def get_html_from_url(url):
        http = urllib3.PoolManager()
        r = http.request('GET', url)
        print ("url GET request status :", r.status)
        if r.status == 200:
            return r.data.decode('utf-8')
        return None
        #return urllib3.urlopen(url).read().decode('utf-8')

    @staticmethod
    def convert_from_html_to_text(html):
        obj = HtmlParser(html)
        text_str = obj.html_to_text()
        return text_str

    def saving_as_text_file(self, text_str, title):
        try:
            name = title + '.txt'
            try:
                os.stat(self.output_path)
            except:
                os.mkdir(self.output_path)
            full_path = self.output_path + name
            text_file = open(full_path, "wb")
            text_file.write(text_str)
            text_file.close()

        except Exception as e:
            #print ("error in saving: ", e)
            raise InvalidInputException(message="Invalid output file path", description="Please enter the valid path", status_code=513)
