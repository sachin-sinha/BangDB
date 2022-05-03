# FRAUD DETECTION
----------------

## INTRODUCTION

Banks and insurance companies globally are seeing an increasing trend in scams as fraudsters are becoming more sophisticated and can quickly change and adapt their approaches. Traditional methods of fraud detection play an important role in minimizing losses. However, they alone are unable to cope up with the increasing sophistication in frauds. 

Even though we know that no method is perfect, Banks need to be agile to respond to threats and embrace new approaches and technologies to predict and prevent fraud.

One of the methods for Improvement fraud detection systems can be achieved by looking beyond the individual data points, to the connections that link them. Oftentimes these connections go unnoticed until it is too late, something that is unfortunate, as these connections.Oftentimes hold the best clues. Understanding the connections between data, and deriving meaning from these links, doesn’t necessarily mean gathering new data. Significant insights can be drawn from one’s existing data, simply by reframing the problem and looking at it in a new way: as a graph.

Graphs uncovering fraud rings and other sophisticated scams with a high-level of accuracy, and are capable of stopping advanced fraud scenarios in real-time.
Here, we will discuss some of the common patterns that appear in three of the most common damaging types of fraud.

1. First-party bank Fraud

2. Insurance Fraud

3. Ecommerce Fraud 


### 1. First-Party Bank Fraud

First-party fraud involves fraudsters who apply for credit cards, loans, overdrafts and unsecured banking credit lines, with no intention of paying them back. It is a serious problem for banking institutions.

The surprising magnitude of these losses is likely the result of two factors. The first is that first-party fraud is very difficult to detect. Fraudsters behave very similarly to legitimate customers, until the moment they “bust out”, cleaning out all their accounts and promptly disappearing.

A second factor— which will also be explored later in greater detail—is the exponential nature of the relationship between the number of participants in the fraud ring and the overall dollar value controlled by the operation. This connected explosion is a feature
often exploited by organized crime.

However while this characteristic makes these schemes potentially very damaging, it also renders them particularly susceptible to
graph-based methods of fraud detection.

Common Types of First-Party Fraud

• Sleeper fraud occurs when a fraudster acquires a form of credit and, over time, builds up what appears to be normal customer behaviour. As the customer builds trust with the service provider over months or even years, they eventually ask for more credit and then cash in, taking the maximum amount of cash and any goods with them, never to be seen again.

• Bust-out fraud, also known as hit and run, can happen on many types of financial services. It’s quick and sometimes easy, with credit cards and loans being the easiest prey today. In some countries where cheques are in use or have slower clearing cycles, fraudsters can exploit these inefficiencies to inflate a credit balance by up to 10 times the limit and cash out before getting caught.


#### 1.1 Scenario

While the exact details behind each first-party fraud collusion vary from operation to operation, the pattern below illustrates how fraud rings commonly operate:

1. A group of two or more people organize into a fraud ring

2. The ring shares a subset of legitimate contact information, for example phone numbers and addresses, combining them to create a number of synthetic identities

3. Ring members open accounts using these synthetic identities

4. New accounts are added to the original ones: unsecured credit lines, credit cards, overdraft protection, personal loans, etc.

5. The accounts are used normally, with regular purchases and timely payments

6. Banks increase the revolving credit lines over time, due to the observed responsible credit behavior

7. One day the ring “busts out”, coordinating their activity, maxing out all of their credit lines, and disappearing

8. Sometimes fraudsters will go a step further and bring all of their balances to zero using fake checks immediately before the prior step, doubling the damage.

9. Collections processes ensue, but agents are never able to reach the fraudster

10.The uncollectible debt is written off


#### 1.2 Solution
 
We can run appropriate graph queries using graph and run checks during key stages in the customer and account life cycles such as

• At the time the account is created

• During an investigation

• As soon as a credit balance threshold is hit

• When a check is bounced


Graph structure :

The graph data model below represents how the data is linked, and illustrates how one can find rings by simply walking the graph.

