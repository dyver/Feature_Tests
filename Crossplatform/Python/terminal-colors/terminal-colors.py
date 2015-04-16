#!/usr/bin/env python2
# -*- coding: utf-8 -*-


def terminal_colors():
    import colorama
    colorama.init(autoreset=False)
    from colorama import Fore, Back, Style

    print Fore.BLUE + 'Some blue text ...'
    print Style.BRIGHT + 'and bright ...'
    print Style.DIM + Back.MAGENTA + 'now dimmed and with a magenta background ...'
    print Fore.RESET + Back.RESET + Style.RESET_ALL
    print 'Welcome back to normal text!'

if __name__ == '__main__':
    terminal_colors()
