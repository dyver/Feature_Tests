#!/usr/bin/env lua

package.path = '../attohttp/?.lua;' .. package.path

require 'attohttp'

local host = arg[1] or 'localhost'
local port = arg[2] or 8000
attohttp.help()
attohttp.listen(host, port)