<img class="alignnone wp-image-7600" src="https://bangdb.com/wp-content/uploads/2022/04/word-image-3.png" alt="The graph data model represents how the data is linked" width="70%" />


#### 1.3 Steps to Implement 

Step 1. Sample Data: Insert data from CLI

```
CREATE GRAPH Bank_Fraud
USE GRAPH Bank_Fraud

CREATE (UID:101 {"FirstName":"John","LastName":"Doe"})-[HAS_ADDRESS {"info":"Address"}]->(Address:address1 {"Street":"123 NW 1st Street","City":"San Francisco","State":"California","ZipCode":"94101" })
CREATE (UID:102 {"FirstName":"Jane","LastName":"Appleseed"})-[HAS_ADDRESS {"info":"Address"}]->(Address:address1 {"Street":"123 NW 1st Street","City":"San Francisco","State":"California","ZipCode":"94101" })
CREATE (UID:103 {"FirstName":"Matt","LastName":"Smith"})-[HAS_ADDRESS {"info":"Address"}]->(Address:address1 {"Street":"123 NW 1st Street","City":"San Francisco","State":"California","ZipCode":"94101" })
CREATE (UID:104 {"FirstName":"Adam","LastName":"Well"})-[HAS_ADDRESS {"info":"Address"}]->(Address:address4 {"Street":"11 4st Street","City":"San Francisco","State":"California","ZipCode":"94105" })

CREATE (UID:105 {"FirstName":"Emily","LastName":"Green"})-[HAS_ADDRESS {"info":"Address"}]->(Address:address5 {"Street":"1445/3278 box street","City":"San Francisco","State":"California","ZipCode":"94103"})

CREATE (UID:106 {"FirstName":"Rose","LastName":"Breey"})-[HAS_ADDRESS {"info":"Address"}]->(Address:address5 {"Street":"1445/3278 box street","City":"San Francisco","State":"California","ZipCode":"94103"})

CREATE (Address:address1)-[ADDRESS_OF {"info":"Address"}]->(UID:101)
CREATE (Address:address1)-[ADDRESS_OF {"info":"Address"}]->(UID:102)
CREATE (Address:address1)-[ADDRESS_OF {"info":"Address"}]->(UID:103)
CREATE (Address:address4)-[ADDRESS_OF {"info":"Address"}]->(UID:104)

CREATE (UID:101)-[HAS_PHONENUMBER {"info":"Phone_Number"}]->(PhoneNumber:555-555-5555)
CREATE (UID:102)-[HAS_PHONENUMBER {"info":"Phone_Number"}]->(PhoneNumber:555-555-5555)
CREATE (UID:104)-[HAS_PHONENUMBER {"info":"Phone_Number"}]->(PhoneNumber:555-555-5357)
CREATE (UID:103)-[HAS_PHONENUMBER {"info":"Phone_Number"}]->(PhoneNumber:555-555-1234)
CREATE (UID:105)-[HAS_PHONENUMBER {"info":"Phone_Number"}]->(PhoneNumber:555-555-5345)
CREATE (UID:106)-[HAS_PHONENUMBER {"info":"Phone_Number"}]->(PhoneNumber:555-555-5555)

CREATE (UID:102)-[HAS_SSN {"info":"IdentificationID"}]->(SSN:241-23-1234)
CREATE (UID:103)-[HAS_SSN {"info":"IdentificationID"}]->(SSN:241-23-1234)
CREATE (UID:104)-[HAS_SSN {"info":"IdentificationID"}]->(SSN:241-23-6875)
CREATE (UID:101)-[HAS_SSN {"info":"IdentificationID"}]->(SSN:241-23-4567)
CREATE (UID:105)-[HAS_SSN {"info":"IdentificationID"}]->(SSN:241-23-7893)
CREATE (UID:106)-[HAS_SSN {"info":"IdentificationID"}]->(SSN:241-23-4567)

CREATE (UID:101)-[HAS_ACCOUNT]->(AccountNumber:1234567890123456 {"HasCreditCard":1,"HasLoan":0,"Limit":5000,"Balance":1442.23,"ExpirationDate":"01-20","SecurityCode":"123"})
CREATE (UID:101)-[HAS_ACCOUNT]->(AccountNumber:2345678901234567 {"HasCreditCard":0,"HasLoan":0,"Limit":0,"Balance":7054.43})

CREATE (UID:102)-[HAS_ACCOUNT]->(AccountNumber:1234467890123456 {"HasCreditCard":1,"HasLoan":0,"Limit":4000,"Balance":2345.56,"ExpirationDate":"02-20","SecurityCode":"456"})
CREATE (UID:102)-[HAS_ACCOUNT]->(AccountNumber:3456789012345678 {"HasCreditCard":0,"HasLoan":0,"Limit":0,"Balance":4231.12 })
CREATE (UID:102)-[HAS_ACCOUNT]->(AccountNumber:4567890123456789-0 {"HasCreditCard":0,"HasLoan":1,"Limit":0,"LoanAmt": 9045.53,"APR": 0.0541})

CREATE (UID:103)-[HAS_ACCOUNT]->(AccountNumber:4567890123456789 {"HasCreditCard":0,"HasLoan":0,"Limit":0,"Balance":12345.45})
CREATE (UID:103)-[HAS_ACCOUNT]->(AccountNumber:56789012345678900 {"HasCreditCard":0,"HasLoan":1,"Limit":0,"LoanAmt":16341.95,"APR":0.0341})

CREATE (UID:104)-[HAS_ACCOUNT]->(AccountNumber:67890123456789010 {"HasLoan":1,"HasCreditCard":0,"Limit":0,"LoanAmt":11233.4,"APR":0.0567})

CREATE (UID:105)-[HAS_ACCOUNT]->(AccountNumber:7890123456789012 {"HasLoan":0,"HasCreditCard":1,"Limit":8000,"Balance":12345.67,"ExpirationDate":"02-20","SecurityCode":"786"})
```

