import time

###Private Functions
def _wait_for_move(browser, value):
	#checks if the names have been moved to the right
	#browser is the browser object
	#value is one of the values that is being moved to the right
	# s = "'"
	# seq = ("select[@id='ctl00_ContentPlaceHolderGb_lstAssignMembers']/option[@value=", str(value), "]")
	# search = s.join(seq)
	while browser.find_by_id('ctl00_ContentPlaceHolderGb_lstAssignMembers').first.text == '':
		time.sleep(1)
	return

def _select_value(browser, value):
	s = "'"
	seq = ("//select/option[@value=", str(value), "]")
	browser.find_by_xpath(s.join(seq)).click()
	return

def _select_values(browser, values):
	for value in values:
		_select_value(browser, value)
	return

###Public Functions
def move_persons(browser, values):
	#moves the values passed in from the left side to the right side
	assert isinstance(values, list)
	assert len(values) > 0
	_select_values(browser, values)
	#click the move button
	browser.find_by_name('ctl00$ContentPlaceHolderGb$cmdSelectOne').click()
	_wait_for_move(browser, values[0])
	return


