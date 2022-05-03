# Supply Chain Management
-----------------------

## INTRODUCTION

A supply chain is an entire system of producing and delivering a product or service, from the very beginning stage of sourcing the raw materials to the final delivery of the product or service to end-users. The supply chain lays out all aspects of the production process, including the activities involved at each stage, information that is being communicated, natural resources that are transformed into useful materials, human resources, and other components that go into the finished product or service.

Mapping out a supply chain is one of the critical steps in performing an external analysis in a strategic planning process. The importance of clearly laying out the supply chain is that it helps a company define its own market and decide where it wants to be in the future. In developing corporate-level strategies, a company often needs to make decisions on whether to operate a single line of business or enter into other related or unrelated industries.

Each stage of a supply chain is essentially a different industry, for example, raw material extraction and manufacturing. The supply chain enables a company to understand others that are involved in each of the stages, and thereby provides some insights on the attractiveness or competitiveness in industries the company might want to enter in the future.


## SCENARIO

The generic supply chain begins with the sourcing and extraction of raw materials. The raw materials are  taken by a logistics provider to a supplier and then to a manufacturer, or probably to various manufacturers that refine and process them into a finished product.

Afterward, it goes to a wholesaler as the finished product, which is next delivered to a retailer. The retailer sells the product in a store to consumers. 

<img class="alignnone wp-image-7600" src="https://bangdb.com/wp-content/uploads/2022/04/word-image.png" alt="SCENARIO" width="70%" />

Example: The Dairy Supply Chain 

<img class="alignnone wp-image-7600" src="https://bangdb.com/wp-content/uploads/2022/04/word-image-1.png" alt="The Dairy Supply Chain" width="70%" />


## IMPLEMENTATION

For the sake of understanding, we will keep it simple and neglect a lot of things, which would be essential in a real world application.

### 1. Graph structure

<img class="alignnone wp-image-7600" src="https://bangdb.com/wp-content/uploads/2022/04/word-image-2.png" alt="Graph structure" width="70%" />

### 2. Schema for the use-case

The schema contains two streams: “Suppliers” and “Retailers” streams. The Supplier stream contains information about raw materials suppliers, suppliers and the product.
The Retailer stream contains information about product, wholesaler and retailer. 