Step 2. Performing Graph Queries 
Find account holders who share more than one piece of legitimate contact information and Determine the financial risk of a possible fraud ring

1.CHECKING FOR PEOPLE SHARING SAME ADDRESS
```
S=>(@u UID:*)-[@d HAS_ADDRESS]->(@q Address:*);RETURN q.name AS AddressID,COUNT(*) AS AddressRingSize WHERE AddressRingSize > 2
```
2. CHECKING THE RISK FOR "address1". BELOW QUERY DISPLAY ALL CUSTOMERS SHARING ID "address1"
```
S2=>[S1=>(@u UID:*)-[@h HAS_ADDRESS]->(Address:address1)]-[@l HAS_ACCOUNT]->(@a AccountNumber:*);RETURN u.name AS UserID, SUM(a.Limit) AS CreditLimit, SUM(a.LoanAmt) AS LoanAmtBal, MATH_EXP("($CreditLimit+$LoanAmtBal)") AS TotalRisk
```
3. CHECKING TOTAL RISK FOR EACH ADDRESS
```
S2=>[S1=>(@u UID:*)-[@d HAS_ADDRESS]->(@q Address:*)]-[@h HAS_ACCOUNT]->(@a AccountNumber:*);RETURN COUNT(a.name) AS NumberOFAccounts, q.name AS AddressID,SUM(a.Limit) AS CreditLimit, SUM(a.LoanAmt) AS LoanAmtBal, MATH_EXP("($CreditLimit+$LoanAmtBal)") AS TotalRisk WHERE NumberOFAccounts > 6
```

4. CHECKING FOR PEOPLE SHARING SAME PHOMENUMBER
```
S=>(@p PhoneNumber:*)<-[@n HAS_PHONENUMBER]-(UID:*);RETURN p.name AS phonenumber, COUNT(*) AS PhoneRingSize WHERE PhoneRingSize > 2
```


