#!/usr/bin/env python3

import argparse
import sys
import typing
import os


verbose = False


def parse_namespace(string: str) -> typing.List[str]:
    absolute = len(string) >= 2 and string[:2] == "::"

    res = [n.strip() for n in string.split("::")]

    if absolute:
        res = [""] + res

    return res


def combine_namespace(l: typing.List[str]):
    return "::".join(l)


class VariantDescription:
    name: str
    namespace: typing.List[str]
    members: typing.List[str]
    includes: typing.Set[str]

    def __init__(self):
        self.name = ""
        self.namespace = []
        self.members = ["nullopt"]
        self.includes = {"<type_traits>", "<cinttypes>"}


def parse_variant(file: typing.TextIO) -> VariantDescription:
    description = VariantDescription()

    if verbose:
        print(f"Parsing variant {file.name}")

    namespace_set = False
    name_set = False

    i: int
    line: str
    for i, line in enumerate(file, 1):
        line = line.strip()

        if len(line) == 0 or line[0] in "#;":
            if verbose:
                print(f"Line {i}: Empty or a comment, skipping.")
            continue

        split = [s.strip() for s in line.split('=', 1)]

        if len(split) != 2:
            print(f"Error: {file.name} Line {i} contains no equals sign.", file=sys.stderr)
            exit(1)

        key: str
        value: str
        key, value = split
        key = key.lower()

        if key == "namespace":
            new_namespace = parse_namespace(value)
            if verbose:
                if namespace_set:
                    print(f"Line {i}: Duplicate namespace. Overwriting. Previous value: "
                          f"{combine_namespace(description.namespace)}. New value: {combine_namespace(new_namespace)}")
                else:
                    print(f"Line {i}: Setting namespace. Value: {combine_namespace(new_namespace)}.")
            namespace_set = True
            description.namespace = new_namespace
        elif key == "name":
            value = value.strip()
            if verbose:
                if name_set:
                    print(f"Line {i}: Duplicate name. Overwriting. Previous value: {description.name}. "
                          f"New value"" {value}")
                else:
                    print(f"Line {i}: Setting name. Value: {value}.")
            name_set = True
            description.name = value
        elif key in ["member", "members"]:
            types = [t.strip() for t in value.split(" ")]
            types = [t for t in types if len(types)]

            for t in types:
                if verbose:
                    if t not in description.members:
                        print(f"Line {i}; Adding class {t} to type list.")
                    else:
                        print(f"Line {i}; Ignoring duplicate type {t}.")
                description.members.append(t)
        elif key in ["include", "includes", "header", "headers"]:
            includes = [t.strip() for t in value.split(" ")]
            includes = [t for t in includes if len(includes)]

            for inc in includes:
                if verbose:
                    if inc not in description.includes:
                        print(f"Line {i}; Adding header {inc} to the include list.")
                    else:
                        print(f"Line {i}; Ignoring duplicate type {inc}.")
                description.includes.add(inc)
        else:
            print(f"Error: {file.name} Unknown key {key} on line {i}.", file=sys.stderr)
            exit(1)

    return description


def compile_main(source: typing.TextIO, dest: typing.TextIO, create_dir: bool):
    if create_dir:
        os.makedirs(os.path.dirname(source.name), exist_ok=True)

    variant = parse_variant(source)

    indent = 0
    tab = "\t"

    # Writing helpers

    def write(string: str) -> None:
        dest.write(f"{tab * indent}{string}\n")

    def write_start(string: str) -> None:
        nonlocal indent

        write(string)
        indent += 1

    def write_end(string: str) -> None:
        nonlocal indent

        indent -= 1
        write(string)

    # File headers
    write("#pragma once")

    for i in variant.includes:
        write(f"#include {i}")

    # Namespaces
    for n in variant.namespace:
        if len(n) == 0:
            continue

        write_start(f"namespace {n}"" {")

    # Primary Structure
    write_start(f"struct {variant.name}"" {")

    # Nullopt
    write("struct nullopt {};")

    write("private:")
    # Data Tag
    write("std::size_t _tag_ = 0;")
    # Data Union
    write_start("union _data_t {")

    for i, m in enumerate(variant.members):
        write(f"{m} _{i};")
    # Dtor to keep everyone happy
    write("~_data_t() {}")
    write_end("} _data_;")  # union

    # Type -> Int conversion
    write('template<class T> struct _offset_t {'
          'static_assert(::std::is_same<T, void***>::value, "Type not a member of this variant");'
          'constexpr static std::size_t offset = -1;'
          '};')
    for i, m in enumerate(variant.members):
        write(f"template<> struct _offset_t<{m}>" "{" f"constexpr static std::size_t offset = {i};" "};")

    # Constructor
    write("public:")
    write(f"{variant.name}()" "{ new(&_data_._0) nullopt; _tag_ = 0 }")

    # Copy and Move Constructors
    for i, m in enumerate(variant.members):
        write(f"{variant.name}({m} const& _m)" "{" f" new(&_data_._{i}) {m}(_m); _tag_ = {i} " "}")
        write(f"{variant.name}({m} && _m)" "{" f" new(&_data_._{i}) {m}(std::move(_m)); _tag_ = {i} " "}")

    write_end("};")  # struct

    for i in range(len(variant.namespace)):
        write_end("}")  # namespaces


def debug_main(source: typing.TextIO) -> None:
    result = parse_variant(source)

    print(f"Variant Definition File: {source.name}")
    print(f"Variant Name: {result.name}")
    print(f"Variant Namespace: {combine_namespace(result.namespace)}")
    for i, m in enumerate(result.members):
        print(f"Variant Member Type {i}: {m}")
    for i, n in enumerate(result.includes):
        print(f"Include File {i}: {n}")


def validate_main(source: typing.TextIO) -> None:
    parse_variant(source)
    exit(0)


def main() -> None:
    global verbose
    parser = argparse.ArgumentParser(description="bvestl variant generator")
    parser.add_argument("-v", "--verbose", action="store_true")
    subparser = parser.add_subparsers(title="modes", description="compile, debug, validate", dest="subcommand")
    compile_parser = subparser.add_parser("compile", help="Compile variant definition file to c++")
    compile_parser.add_argument("source", help="variant definition file", type=argparse.FileType(mode="r"))
    compile_parser.add_argument("destination", help="generated header file", type=argparse.FileType(mode="w"))
    compile_parser.add_argument("--no-create-dir", action="store_false", dest="create_dir")

    debug_parser = subparser.add_parser("debug", help="Print the full details of the variant to generate")
    debug_parser.add_argument("source", help="variant definition file", type=argparse.FileType(mode="r"))

    validate_parser = subparser.add_parser("validate", help="Verify variant definition file")
    validate_parser.add_argument("source", help="variant definition file", type=argparse.FileType(mode="r"))

    args = parser.parse_args()

    verbose = args.verbose

    if args.subcommand == "compile":
        compile_main(args.source, args.destination, args.create_dir)
    elif args.subcommand == "debug":
        debug_main(args.source)
    elif args.subcommand == "validate":
        validate_main(args.source)


if __name__ == '__main__':
    main()
