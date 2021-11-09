# sush - A shell that sucks less.


A command line interface , written in C.
> under development

# Install
```bash
git clone https://github.com/BishrGhalil/sush.git
cd sush/src
make
sudo make install
```


# Uninstall
```bash
sudo make uninstall
```

# TODO
## bugs:
   - [ ] Find unfreed allocation
## features:
- [o] a better prompt:
  - [X] prompt parser
  - [X] get login name
  - [X] get current working directory
  - [X] get host name
  - [ ] get current time
  - [ ] parse the time
  - [ ] return status
  - [ ] replace $HOME with '~'
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
