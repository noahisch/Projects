def _fill_box(browser, base, type_, data):
	text = 'ctl00_ContentPlaceHolderGb_grdCharges_ctl0'+str(base)+type_
	print text
	text.strip()
	print data
	browser.find_by_id(text).fill(data)

def _choose_dropdown(browser, base, value):
	browser.find_by_id('ctl00_ContentPlaceHolderGb_grdCharges_ctl0'+str(base)+'_cmbType').select(value)

def apply_charges(browser, charges):
	assert isinstance(charges, list)
	assert isinstance(charges[0], tuple)
	#More than 5 is not supported at this time
	assert len(charges) <= 5
	base = 02
	for index, charge in enumerate(charges):
		_fill_box(browser, base + index, '_txtDesc', charge[0])
		_choose_dropdown(browser, base + index, charge[1])
		# browser.find_by_id('ctl00_ContentPlaceHolderGb_grdCharges_ct'+str(base+index)+'_cmbType').select(charge[1]).click()
		_fill_box(browser, base+index, '_txtAmount', charge[2])
		# text ='ctl00_ContentPlaceHolderGb_grdCharges_ctl'+str(base + index)+ '_txtDesc'
		# print text
		# print text == 'ctl00_ContentPlaceHolderGb_grdCharges_ctl02_txtDesc'
		# browser.find_by_id('ctl00_ContentPlaceHolderGb_grdCharges_ctl02_txtDesc').fill(charge[0])
		# # browser.find_by_id(text).fill(charge[0])
		# # select an option
		# browser.find_by_id('ctl00_ContentPlaceHolderGb_grdCharges_ctl02_cmbType').select('199239')
		# # fill in money
		# browser.find_by_id('ctl00_ContentPlaceHolderGb_grdCharges_ctl02_txtAmount').fill("0.01")

