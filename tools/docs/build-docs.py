#!/usr/bin/env python3

import shutil
import os
import subprocess
import argparse

def rmtree(path):
	if os.path.exists(path):
		shutil.rmtree(path)

def prep_build_folder(source_dir, docs_dir):
	absolute_docs_dir = os.path.abspath(docs_dir)
	print(f"Creating docs directory {absolute_docs_dir}")

	outputDoxyfile = os.path.join(docs_dir, "Doxyfile")

	includeDir = os.path.join(source_dir, "include")
	srcDir = os.path.join(source_dir, "src")

	rmtree(docs_dir)
	os.makedirs(docs_dir, exist_ok=True)
	shutil.copy(os.path.join(source_dir, "docs/config/Doxyfile"), outputDoxyfile)
	with open(outputDoxyfile, 'a') as f:
		f.write(f"OUTPUT_DIRECTORY = {absolute_docs_dir}\n")
		f.write(f"STRIP_FROM_INC_PATH = {includeDir} {srcDir}\n")
		f.write(f"STRIP_FROM_PATH = {includeDir} {srcDir}\n")

def run_doxygen(source_dir, docs_dir):
	subprocess.run(["doxygen", os.path.join(docs_dir, "Doxyfile")], cwd=source_dir)

def install(docs_dir, destination):
	print(f"Installing into {destination}")
	rmtree(destination)
	shutil.copytree(os.path.join(docs_dir, "html"), destination)

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--source-dir", type=str, default=os.getcwd())
	parser.add_argument("--output-dir", type=str, default=os.path.join(os.getcwd(), "build-docs"))
	parser.add_argument("--install", default=None)
	parsed = parser.parse_args()

	prep_build_folder(parsed.source_dir, parsed.output_dir)
	run_doxygen(parsed.source_dir, parsed.output_dir)
	if(parsed.install is not None):
		install(parsed.output_dir, parsed.install)

if __name__ == '__main__':
	main()