To starte, register the schema below.
```
{
    "schema":"SupplyChain",
    "streams":[
   	 {
   		 "inpt":[],
   		 "name":"Suppliers",
   		 "type":1,
   		 "swsz":86400,
   		 "attr":[
   			 {"name":"Product","type":5},
   			 {"name":"P_lat","type":11},
   			 {"name":"P_lon","type":11},
   			 {"name":"P_waste","type":9},
   			 {"name":"P_cost","type":9},
   			 {"name":"P_time","type":9},
   			 {"name":"Supplier","type":5},
   			 {"name":"SUP_lat","type":11},
   			 {"name":"SUP_lon","type":11},
   			 {"name":"SUP_waste","type":9},
   			 {"name":"SUP_cost","type":9},
   			 {"name":"SUP_time","type":9},
   			 {"name":"Rawsupplier","type":5},
   			 {"name":"RAW_lat","type":11},
   			 {"name":"RAW_lon","type":11},
   			 {"name":"RAW_waste","type":9},
   			 {"name":"RAW_cost","type":9},
   			 {"name":"RAW_time","type":9}
   		 ],
   		 "catr":[
   			 {"name":"P_SUP_dist","type":11,"opnm":"GEO_DISTANCE","iatr":["P_lat","P_lon","SUP_lat","SUP_lon"]},
   			 {"name":"SUP_RAW_dist","type":11,"opnm":"GEO_DISTANCE","iatr":["SUP_lat","SUP_lon","RAW_lat","RAW_lon"]},
   			 {"name":"Supply_time","type":11,"opnm":"ADD","iatr":["P_time","SUP_time","RAW_time"]},
   			 {"name":"Supply_score","type":11,"opnm":"MATH_EXP","iatr":["((((($P_cost+$SUP_cost)+$RAW_cost)*0.6)+((($P_waste+$SUP_waste)+$RAW_waste)*0.2))+((($P_time+$SUP_time)+$RAW_time)*0.2))"]},
   			 {"name":"Supply_dist","type":11,"opnm":"ADD","iatr":["P_SUP_dist","SUP_RAW_dist"]}
   		 ],
   		 "rels":[
   			 {"sub":"Rawsupplier","obj":"Supplier","rel":"DELIVER_SUPPLIER","sub_props":["RAW_lat","RAW_lon","RAW_waste","RAW_cost","RAW_time"],"obj_props":["SUP_lat","SUP_lon","SUP_waste","SUP_cost","SUP_time"],"rel_props":["SUP_RAW_dist"]},
   			 {"sub":"Supplier","obj":"Product","rel":"DELIVER_PRODUCT","obj_props":["P_lat","P_lon","P_waste","P_cost","P_time"],"rel_props":["P_SUP_dist","Supply_dist","Supply_time","Supply_score"]}
   		 ]
   	 },
   	 {
   		 "inpt":[],
   		 "name":"Retailers",
   		 "type":1,
   		 "swsz":86400,
   		 "attr":[
   			 {"name":"Product","type":5},
   			 {"name":"P_lat","type":11},
   			 {"name":"P_lon","type":11},
   			 {"name":"P_waste","type":9},
   			 {"name":"P_cost","type":9},
   			 {"name":"P_time","type":9},
   			 {"name":"Wholesaler","type":5},
   			 {"name":"W_lat","type":11},
   			 {"name":"W_lon","type":11},
   			 {"name":"W_waste","type":9},
   			 {"name":"W_cost","type":9},
   			 {"name":"W_time","type":9},
   			 {"name":"Retailer","type":5},
   			 {"name":"R_lat","type":11},
   			 {"name":"R_lon","type":11},
   			 {"name":"R_waste","type":9},
   			 {"name":"R_cost","type":9},
   			 {"name":"R_time","type":9}
   		 ],
   		 "catr":[
   			 {"name":"P_W_dist","type":11,"opnm":"GEO_DISTANCE","iatr":["P_lat","P_lon","W_lat","W_lon"]},
   			 {"name":"W_R_dist","type":11,"opnm":"GEO_DISTANCE","iatr":["W_lat","W_lon","R_lat","R_lon"]},
   			 {"name":"Retailer_time","type":11,"opnm":"ADD","iatr":["P_time","W_time","R_time"]},
   			 {"name":"Retailer_score","type":11,"opnm":"MATH_EXP","iatr":["((((($P_cost+$W_cost)+$R_cost)*0.6)+((($P_waste+$W_waste)+$R_waste)*0.2))+((($P_time+$W_time)+$R_time)*0.2))"]},
   			 {"name":"Retailer_dist","type":11,"opnm":"ADD","iatr":["P_W_dist","W_R_dist"]}
   		 ],
   		 "rels":[
   			 {"sub":"Product","obj":"Wholesaler","rel":"DELIVER_WHOLESALER","obj_props":["W_lat","W_lon","W_waste","W_cost","W_time"],"rel_props":["P_W_dist"]},
   			 {"sub":"Wholesaler","obj":"Retailer","rel":"DELIVER_RETAILER","obj_props":["R_lat","R_lon","R_waste","R_cost","R_time"],"rel_props":["W_R_dist","Retailer_dist","Retailer_time","Retailer_score"]}
   		 ]
   	 }
    ]
}
```
We are calculating Geo_distance between every node ( like  Rawsuppler to supplier) using latitude and longitude.
We are calculating scores using formula 

(Waste produce*0.2) + (time*0.2) + (Cost*0.6) 

for every (raw_supplier) -> (retailer) path.


