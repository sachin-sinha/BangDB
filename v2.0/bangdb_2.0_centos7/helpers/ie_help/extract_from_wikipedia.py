from SPARQLWrapper import SPARQLWrapper, JSON
import wikipedia
import urllib3
from bs4 import BeautifulSoup
import re


def extract_main_page(query):
    try:
        page_ = wikipedia.page(query)
        print ("page_:", page_)
    except wikipedia.exceptions.DisambiguationError as e:
        page_ = e.options
    if isinstance(page_, list):
        print ("list type")
        search = page_[0]
        page_ = wikipedia.page(search)
    return page_


def extract_category_from_dbpedia(category):
    if category:
        print ("**inside dbpedia**")
        sparql = SPARQLWrapper("http://dbpedia.org/sparql")
        sparql.setQuery("""
            select distinct ?subject
            where {
            ?concept rdfs:label """ + "\"" + category + "\"" + """@en .
            ?concept ^dct:subject ?subject .
            }
            LIMIT 100
            """)

        sparql.setReturnFormat(JSON)
        results = sparql.query().convert()
        results = results["results"]["bindings"]
        final_results = [item["subject"]["value"] for item in results]
        subdomains = []
        for val in final_results:
            tokens = val.split('/')
            subdomains.append(tokens[-1].replace('_', ' '))
        return subdomains
    else:
        return []


def extract_subdomain_names_from_dbpedia(page_url):
    scrap_links = []
    http = urllib3.PoolManager()
    html = http.request('GET', page_url)
    print ("url GET request status :", html.status)
    if html.status != 200:
        return None
    #html = urllib3.urlopen(page_url)
    #print ("html = ", html)
    soup = BeautifulSoup(html.data, 'html.parser')

    for link in soup.find("div", {"id": "bodyContent"}).findAll("a", href=re.compile("^(/wiki/)(.)*$")):
        if 'href' in link.attrs:
            data = str(link.attrs['href'])
            tokens = data.split('/')
            scrap_links.append(tokens[-1].replace('_', ' '))

    print ("scrap links:")
    index = scrap_links.index('Help:Category')
    category = scrap_links[index + 1].split(':')[-1]

    print ("category:", category)
    subdomains = extract_category_from_dbpedia(category)

    return subdomains


def merge_subdomain_and_links(subdomain_names, all_links):
    for val in subdomain_names:
        if val not in all_links:
            all_links.append(val)

    return all_links
