# Turing Machine

This repository is part of a student project for the Language theory module at UVSQ.

## Introduction

The aim of this project is to build a program that emulates a Turing machine.

## Description

You will find in this repository:
- `compte_rendu.pdf` the report submitted with the project (written in french).
- `src` a directory with the source code files.
- `mt` a directory with some examples of input for our application.

## Usage

The programm is built using a Makefile located in the `src` directory.
```bash
% build the application under the name mt
$ make mt
```
The binary can then be used
```bash
$ ./mt [option] file input_word
```

The `-b` option transforms our semi infinite band on the right in a bi infinite band.

For further informations on the machine language or the usage of program, please read the `compte_rendu.pdf`.

## Authors

- Corentin Beaulieu
- Victor Schweisthal
