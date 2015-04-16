#!/usr/bin/env python2
# -*- coding: utf-8 -*-


def unicode_string():
    try:
        print u"Строка в кодировке UTF-8 --- UTF-8 encoded string"
    except:
        print 'Fatal error:', sys.exc_info()[0], sys.exc_info()[1]


if __name__ == '__main__':
    unicode_string()
