import os
import sys 

#=================================#
def remove_decimal_precision(value):
    return round(value,4)

#================================#
def create_temporary_files(f1, f2):
    temp1_n = 'temp1'
    temp2_n = 'temp2'
    with open(f1, 'r') as file1, open(f2, 'r') as file2, \
    open(temp1_n, 'w') as temp1, open(temp2_n, 'w') as temp2:
        for line in file1:
            if 'search:' in line:
                continue
            elif 'pages:' in line:
                temp1.write(line)
            elif 'pr:' in line:
                temp1.write('pr:')
                line = line.split(':')
                line = line[1].split(' ')
                for value in line:
                    try:
                        value = remove_decimal_precision(float(value))
                    except:
                        continue
                    temp1.write(f'{value} ')
                temp1.write('\n')
        for line in file2:
            if 'search:' in line:
                continue
            elif 'pages:' in line:
                temp2.write(line)
            elif 'pr:' in line:
                temp2.write('pr:')
                line = line.split(':')
                line = line[1].split(' ')
                for value in line:
                    try:
                        value = remove_decimal_precision(float(value))
                    except:
                        continue
                    temp2.write(f'{value} ')
                temp2.write('\n')
    return temp1_n, temp2_n

#========================#
def compare_files(f1, f2):
    os.system(f'diff {f1} {f2}')

#================#
def remove_file(f):
    os.system(f'rm {f}')

#=========#
def main():
    if len(sys.argv) != 3:
        print('Insert args!')
        exit(1)

    temp1, temp2 = create_temporary_files(sys.argv[1], sys.argv[2])
    compare_files(temp1, temp2)
    remove_file(temp1)
    remove_file(temp2)
    print('All done!')

if __name__ == '__main__':
    main()
