import re

ftraces = []
fnames = {}
symbols = []
mapping = []
offset = 0

def parse_line(l):
	m = re.match(r"(\-?\d+)(\<|\>)0x([0-9A-Fa-f]+)", l)
	ftraces.append(m.groups())
	fnames[long(m.groups()[2], 16)] = "func_" + m.groups()[2]


def parse(filename):
	global mapping
	with open(filename) as f:
		# Read header and date
		header = f.readline()
		if header != "VTRACE\n":
			print "ERROR"

		date = f.readline()
		mapping = f.readline().split()
		data = f.readline()

		# Read function traces
		for l in f:
			parse_line(l)


def parse_symbols():
	global offset, symbols
	for s in symbols:
		addr = long(s[0], 16) + offset
		name = s[3]
		if addr in fnames:
			fnames[addr] = name
			print "added " + name + " " + format(addr,"x")
	

def compute_offset(fname, pos):
	global symbols, offset
	for n in symbols:
		if n[3] == fname:
			offset = pos - long(n[0], 16)

def load_symbols(fsym):
	global symbols
	with open(fsym) as f:
		for l in f:
			symbols.append(l.split())


def write_vcd():
	print 	"$date\n"\
		"   Date text. For example: November 11, 2009.\n"\
		"$end\n"\
		"$version\n"\
		"   VCD generator tool version info text.\n"\
		"$end\n"\
		"$comment\n"\
		"   Any comment text.\n"\
		"$end\n"\
		"$timescale 1ps $end\n"\
		"$scope module logic $end"

	for f in fnames.items():
		print "$var wire 1 f" + format(f[0], "x") + " " + f[1] + " $end"

	print	"$upscope $end\n"\
		"$enddefinitions $end"

	print	"#" + ftraces[0][0]
	print	"$dumpvars"
	for f in fnames.keys():
		print "0f" + format(f, "x") 
	print	"$end"


	for t in ftraces:
		print "#" + t[0]
		if t[1] == ">":
			print "1f" + t[2]
		else:
			print "0f" + t[2]
		

parse("./test.vtrc")
load_symbols("./test.sym")
compute_offset(mapping[1], long(mapping[2],16))
print offset
parse_symbols()
#print fnames
#write_vcd()
