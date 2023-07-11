import os
import sys 
import filecmp
import subprocess
import time

OUT_FILE='out.txt'

def execute_program(program, main_dir):
    process = subprocess.Popen(['make'])
    process.wait()

    print('Executing...')
    process2 = subprocess.Popen(f'./{program} {main_dir} < {main_dir}/searches.txt > {OUT_FILE}', shell=True)
    process2.wait()

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
    print('Testing...')
    time.sleep(1)
    result = filecmp.cmp(f1, f2)
    if result:
        print('No differences found!')
        return
    buffer = str(input('Differences found! Do you wanna see more details? [yes/any]'))
    if buffer == 'yes':
        os.system(f'diff {f1} {f2}')
        return
    return

#================#
def remove_file(f):
    os.system(f'rm {f}')

#=========#
def main():
    if len(sys.argv) != 4:
        print('Insert args! [program name][main directory][test file]')
        exit(1)

    execute_program(sys.argv[1], sys.argv[2])
    temp1, temp2 = create_temporary_files(sys.argv[3], OUT_FILE)
    compare_files(temp1, temp2)
    remove_file(temp1)
    remove_file(temp2)

if __name__ == '__main__':
    main()
