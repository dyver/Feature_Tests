#!/usr/bin/env python2
# -*- coding: utf-8 -*-


def test():
    import sys

    print 'We have ' + str((len(sys.argv) - 1)) + ' arguments:'
    for arg in sys.argv[1:]:
        print '> ' + arg


if __name__ == '__main__':
    print 'I am used as program ...'
    test()
else:
    print 'I am used as module ...'
