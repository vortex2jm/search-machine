import os
import sys

if len(sys.argv) != 3:
    print('arg1 = pages dir | arg2 = new search file')
    exit(0)

SEARCH_LIMIT = 50000

files = os.listdir(sys.argv[1])

count = 0
with open(sys.argv[2],'w') as search_file:
    for file in files:
        if count > SEARCH_LIMIT:
            break
        path = os.path.join(sys.argv[1], file)
        with open(path,'r') as page_file:
            for line in page_file:
                search_file.write(line)
                count+=1
