import sys

print 'We have ' + str((len(sys.argv) - 1)) + ' arguments'
for arg in sys.argv[1:]:
    print '> ' + arg
