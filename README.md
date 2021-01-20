# Iec61850ToIEDScout
iec61850 - goose publisher and subscriber function for send and receive data from Omicron IEDScout software

## How to use
1 - use <a href="https://github.com/mz-automation/libiec61850">libiec61850</a> library for compile your project <br>
2 - set your adapter interface network id - in windows: <b>.\goose_publisher_example.exe 2</b> <br>
3 - for read packet and make your packet you can capture goose traffic with <b>wireshark</b>

## How to Create Data Attribute
	MmsValue* optFlds2 = MmsValue_newBitString(2); // open
	MmsValue_setBitStringFromInteger(optFlds2, 2); 