### 3. Date :
```
insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierA0","SUP_lat":110.660283127047,"SUP_lon":21.574243546186,"SUP_waste":515,"SUP_cost":21,"SUP_time":3,"Rawsupplier":"RawsupplierA0","RAW_lat":98.6539252197985,"RAW_lon":107.907432903924,"RAW_waste":390,"RAW_cost":22,"RAW_time":1}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierA0","SUP_lat":110.660283127047,"SUP_lon":21.574243546186,"SUP_waste":515,"SUP_cost":21,"SUP_time":3,"Rawsupplier":"RawsupplierA2","RAW_lat":107.340609324664,"RAW_lon":100.076500620285,"RAW_waste":334,"RAW_cost":28,"RAW_time":4}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierA0","SUP_lat":110.660283127047,"SUP_lon":21.574243546186,"SUP_waste":515,"SUP_cost":21,"SUP_time":3,"Rawsupplier":"RawsupplierA4","RAW_lat":114.764040331065,"RAW_lon":20.7330090061881,"RAW_waste":252,"RAW_cost":27,"RAW_time":2}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierA1","SUP_lat":71.18497232919823,"SUP_lon":1.305450007902,"SUP_waste":264,"SUP_cost":23,"SUP_time":1,"Rawsupplier":"RawsupplierA1","RAW_lat":55.1809352284595,"RAW_lon":14.764481568444,"RAW_waste":270,"RAW_cost":27,"RAW_time":4}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierA1","SUP_lat":71.18497232919823,"SUP_lon":1.305450007902,"SUP_waste":264,"SUP_cost":23,"SUP_time":1,"Rawsupplier":"RawsupplierA3","RAW_lat":54.7975977591404,"RAW_lon":63.5836668672296,"RAW_waste":332,"RAW_cost":23,"RAW_time":3}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierB0","SUP_lat":139.312421505472,"SUP_lon":55.3139769562115,"SUP_waste":277,"SUP_cost":26,"SUP_time":2,"Rawsupplier":"RawsupplierB0","RAW_lat":139.945556614575,"RAW_lon":39.912938103419,"RAW_waste":436,"RAW_cost":35,"RAW_time":3}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierB0","SUP_lat":139.312421505472,"SUP_lon":55.3139769562115,"SUP_waste":277,"SUP_cost":26,"SUP_time":3,"Rawsupplier":"RawsupplierB1","RAW_lat":85.1953246573602,"RAW_lon":62.6767081938293,"RAW_waste":252,"RAW_cost":21,"RAW_time":4}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierB0","SUP_lat":139.312421505472,"SUP_lon":55.3139769562115,"SUP_waste":277,"SUP_cost":26,"SUP_time":2,"Rawsupplier":"RawsupplierB2","RAW_lat":117.83017215995,"RAW_lon":63.9601342330773,"RAW_waste":256,"RAW_cost":29,"RAW_time":2}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierB0","SUP_lat":139.312421505472,"SUP_lon":55.3139769562115,"SUP_waste":277,"SUP_cost":26,"SUP_time":3,"Rawsupplier":"RawsupplierB3","RAW_lat":92.1540045082611,"RAW_lon":61.0228953783365,"RAW_waste":2004,"RAW_cost":33,"RAW_time":3}

insert into SupplyChain.Suppliers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Supplier":"SupplierB0","SUP_lat":139.312421505472,"SUP_lon":55.3139769562115,"SUP_waste":277,"SUP_cost":26,"SUP_time":1,"Rawsupplier":"RawsupplierB4","RAW_lat":20.8551478417528,"RAW_lon":39.0235022177217,"RAW_waste":291,"RAW_cost":25,"RAW_time":4}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler0","W_lat":24.1496562226706,"W_lon":60.6662646306976,"W_waste":1719,"W_cost":31,"W_time":4,"Retailer":"Retailer0","R_lat":42.9124151808688,"R_lon":11.270867062432,"R_waste":396,"R_cost":24,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler0","W_lat":24.1496562226706,"W_lon":60.6662646306976,"W_waste":1719,"W_cost":31,"W_time":4,"Retailer":"Retailer1","R_lat":2.67642030370433,"R_lon":46.4589120323211,"R_waste":1162,"R_cost":22,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler0","W_lat":24.1496562226706,"W_lon":60.6662646306976,"W_waste":1719,"W_cost":31,"W_time":4,"Retailer":"Retailer2","R_lat":106.327472938397,"R_lon":39.9044877627902,"R_waste":253,"R_cost":26,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler0","W_lat":24.1496562226706,"W_lon":60.6662646306976,"W_waste":1719,"W_cost":31,"W_time":4,"Retailer":"Retailer3","R_lat":11.7695052738019,"R_lon":55.3097536366582,"R_waste":292,"R_cost":30,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler1","W_lat":16.3864259628063,"W_lon":56.5913607525871,"W_waste":256,"W_cost":22,"W_time":3,"Retailer":"Retailer4","R_lat":27.861155040609,"R_lon":22.5074480130039,"R_waste":261,"R_cost":36,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler1","W_lat":16.3864259628063,"W_lon":56.5913607525871,"W_waste":256,"W_cost":22,"W_time":3,"Retailer":"Retailer5","R_lat":41.9759160186316,"R_lon":11.0739455500895,"R_waste":356,"R_cost":21,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler1","W_lat":16.3864259628063,"W_lon":56.5913607525871,"W_waste":256,"W_cost":22,"W_time":3,"Retailer":"Retailer6","R_lat":8.82017868443289,"R_lon":48.8499595215361,"R_waste":254,"R_cost":22,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler1","W_lat":16.3864259628063,"W_lon":56.5913607525871,"W_waste":256,"W_cost":22,"W_time":3,"Retailer":"Retailer7","R_lat":30.4589698436766,"R_lon":67.4023712400302,"R_waste":257,"R_cost":22,"R_time":1}

insert into SupplyChain.Retailers values null {"Product":"Product0","P_lat":81.0716978,"P_lon":93.0065783,"P_waste":200,"P_cost":100,"P_time":1,"Wholesaler":"Wholesaler1","W_lat":16.3864259628063,"W_lon":56.5913607525871,"W_waste":256,"W_cost":22,"W_time":3,"Retailer":"Retailer8","R_lat":146.979359059592,"R_lon":130.456315605573,"R_waste":2687,"R_cost":24,"R_time":1}
```
Copy and paste the above insert command on Cli. The data used is not real and is produced randomly 

