import random

function_mappings = {'1':'logic_one','2':'logic_two'}

def logic_one(record):
	'''
	Attributes : ['total_remove_from_cart', 'views_per_product_per_session', 'add_to_cart_count',
				  'quantity', 'total_events_in_this_page', 'total_events_happened', 'time_spent_on_this_page',
				  'total_time_spent', 'brand_name', 'product_id', 'price_per_unit', '__startTime',
				  '__endTime']
	'''
	record['total_time_spent'] = record['total_time_spent']+3
	record['time_spent_on_this_page'] = int(record['total_time_spent']/3)
	if random.randrange(1, 100, 1) > 50:
		if record['total_remove_from_cart'] == 0:
			record['quantity'] = random.randrange(record['add_to_cart_count'],record['add_to_cart_count']+4,1)
			record['total_remove_from_cart'] = random.randrange(1,3,1)
			record['views_per_product_per_session'] = random.randrange(1,20,1)
			record['total_events_in_this_page'] = random.randrange(1,40,1)
			record['total_events_happened'] = random.randrange(record['total_events_in_this_page'], 100, 1)
			record['time_spent_on_this_page'] = random.randrange(20, 1000, 1)
			record['total_time_spent'] = random.randrange(record['time_spent_on_this_page'], 2000, 1)
	r1 = record['total_events_happened']/record['total_time_spent']
	r2 = record['total_events_in_this_page']/record['time_spent_on_this_page']
	r3 = 0
	r5 = 0
	if(record['quantity'] == 0):
		r3 = 1
	elif (record['quantity'] > record['add_to_cart_count']):
		r5 = 1
	r4 = record['total_remove_from_cart']
	target_val = (r1*20 + r2*80 + r3*20 + r4*40 + r5*10)/150
	return target_val

def logic_two(record):
	'''
	Attributes : ['userid', 'clickid', 'usertype',
				  'page', 'cartsize', 'cat']
	'''
	r1 = record['cartsize']
	r3 = record['clickid']
	target_val = (r1*90 + r3*50)/1500
	return target_val
