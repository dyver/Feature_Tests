#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import cgi


header = '''
<html>
<title>Reply Page</title>

<body>

'''

footer = '''
</body>
</html>
'''

page = header

form = cgi.FieldStorage()
if not 'user' in form:
    page += '<h1>Who are you?</h1>\n'
else:
    page += '<h1>Hello <i>{0}</i>!</h1>\n'.format(cgi.escape(form['user'].value))

page += footer

print page

with open('./constructed-page.html', 'w') as f:
    f.write(page)
