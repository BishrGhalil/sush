# sush __ - A shell that sucks less |Build Status|
==================================================

A command line interface , written in C.
> under development

# Install
```console
git clone https://github.com/BishrGhalil/sush.git
cd sush
make
sudo make install
```


# Uninstall
```console
sudo make uninstall
```

# TODO
## bugs:
   - [ ] Find unfreed allocation
## features:
- [ ] a better prompt:
  - [X] get login name
  - [X] get current working directory
  - [X] get host name
  - [ ] get current time
  - [ ] parse the time
  - [ ] prompt parser
- [X] prev commands list (readline.h)
  - [ ] up to show prev commands
- [ ] quoting and backslash escaping:
  - [ ] qouted argument as one argument
- [ ] keys handling
  - [ ] KEY_UP ==> prev commands
  - [ ] Ctrl+C ==> kill proces
  - [ ] !! prev command
- [ ] more builtins:
  - [ ] prompt setup
  - [ ] alias
  - [ ] history
  - [ ] colors
  - [ ] autosuggest
  - [X] tab complete
- [ ] config file
