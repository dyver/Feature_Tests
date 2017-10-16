#!/usr/bin/env lua

local page = {}

page.header = [[
    <!DOCTYPE html PUBLIC
        '-//W3C//DTD XHTML 1.0 Strict//EN'
        'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'
    >

    <html>

    <head>
        <title>Backuper</title>
        <meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
        <link rel='shortcut icon' type='image/ico' href='/pic/Main.ico' />
    </head>

    <body>
]]

page.footer = [[
    </body>
    </html>
]]

page.body = [[
]]

local append_to_page = function(info)
    if (type(info) == 'table') then
        info = table.concat(info, '\n') .. '<p/>'
    end
    page.body = (page.body or '') .. info .. '\n'
end

local report_error = function(message)
    append_to_page('<h1>ERROR:</h1>')
    append_to_page('<p>' .. message:gsub('\n', '<br>\n'):gsub('\t', '&nbsp;&nbsp;&nbsp;&nbsp;'))
end

local safe_call = function(f)
    local code, r1, r2 = xpcall(f, debug.traceback)
    if not code then
        report_error(r1)
        return false
    else
        return r1, r2
    end
end

local main = function()
    local make_backup, error_message = loadfile('./cgi-bin/make_backup.lua')
    if not make_backup then
        append_to_page('<h1>ERROR:</h1>')
        append_to_page(error_message)
    else
        local environment = _ENV
        environment.page = page
        environment.append_to_page = append_to_page
        environment.report_error = report_error
        debug.setupvalue(make_backup, 1, environment)
        safe_call(make_backup)
    end
    io.write(page.header)
    io.write(page.body)
    io.write(page.footer)
end

main()
