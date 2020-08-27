import html2text
import unicodedata
from bs4 import BeautifulSoup
import re


class HtmlParser(object):
    def __init__(self, html):
        self.html = html
        self.soup = BeautifulSoup(self.html, 'html.parser')

    def html_to_text(self):
        """
        This function will parse the html page and extract text data from it.
        :return:
        """
        try:
            print(" comes under html to text parser")
            text_maker = html2text.HTML2Text()
            text_maker.ignore_links = True
            text_maker.ignore_images = True
            text_maker.ignore_tables = False
            text_maker.images_to_alt = True
            text_maker.no_automatic_links = True
            text_maker.single_line_break = True
            text_unicode = text_maker.handle(self.html)
            text_str = unicodedata.normalize('NFKD', text_unicode).encode('ascii', 'ignore')
            # if text_str:
            #     text_str = self.remove_text_before_title(text_str)
            #     text_str = self.remove_extra_space(text_str)
            #print ("parsed text = ", text_str)
            return text_str

        except Exception as e:
            print ("error in htmltotext parser: ", e)

    def remove_text_before_title(self, text_data):
        """remove all the text which is above the title in the page"""
        try:
            print("remove text before title")
            title = self.soup.title.string
            print (title)
            title_split = title.split()
            if len(title_split) > 1:
                title = ' '.join(x for x in title_split[:len(title_split) / 2])
                start_index = text_data.find(title)
                if start_index != -1:
                    text_data = text_data[start_index:]

            return text_data

        except Exception as e:
            print (e)

    def remove_end_text(self, text_data):
        pass

    def remove_extra_space(self, text_data):
        """

        :rtype: string object
        """
        print ("remove extra space")
        text_data = re.sub('(\\n)+', ' ', text_data)
        return text_data

    def remove_special_keywords(self, text_data):
        pass