5. CHECKING THE RISK FOR ALL PHONENUMBER RINGS
```
S2=>[S1=>(@u UID:*)-[@n HAS_PHONENUMBER]->(@p PhoneNumber:*)]-[@H HAS_ACCOUNT]->(@a AccountNumber:*);RETURN UCOUNT(u.name) AS PhoneNumberRingSize, p.name AS PhoneNumbers, UCOUNT(a.name) AS NumberOFAccounts, SUM(a.Limit) AS CreditLimit, SUM(a.LoanAmt) AS LoanAmtBal, MATH_EXP("($CreditLimit+$LoanAmtBal)") AS TotalRisk
```
6. CHECKING FOR PEOPLE SHARING SAME IDENTIFICATION NUMBER
```
S=>(@s SSN:*)<-[@l HAS_SSN]-(UID:*);RETURN s.name AS IdentificationNumber, COUNT(*) AS SSNRingSize  WHERE SSNRingSize > 1
```
7. CHECKING THE RISK FOR "241-23-4567". BELOW QUERY DISPLAY ALL CUSTOMERS SHARING ID "241-23-4567"
```
S2=>[S1=>(@u UID:*)-[@l HAS_SSN]->(SSN:241-23-4567)]-[@H HAS_ACCOUNT]->(@a AccountNumber:*);RETURN u.name AS CustomerID, COUNT(a.name) AS NumberOFAccounts, SUM(a.Limit) AS CreditLimit, SUM(a.LoanAmt) AS LoanAmtBal, MATH_EXP("($CreditLimit+$LoanAmtBal)") AS TotalRisk
```
Real-time graph traversals tied to the right kinds of events can help banks identify probable fraud rings: during or even before the
Bust-Out occurs.


### 2. Insurance Fraud:- Whiplash For Cash Fraud

An increase in “crash for cash” cases is driving up the total cost of insurance fraud. In particular, so-called crash for cash scams, in which fraudsters deliberately cause motor accidents in order to make false whiplash claims, have contributed to the increase.
The problem with schemes like whiplash for cash is that it targets the insurance companies' weaknesses. Faced with thousands of claims they have a hard time finding suspicious behavior in the data they process. Luckily, like with stolen credit cards or loan fraud, whiplash for cash criminals can be identified with graph technologies.
2.1 Scenario

In a typical hard fraud scenario, rings of fraudsters work together to stage fake accidents and claim soft tissue injuries. These fake accidents never really happen. They are “paper collisions”, complete with fake drivers, fake passengers, fake pedestrians and even fake witnesses.

Such rings normally include a number of roles.

a. Providers. Collusions typically involve participation from professionals in several categories: Doctors or  Lawyers

b. Drivers

c. Passengers

d. Witnesses

Fraudsters often create and manage rings by “recycling” participants so as to stage many accidents. Thus one accident may have a particular person playing the role of the driver. In another accident the same person may be a passenger or a pedestrian, and in another a witness. Clever usage of roles can generate a large number of costly fake accidents, even with a small number of participants.


#### 2.2 Solution

We can model the data the insurance company has about its accidents as a graph and then find fraud rings with graph queries. 

Graph Structure: 

The graph data model below represents how the data is linked, and illustrates how one can find rings by simply walking the graph.

<img class="alignnone wp-image-7600" src="https://bangdb.com/wp-content/uploads/2022/04/word-image-4.png" alt="The graph data model represents how the data is linked" width="70%" />

#### 2.3 Steps to Implement 

