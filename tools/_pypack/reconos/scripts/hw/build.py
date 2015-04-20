import reconos.utils.shutil2 as shutil2
import reconos.utils.template as template

import logging
import argparse
import subprocess

log = logging.getLogger(__name__)

def get_cmd(prj):
	return "build_hw"

def get_call(prj):
	return build_ise_cmd

def get_parser(prj):
	parser = argparse.ArgumentParser("build_hw", description="""
		Builds the hardware project and generates a bitstream to
		be downloaded to the FPGA.
		""")
	return parser

def build_ise_cmd(args):
	build_ise(args)

def build_ise(args):
	prj = args.prj
	hwdir = prj.basedir + ".hw"

	try:
		shutil2.chdir(hwdir)
	except:
		log.error("hardware directory '" + hwdir + "' not found")
		return
	
	subprocess.call("""
	  source /opt/Xilinx/""" + prj.ise + """/ISE_DS/settings64.sh;
	  echo -e "run hwclean\nrun netlist\nexit\n" | xps -nw system""",
	  shell=True)

	print()
	shutil2.chdir(prj.dir)