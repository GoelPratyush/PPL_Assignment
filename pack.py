# Script to add headers to all source files and Makefile and create new
# directory for submission. This script creates a directory called Group_53 in
# the parent directory of this script. Group_53 contains the packaged source
# files to be submitted.

import os
import shutil
import glob

name_width = 30
id_width = 13
num_sep = name_width + id_width

header = ['CS F301 Principles of Programming Languages\n',
	'Assignment 1\n',
	'Group 53\n\n',
	('{:' + str(name_width) + 's}' + '{:' + str(id_width) + 's}\n').format('NAME', 'ID'),
	('{:' + str(name_width) + 's}' + '{:' + str(id_width) + 's}\n').format('Nikhil Kumar', '2017B5A70658P'),
	('{:' + str(name_width) + 's}' + '{:' + str(id_width) + 's}\n').format('Goel Pratyush Ram Sharan', '2017B5A70899P'),
	('{:' + str(name_width) + 's}' + '{:' + str(id_width) + 's}\n').format('Dhanuka Aarnav', '2017B5A70945P'),
	('{:' + str(name_width) + 's}' + '{:' + str(id_width) + 's}\n\n').format('Aditya Vishwakarma', '2017B5A70954P'),
	('-' * num_sep) + '\n\n'
]

# Header for *.c and *.h files (requires // for comments).
header_source = '// ' + '// '.join(header)
# Header for Makefile (required # for comments).
header_makefile = '# ' + '# '.join(header)

# Path to output directory.
output_dir = os.path.join('..', 'Group_53')
# Deleting directory if it already exists and creating a new one (overwriting).
if os.path.exists(output_dir):
	shutil.rmtree(output_dir)
os.makedirs(output_dir)

# Files to add header and package.
files = glob.glob('*.c') + glob.glob('*.h') + glob.glob('Makefile')
print(f'Adding header to the following files and copying them to {output_dir}:')
[print('\t' + file) for file in files]

for file in files:
	input_file = open(file, 'r')
	output_file = open(os.path.join(output_dir, file), 'w')

	lines = input_file.read()
	if file == 'Makefile':
		lines = header_makefile + lines
	else:
		lines = header_source + lines

	output_file.write(lines)

	input_file.close()
	output_file.close()

text_files = glob.glob('*.txt')
print(f'Copying the following files to {output_dir} as is:')
[print('\t' + text_file) for text_file in text_files]
# Copying text files to submission directory Group_53.
for text_file in text_files:
	shutil.copy(text_file, output_dir)