Step 1. Sample Data: Creating graph data from CLI
```
CREATE (Person:UdoHalstein {"first_name":"Udo", "last_name":"Halstein"})
CREATE (Person:RobrechtMiloslav {"first_name":"Robrecht", "last_name":"Miloslav"})
CREATE (Person:MonroeMaksymilian {"first_name":"Monroe", "last_name":"Maksymilian"})
CREATE (Person:SkylerGavril {"first_name":"Skyler","last_name":"Gavril"})
CREATE (Person:EuantheRossana {"first_name":"Euanthe","last_name":"Rossana"})
CREATE (Person:JasmineRhea {"first_name":"Jasmine","last_name":"Rhea"})
CREATE (Person:SousannaPinar {"first_name":"Sousanna","last_name":"Pinar"})
CREATE (Person:ChelleJessie {"first_name":"Chelle", "last_name":"Jessie"})

CREATE (Car:Ford_Focus {"constructor":"Ford", "model":"Focus"})
CREATE (Car:Toyota_Corolla {"constructor":"Toyota", "model":"Corolla"})
CREATE (Car:Kia_Rio {"constructor":"Kia", "model":"Rio"})
CREATE (Car:Hyundai_Elantra {"constructor":"Hyundai", "model":"Elantra"})
CREATE (Car:Ford_Fiesta {"constructor":"Ford", "model":"Fiesta"})
CREATE (Car:Renault_Clio {"constructor":"Renault", "model":"Clio"})

CREATE (Accident:123 {"date":"19/05/2014","location":"New Jersey"})
CREATE (Accident:234 {"date":"23/05/2014","location":"Florida"})
CREATE (Accident:345 {"date":"27/05/2014","location":"Florida"})

CREATE (Car:Ford_Focus)-[IS_INVOLVED {"claim_total":"4817"}]->(Accident:123)
CREATE (Car:Toyota_Corolla)-[IS_INVOLVED {"claim_total":"4693"}]->(Accident:123)
CREATE (Car:Kia_Rio)-[IS_INVOLVED {"claim_total":"4157"}]->(Accident:234)
CREATE (Car:Hyundai_Elantra)-[IS_INVOLVED {"claim_total":"4001"}]->(Accident:234)
CREATE (Car:Ford_Focus)-[IS_INVOLVED {"claim_total":"4513"}]->(Accident:345)
CREATE (Car:Renault_Clio)-[IS_INVOLVED {"claim_total":"4307"}]->(Accident:345)

CREATE (Person:UdoHalstein)-[DRIVER {"claim_total":"19068","info":"Driver"}]->(Car:Ford_Focus)
CREATE (Person:UdoHalstein)-[PASSENGER {"claim_total":"19447","info":"Passenger"}]->(Car:Kia_Rio)
CREATE (Person:UdoHalstein)-[PASSENGER {"claim_total":"19346","info":"Passenger"}]->(Car:Ford_Fiesta)
CREATE (Person:RobrechtMiloslav)-[DRIVER {"claim_total":"19359","info":"Driver"}]->(Car:Toyota_Corolla)
CREATE (Person:RobrechtMiloslav)-[PASSENGER {"claim_total":"19658","info":"Passenger"}]->(Car:Hyundai_Elantra)
CREATE (Person:RobrechtMiloslav)-[PASSENGER {"claim_total":"19282","info":"Passenger"}]->(Car:Renault_Clio)
CREATE (Person:MonroeMaksymilian)-[DRIVER {"claim_total":"19425","info":"Driver"}]->(Car:Kia_Rio)
CREATE (Person:MonroeMaksymilian)-[PASSENGER {"claim_total":"19535","info":"Passenger"}]->(Car:Ford_Focus)
CREATE (Person:MonroeMaksymilian)-[PASSENGER {"claim_total":"19779","info":"Passenger"}]->(Car:Renault_Clio)
CREATE (Person:SkylerGavril)-[DRIVER {"claim_total":"19010","info":"Driver"}]->(Car:Hyundai_Elantra)
CREATE (Person:SkylerGavril)-[PASSENGER {"claim_total":"19423","info":"Passenger"}]->(Car:Ford_Fiesta)
CREATE (Person:SkylerGavril)-[PASSENGER {"claim_total":"19971","info":"Passenger"}]->(Car:Toyota_Corolla)
CREATE (Person:EuantheRossana)-[DRIVER {"claim_total":"19940","info":"Driver"}]->(Car:Ford_Fiesta)
CREATE (Person:EuantheRossana)-[PASSENGER {"claim_total":"19474","info":"Passenger"}]->(Car:Hyundai_Elantra)
CREATE (Person:EuantheRossana)-[PASSENGER {"claim_total":"19762","info":"Passenger"}]->(Car:Ford_Focus)
CREATE (Person:JasmineRhea)-[DRIVER {"claim_total":"19558","info":"Driver"}]->(Car:Renault_Clio)
CREATE (Person:JasmineRhea)-[PASSENGER {"claim_total":"19224","info":"Passenger"}]->(Car:Toyota_Corolla)
CREATE (Person:JasmineRhea)-[PASSENGER {"claim_total":"19520","info":"Passenger"}]->(Car:Kia_Rio)
CREATE (Person:SousannaPinar)-[IS_DOCTOR {"info":"Doctor"}]->(Person:UdoHalstein)
CREATE (Person:SousannaPinar)-[IS_DOCTOR {"info":"Doctor"}]->(Person:MonroeMaksymilian)
CREATE (Person:SousannaPinar)-[IS_DOCTOR {"info":"Doctor"}]->(Person:EuantheRossana)
CREATE (Person:ChelleJessie)-[IS_LAWYER {"info":"Lawyer"}]->((Person:RobrechtMiloslav)
CREATE (Person:ChelleJessie)-[IS_LAWYER {"info":"Lawyer"}]->((Person:MonroeMaksymilian)
CREATE (Person:ChelleJessie)-[IS_LAWYER {"info":"Lawyer"}]->((Person:SkylerGavril)
CREATE (Person:ChelleJessie)-[IS_LAWYER {"info":"Lawyer"}]->((Person:EuantheRossana)
```



