#!/usr/bin/env lua

attohttp = {}

attohttp._ABOUT = 'Atto HTTP server'
attohttp._VERSION = '2017.10.03.00'
attohttp._AUTHORS = 'Sergey Nikonov <dyver@hotmail.com>'
attohttp._DESCRIPTION =
    attohttp._ABOUT .. '\nVersion: ' .. attohttp._VERSION ..
    '\nAuthor: ' .. attohttp._AUTHORS .. '\n' .. [[
Incredibly simple and small HTTP server with CGI support.
]]

attohttp.help = function()
    print(attohttp._DESCRIPTION)
end

local socket = require 'socket'
local environ = require 'environ.process'

local headers = {
    separator = '\r\n',
    ok = 'HTTP/1.1 200 OK\r\n',
    fail = 'HTTP/1.1 501 Not Implemented\r\n',
}
local default_page = [[
    <!DOCTYPE html PUBLIC
        '-//W3C//DTD XHTML 1.0 Strict//EN'
        'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'
    >
    <html>
        <head>
            <meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
            <title>!!! Жопа !!!</title>
        </head>
        <body>
            <h1>Что-то пошло не так...</h1>
        </body>
    </html>
]]

local get_mime = function(extension)
    local default_mime = 'application/octet-stream'
    local mime_types = {
        html = 'text/html',
        lua = 'text/lua',
        ico = 'image/x-icon',
    }
    return mime_types[extension] or default_mime
end

local format_address = function(ip, port) return ip .. ':' .. port end

attohttp.listen = function(host, port)
    local host = host or 'localhost'
    local port = port or 8000
    local server = assert(socket.bind(host, port))
    while true do
        io.write("Waiting for client on " .. format_address(server:getsockname()) .. "... ")
        io.flush()
        local client = assert(server:accept())
        print("established connection form " .. format_address(client:getpeername()) .. '.')
        local input_line, err = client:receive()
        local output_message
        local build_message = function(header, data_type, data)
            output_message = header
            output_message = output_message .. 'Content-Type: ' .. get_mime(data_type) .. '\r\n'
            output_message = output_message .. 'Content-Length: ' .. #data .. '\r\n'
            output_message = output_message .. headers.separator
            output_message = output_message .. data
        end
        local request = {}
        local parameters = {}
        local parse_input_line = function()
            local command, path = input_line:match('([^%s]+)%s+([^%s]+)%s+HTTP')
            if command then
                request.command = command
                if path == '/' then path = '/index.html' end
                request.path = path
                request.directory, request.extension = path:match('^(.*/)[^/]+%.(.+)$')
                print('>>>{' .. input_line .. '}')
            else
                local name, value = input_line:match('([^%s]+):%s+(.+)$')
                if name and value then
                    name = name:upper():gsub('-', '_')
                    parameters[name] = value
                end
            end
        end
        local process_command = function()
            local process_CGI_request = function()
                environ.setenv('REMOTE_ADDR', client:getpeername())
                environ.setenv('SERVER_SOFTWARE', attohttp._ABOUT)
                local key, value
                for key, value in pairs(parameters) do
                    environ.setenv(key, value)
                end
                local data_file = os.tmpname()
                local error_file = os.tmpname()
                local handle, e = io.popen(
                    '.' .. request.path .. ' > ' .. data_file .. ' 2> ' .. error_file, 'w'
                )
                if handle then
                    if request.command == 'POST' then
                        handle:write(request.data)
                    end
                    handle:close()
                end
                local handle = io.open(error_file, 'r')
                if handle then
                    if handle:read('a') ~= '' then
                        build_message(headers.fail, 'html', default_page)
                    else
                        local handle = io.open(data_file, 'r')
                        if not handle then
                            build_message(headers.fail, 'html', default_page)
                        else
                            local data = handle:read('a')
                            build_message(headers.ok, 'html', data)
                            handle:close()
                            os.remove(data_file)
                        end
                    end
                    handle:close()
                    os.remove(error_file)
                end
            end
            local process_nonCGI_request = function()
                local file = io.open('.' .. request.path, 'rb')
                if file then
                    local data = file:read('a')
                    file:close()
                    build_message(headers.ok, request.extension, data)
                else
                    build_message(headers.fail, 'html', default_page)
                end
            end
            if request.directory == '/cgi-bin/' then
                process_CGI_request()
            else
                process_nonCGI_request()
            end
        end
        while not err do
            parse_input_line()
            if input_line == '' then -- Empty line separates HTML header from data.
                if parameters['CONTENT_LENGTH'] ~= nil then
                    request.data = client:receive(parameters['CONTENT_LENGTH'])
                end
                if request.command == 'GET' or request.command == 'POST' then
                    process_command()
                elseif request.command then -- Not supported command.
                    build_message(headers.fail, 'html', default_page)
                end
                if output_message then
                    local try = socket.newtry(function() client:close() end)
                    try(client:send(output_message))
                end
                request = {}
                parameters = {}
                client:close()
            end
            input_line, err = client:receive()
        end
        client:close()
    end
end
