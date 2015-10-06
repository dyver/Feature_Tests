#!/usr/bin/env python2
# -*- coding: utf-8 -*-


HOST = 'localhost'
PORT = 8000

import os
import sys
import CGIHTTPServer


server_address = (HOST, PORT)

httpd = CGIHTTPServer.BaseHTTPServer.HTTPServer(server_address, CGIHTTPServer.CGIHTTPRequestHandler)

socket_information = httpd.socket.getsockname()
print 'Serving HTTP on', socket_information[0], 'port', socket_information[1], '...'

httpd.serve_forever()