Step 2. Performing Graph Queries

Let’s start with a simple example.
1. CHECKING NUMBER OF ACCIDENTS A PERSON IS INVOLVED IN
```
S1=>(@p Person:*)-[@r *]->(@c Car:*);RETURN p.name AS Person, COUNT(*) AS AccidentInvolvedIn
```
2. CHECKING PASSENGERS INVOLVED IN A ACCIDENT 
```
S1=>(@p Person:*)-[@r PASSENGER]->(@c Car:*)-[@f IS_INVOLVED]->(@a Accident:*);RETURN p.name AS PersonName, c.name AS CarModel, a.location AS Location, r.info AS label, a.name AS AccidentID
```
3. CHECKING DRIVER INVOLVED IN A ACCIDENT 
```
S1=>(@p Person:*)-[@r DRIVER]->(@c Car:*)-[@f IS_INVOLVED]->(@a Accident:*);RETURN p.name AS PersonName, c.name AS CarModel, a.location AS Location, r.info AS label,a.name AS AccidentID
```
4. CHECKING FOR ALL THE PEOPLE WHO WERE BOTH DRIVER AND PASSENGER
```
S2=>[S1=>(@p Person:*)-[@d DRIVER]->(@c Car:*)]-[@g PASSENGER]->(@f Car:*);RETURN p.name AS Pname, d.info AS driver, g.info AS Passenger, COUNT(p.name) AS CNT
```

As in the bank fraud example above, graph database queries can be added to the insurance company’s standard checks, at appropriate points in time such as when the claim is filed to flag suspected fraud rings in real time.


### 3. Ecommerce Fraud: Reshipping Scam

Ecommerce fraud is when a fraudster commits a crime via an online store by manipulating the transaction process using stolen or scammed credit card information to illegally obtain the product or payment.

An online store is naturally vulnerable to ecommerce fraud since transactions occur without the user being in direct contact, therefore allowing more opportunities for fraudulent activity. 

One of the ecommerce fraud involves “reshipping scam”.The reshipping scam, which involves fraudsters who use stolen credit cards to buy items—usually expensive items—online. Instead of having the items shipped to the billing address, the fraudster sends them to what’s called a “re-shipper". At the “re-shipper” location, the items are repackaged and usually sent overseas. There, they can often be sold at a high price on the black market.

#### 3.1 Scenario

