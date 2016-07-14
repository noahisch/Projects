from splinter import Browser
import movePersons
import applyCharges
import sys

#Navigate to Charge page
def _navigate():
	browser = Browser()
	browser.visit('http://greekbill.com')

	#sign in
	browser.fill('txtUID', 'RemovedForGithub')
	browser.fill('txtPwd', 'RemovedForGiyhub')
	browser.find_by_name('imageField').first.click()

	#switch to admin account
	#browser.find_by_xpath("//select/option[@value='R32486,C34351']").click()

	#Charge Members
	browser.visit('https://www.greekbill.com/GBWEB/AddCharges.aspx')
	return browser

def _getData(fileName):
	f = open(fileName, 'r')
	r = open('ref2.txt', 'r')
	ref = {}
	for line in r:
		_line = line.strip().split(' ')
		print _line
		ref[_line[0].strip() + ' ' + _line[1].strip()]= _line[2].strip()
	data = ([], [])
	for key, value in ref.items():
		print key, ' ', value
	num = int(f.readline())
	for i in range(num):
		line = f.readline().split(',')
		data[1].append((line[0], line[1], line[2]))
		print i, ' ', data
	num = int(f.readline())
	for i in range(num):
		data[0].append(ref[f.readline().strip().upper()])
	return data
def _getDataReverse(fileName):
	f = open(fileName, 'r')
	r = open('ref.txt', 'r')
	ref = {}
	for line in r:
		_line = line.strip().split(' ')
		print _line
		ref[_line[0].strip() + ' ' + _line[1].strip()]= _line[2].strip()
	data = ([], [])
	for key, value in ref.items():
		print key, ' ', value
	num = int(f.readline())
	for i in range(num):
		line = f.readline().split(',')
		data[1].append((line[0], line[1], line[2]))
		print i, ' ', data
	num = int(f.readline())
	for i in range(num):
		del ref[f.readline().strip().upper()]
	for key, value in ref.items():
		data[0].append(value)
	return data

def main():
	browser = _navigate()
	# print sys.argv
	data = None
	if(len(sys.argv) > 2 and sys.argv[2] == 'reverse'):
		data = _getDataReverse(sys.argv[1])
	else:
		data = _getData(sys.argv[1])
	values = data[0]
	charges = data[1]
	# print values
	print len(values)
	# exit()
	movePersons.move_persons(browser, values)
	applyCharges.apply_charges(browser, charges)
	cmd = raw_input("Make these charges y/n: ")
	if cmd == 'y':
		browser.find_by_id('ctl00_ContentPlaceHolderGb_grdCharges_ctl07_cmdSaveCharges').click()

if __name__ == "__main__":
	main()