### 4. Performing Graph Queries

We first have to select the graph on which we want to perform queries.

Select the graph by using below command
```
USE GRAPH SupplyChain_graph
```
1. Listing all Wholesalers with the accumulated distance to every retailer.
```
S=>(@w Wholesaler:*)-[@d DELIVER_RETAILER]->(@r Retailer:*);RETURN w.name AS Wholesaler, r.name AS Retailer, d.Retailer_dist AS Distance
```
2. Let’s check the time required for the ingredients to reach production (Product)
```
S=>(@s Supplier:* {name = "SupplierA$%"})-[@d DELIVER_PRODUCT]->(@p Product:*);RETURN s.name AS Supplier, p.name AS product, d.Supply_time
```
3. Checking time required from production site to retailers
```
S=>(@w Wholesaler:*)-[@d DELIVER_RETAILER]->(@r Retailer:*);RETURN w.name AS Wholesaler, r.name AS Retailer, d.Retailer_time AS time
```
4. Checking supply chain from  raw material supplier "RawsupplierB1".
```
S=>(@raw Rawsupplier:* {name = "RawsupplierB1"})-[@f DELIVER_SUPPLIER]->(@s Supplier:*)-[@d DELIVER_PRODUCT]->(@p Product:*)-[@i DELIVER_WHOLESALER]->(@w Wholesaler:*)-[@t DELIVER_RETAILER]->(@r Retailer:*);RETURN s.name AS Supplier, p.name AS product, w.name AS Wholesaler, r.name AS Retailer, raw.name AS Raw_matterial_supplier, d.Supply_time AS Supply_time, t.Retailer_time AS Retailer_time
```
5. Listing the product site that are less than same distance from the farmer 
```
S=>(@raw Rawsupplier:*)-[@f DELIVER_SUPPLIER]->(@s Supplier:*)-[@d DELIVER_PRODUCT {Supply_dist < 5747127}]->(@p Product:*);RETURN d.Supply_dist AS distance, s.name AS supplier, raw.name AS RawMaterial_Supplier
```
6. Checking the scores, time and distance for Supply and Retailer chain
```
S=>(@raw Rawsupplier:*)-[@f DELIVER_SUPPLIER]->(@s Supplier:*)-[@d DELIVER_PRODUCT {Supply_dist < 5747127}]->(@p Product:*);RETURN d.Supply_dist AS distance, s.name AS supplier, raw.name AS RawMaterial_Supplier, d.Supply_time AS time,d.Supply_score AS Scores

S1=>(@p Product:*)-[@dw DELIVER_WHOLESALER]->(@w Wholesaler:*)-[@dr DELIVER_RETAILER]->(@r Retailer:*);RETURN p.name AS Product, w.name AS Wholesaler, dr.Retailer_dist AS Distance, dr.Retailer_time AS Time, dr.Retailer_score AS Scores, r.name AS Retailer
```
## Conclusion

The biggest challenge in supply chain management is the inherent complexity of modern supply chains. Therefore, none of these examples is sufficient enough for decision-making. There are many additional questions to answer, which are beyond the scope of this scenario.