The scam begins when criminals buy high-dollar merchandise — such as computers, cameras, and other electronics — via the Internet using stolen credit cards. They have the merchandise shipped to addresses in the United States of paid “reshippers” (who may be unaware they are handling stolen goods). The reshippers repackage the merchandise and mail it to locations in Russia, Ukraine, Estonia, Lithuania, Romania, and Germany. 

It works like this :
• the criminals steal credit cards information ;

• they buy goods on ecommerce websites ;

• the goods are sent to a third party ;

• the third party receives the goods and re-ships them to the criminal ;

• the criminal sells the goods and receives cash ;
The third party, recruited via a job and promising a generous compensation, acts as mule.


#### 3.2 Solution

There are a couple of things we can do with that data to identify fraud. A first step might be to compare the billing and shipping address. A difference between a billing and a shipping address might be indicative of a reshipping scam. Furthermore we can look into the IP address. If the IP address localization does not match the billing address or the shipping address, the situation is highly suspicious.
Graph Structure: 

The graph data model below represents how the data is linked, and illustrates how one can find rings by simply walking the graph.

<img class="alignnone wp-image-7600" src="https://bangdb.com/wp-content/uploads/2022/04/word-image-5.png" alt="The graph data model represents how the data is linked" width="70%" />

#### 3.3 Steps to Implement 

Step 1. Sample Data: Creating graph data from CLI
```
CREATE (City:paris {"Name":"Paris"})
CREATE (City:chicago {"Name":"Chicago"})
CREATE (City:san_francisco {"Name":"San Francisco"})
CREATE (City:detroit {"Name":"Detroit"})
CREATE (City:lagos {"Name":"Lagos"})
CREATE (Country:france {"Name":"France"})
CREATE (Country:usa {"Name":"USA"})
CREATE (Country:nigeria {"Name":"Nigeria"})
CREATE (Transaction:order1 {"Date":"11/08/2014", "Items":"A Wonderful World","Amount":10})
CREATE (Transaction:order2 {"Date":"11/08/2014", "Items":"Nike sneakers, Football jersey","Amount":299})
CREATE (Transaction:order3 {"Date":"11/08/2014", "Items":"Perfume","Amount":99})
CREATE (Transaction:order4 {"Date":"11/08/2014", "Items":"Mobile phone","Amount":499})
CREATE (Transaction:order5 {"Date":"11/08/2014", "Items":"Laptop, gifcard","Amount":878})

CREATE (Address:address1 {"Street":"rue_dareau","Number" :"9","City":"Paris"})
CREATE (Address:address2 {"Street":"the47th_street","Number" :"21","City":"Chicago"})
CREATE (Address:address3 {"Street":"folsom_street","Number" :"98","City":"San_francisco"})
CREATE (Address:address4 {"Street":"the23th_street","Number" :"123","City":"Chicago"})
CREATE (Address:Address5 {"Street":"octavia_boulevard","Number" :"211","City":"San_francisco"})
CREATE (Address:Address6 {"Street":"duboce_avenue","Number" :"9","City":"San_francisco"})
CREATE (Address:Address7 {"Street":"carney_street","Number" :"16","City":"Detroit"})

CREATE (Address:address1)-[IS_BILLING_ADDRESS]->(Transaction:order1)
CREATE (Address:address1)-[IS_SHIPPING_ADDRESS]->(Transaction:order1)
CREATE (Address:address1)-[IS_LOCATED_IN]->(City:Paris)

CREATE (Address:address2)-[IS_BILLING_ADDRESS]->(Transaction:order2)
CREATE (Address:address2)-[IS_SHIPPING_ADDRESS]->(Transaction:order2)
CREATE (Address:address2)-[IS_LOCATED_IN]->(City:chicago)

CREATE (Address:address3)-[IS_BILLING_ADDRESS]->(Transaction:order3)
CREATE (Address:address3)-[IS_LOCATED_IN]->(City:san_francisco)

CREATE (Address:address4)-[IS_SHIPPING_ADDRESS]->(Transaction:order3)
CREATE (Address:address4)-[IS_LOCATED_IN]->(City:chicago)

CREATE (Address:Address5)-[IS_BILLING_ADDRESS]->(Transaction:order4)
CREATE (Address:Address5)-[IS_LOCATED_IN]->(City:san_francisco)

CREATE (Address:Address6)-[IS_BILLING_ADDRESS]->(Transaction:order5)
CREATE (Address:Address6)-[IS_LOCATED_IN]->(City:san_francisco)

CREATE (Address:Address7)-[IS_SHIPPING_ADDRESS]->(Transaction:order4)
CREATE (Address:Address7)-[IS_SHIPPING_ADDRESS]->(Transaction:order5)
CREATE (Address:Address7)-[IS_LOCATED_IN]->(City:detroit)

CREATE (City:chicago)-[IS_LOCATED_IN]->(Country:usa)
CREATE (City:detroit)-[IS_LOCATED_IN]->(Country:usa)

CREATE (IP_Address:ip1 {"ip_address":"214.77.224.225","ip_City":"Paris"})
CREATE (IP_Address:ip2 {"ip_address":"48.215.250.22","ip_City":"Chicago"})
CREATE (IP_Address:ip3 {"ip_address":"147.170.219.106","ip_City":"San_francisca"})
CREATE (IP_Address:ip4 {"ip_address":"217.54.121.65","ip_City":"Lagos"})

CREATE (IP_Address:ip1)-[IS_USED_FOR]->(Transaction:order1)
CREATE (IP_Address:ip2)-[IS_USED_FOR]->(Transaction:order2)
CREATE (IP_Address:ip3)-[IS_USED_FOR]->(Transaction:order3)
CREATE (IP_Address:ip4)-[IS_USED_FOR]->(Transaction:order4)
CREATE (IP_Address:ip4)-[IS_USED_FOR]->(Transaction:order5)

CREATE (City:lagos)-[IS_LOCATED_IN]->(Country:nigeria)
CREATE (City:paris)-[IS_LOCATED_IN]->(Country:france)
CREATE (City:san_francisco)-[IS_LOCATED_IN]->(Country:usa)
```

