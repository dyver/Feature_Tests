#!/usr/bin/env lua

local sha2 = require('sha2')

local change_password = function(login, password)
    local logins_file = '../auth/logins.conf'
    local Login = function(records)
        local found
        for key, value in pairs(records) do
            if key == login then
                found = true
                break
            end
        end
        if not found then return false end
        records[login].password = sha2.hash256(password)
        local temporary_file = logins_file .. '.temp'
        local f = io.open(temporary_file, 'w')
        f:write('Login {\n')
        for key, value in pairs(records) do
            f:write('    ' .. key .. ' = {\n')
            if value.name then f:write('        name = "' .. value.name .. '",\n') end
            f:write('        password = "' .. value.password .. '",\n')
            f:write('    },\n')
        end
        f:write('}\n')
        f:close()
        os.rename(temporary_file, logins_file)
    end
    local f, error_string = loadfile(logins_file)
    if not f then
        print('ERROR: ' .. error_string)
        return
    end
    debug.setupvalue(f, 1, { Login = Login })
    f()
end

if arg[1] and arg[2] then
    local login, password = arg[1], arg[2]
    change_password(login, password)
end