Step 2. Performing Graph Queries

1. Let’s start by looking at the transactions recorded
```
S1=>(@t Transaction:*);RETURN t.name AS OrderID, t.Date AS BookingDate, t.Item AS Item, t.Amount AS Amount
```
2. See the transactions where the billing and shipping addresses are different
If the shipping address and the billing address are different, maybe we are looking at a reshipping scam. We want to identify these transactions for analysis.
```
S1=>(@a Address:*)-[IS_BILLING_ADDRESS]->(@t Transaction:*)<-[@i IS_SHIPPING_ADDRESS]-(@q Address:*);RETURN a.name AS BillingAdd, t.name AS OrderID, q.name AS ShippingAdd, t.Amount AS Amount,a.City AS BillingCity, q.City AS ShippingCity
```
3. Checking for transaction where billing and IP_address used are different cities
```
S1=>(@a Address:*)-[IS_BILLING_ADDRESS]->(@t Transaction:*)<-[@i IS_USED_FOR]-(@q IP_Address:*);RETURN a.name AS BillingAddress, t.name AS OrderID, t.Amount AS Amount, a.City AS BillingCity, q.ip_City AS IP_City
``` 
4. Checking for transaction where shipping and IP_address used are different cities
```
S1=>(@a Address:*)-[IS_SHIPPING_ADDRESS]->(@t Transaction:*)<-[@i IS_USED_FOR]-(@q IP_Address:*);RETURN a.name AS ShippingAddress, t.name AS OrderID, t.Amount AS Amount, a.City AS ShippingCity, q.ip_City AS IP_City
```

## Conclusion

The data we have used here is fake. Furthermore, the fraudsters could use more advanced techniques to avoid detection. Nevertheless, improving the approach of identifying fraudulent patterns and looking for them can be used successfully to fight against fraud.


## Overview of the solution

Please let me know if you want more features in the use case to be added or another use case to be implemented and shared.
Also do send me your feedback / comment at sachin@bangdb.com
