#!/usr/bin/env lua

package.path = './cgi-bin/?.lua;' .. package.path

local cgi = require('cgi')
require('lfs')

local parameters = cgi.Params()['Post']

if parameters['Action'] == nil then
   parameters['Login'] = 'Nobody'
   parameters['Action'] = 'prompt'
end

local program_work_directory = '/tmp/backuper_archiver/'
local login_work_directory = program_work_directory .. parameters['Login'] .. '/'
local pid_file = login_work_directory .. 'pid'
local status
local session_key = 0
local session_key_file = login_work_directory .. 'key'
local user_configuration = {}
local packer_command_file = login_work_directory .. 'packer.sh'
local packer_destination_directory

local check_login = function(fake)
    local login = parameters['Login']
    local password = parameters['Password']
    local logins_file = './auth/logins.conf'
    local result, name
    local Login = function(records)
        for key, value in pairs(records) do
            if key == login then
                if value.password == password or fake then
                    result = true
                else
                    result = false
                end
                name = value.name or login
                return
            end
        end
        name = login
    end
    local f = loadfile(logins_file)
    debug.setupvalue(f, 1, { Login = Login })
    f()
    return result, name
end

local check_session = function()
    local f = io.open(session_key_file, 'r')
    if not f then
        return false
    end
    local result = f:read('a')
    f:close()
    if result == parameters['Key'] then
        return true
    end
    return false
end

local create_session_key = function()
    local key = math.random(1, 10000)
    lfs.mkdir(program_work_directory)
    lfs.mkdir(login_work_directory)
    local f = io.open(session_key_file, 'w')
    f:write(key)
    f:close()
    parameters['Key'] = key
end

local report_login_result = function(result, name)
    if result == true then
        append_to_page('<h1 align="center">Добро пожаловать, <em>' .. name .. '</em>.</h1>')
    elseif result == false then
        append_to_page('<h1>Уважаемый <em>' .. name .. '</em>, вы ввели неверный пароль.')
    else
        append_to_page('<h1>Неизвестная учётная запись: <em>' .. name .. '</em>.</h1>')
    end
end

local read_user_configuration = function()
    local login = parameters['Login']
    local directories_list_file = './data/' .. login .. '.conf'
    local result
    local Configuration = function(records)
        for key, value in ipairs(records) do
            if lfs.attributes(value, 'mode') ~= 'directory' then
                value = value .. '  <em>&larr; такого каталога нет</em>'
            end
            table.insert(user_configuration, value)
        end
        packer_destination_directory = records.destination or '/tmp/'
    end
    local f, error_message = loadfile(directories_list_file)
    if not f then
        append_to_page('<h1>ERROR:</h1>')
        append_to_page(error_message)
    else
        debug.setupvalue(f, 1, { Configuration = Configuration })
        f()
    end
    if lfs.attributes(packer_destination_directory, 'mode') == nil then
        append_to_page('<h1>ERROR:</h1>')
        append_to_page('No such directory: ' .. packer_destination_directory)
        user_configuration = {}
        return
    end
end

local show_user_configuration = function()
    if #user_configuration == 0 then return end
    append_to_page('<h3>Это ваш список архивируемых каталогов:</h3>')
    local list = {}
    table.insert(list, '<ul type="square">')
    for _, item in ipairs(user_configuration) do
        table.insert(list, '<li>' .. item .. '</li>')
    end
    table.insert(list, '</ul>')
    append_to_page(table.concat(list))
    append_to_page('<h3>Архивы будут созданы в следующем каталоге:</h3>')
    append_to_page(packer_destination_directory)
    append_to_page('<hr size=5 noshade>')
end

local start_process = function()
    lfs.mkdir(packer_destination_directory)
    local all_pack_commands = ''
    for i, directory_to_pack in ipairs(user_configuration) do
        local pack_file = packer_destination_directory .. '/' .. i .. '_pack.7z'
        os.remove(pack_file)
        pack_command = {
            '7z',
            'a',
            '-t7z',  -- 7z archive
            '-m0=lzma',  -- lzma method
            '-mfb=64',  -- 64 fast bytes for LZMA
            '-md=32m',  -- dictionary size = 32 megabytes
            '-mx=9',  -- ultra compression
            '-ms=on',  -- solid archive
            pack_file,
            '"' .. directory_to_pack .. '"',
            '1> /dev/null'
        }
        pack_command = table.concat(pack_command, ' ')
        pack_command = pack_command .. '\n'
        all_pack_commands = all_pack_commands .. pack_command
    end
    local f = io.open(packer_command_file, 'w')
    f:write('#!/bin/bash\n\n')
    f:write(all_pack_commands)
    f:close()
    os.execute('chmod 777 ' .. packer_command_file)

    local store_pid_suffix = ' & echo $! > ' .. pid_file
    os.execute(packer_command_file .. store_pid_suffix)
end

local add_login_form = function()
    append_to_page('<h1>Вас приветствует программа создания резервной копии.</h1>')
    append_to_page('<h2>Введите имя учётной записи и пароль:</h2>')
    local form = [[
        <form action='/cgi-bin/main.lua' method='post'>
            <div><input type='hidden' name='Action' value='login' /></div>
            <table>
                <tbody>
                    <tr>
                        <td>Учётная запись</td>
                        <td><input type='text' size='20' name='Login' /></td>
                    </tr>
                    <tr>
                        <td>Пароль</td>
                        <td><input type='password' size='20' name='Password' /></td>
                    </tr>
                    <tr>
                        <td><input type='submit' value='Ввод' /></td>
                    </tr>
                </tbody>
            </table>
        </form>
    ]]
    append_to_page(form)
end

local add_start_form = function()
    local form_head = [[
        <form action='/cgi-bin/main.lua' method='post'>
            <div><input type='hidden' name='Login' value=']] .. parameters['Login'] .. [[' /></div>
            <div><input type='hidden' name='Key' value=']] .. parameters['Key'] .. [[' /></div>
            <table>
                <tbody>
                    <tr>
    ]]
    local form_tail = [[
                    </tr>
                </tbody>
            </table>
        </form>
    ]]
    append_to_page(form_head)
    if #user_configuration == 0 then return end
    if (not status) then
        append_to_page([[
            <td>
                <input type='submit' value='Начать резервное копирование' />
            </td>
            <div><input type='hidden' name='Action' value='start' /></div>
        ]])
    else
        append_to_page([[
            <td>
                <input type='submit' value='Обновить статус' />
            </td>
            <div><input type='hidden' name='Action' value='status' /></div>
        ]])
    end
end

local add_status_form = function()
    local retreive_pid = function()
        local f = io.open(pid_file, 'r')
        if not f then
            return false
        end
        local result = f:read('a')
        f:close()
        return result
    end
    local check_process_started = function()
        local pid = retreive_pid()
        if not pid then
            return false
        end
        local f = io.popen('ps | grep -o ' .. pid, 'r')
        local result = f:read('a')
        f:close()
        return result == pid
    end
    if #user_configuration == 0 then return end
    if not check_process_started() then
        append_to_page('<h3>Система готова начать резервное копирование</h3>')
        status = false
    else
        append_to_page('<h3>Идёт резервное копирование</h3>')
        status = true
    end
end

local actions = {}

actions.prompt = function()
    add_login_form()
end

actions.login = function()
    local result, name = check_login()
    report_login_result(result, name)
    if not result then
        return
    end
    create_session_key()
    read_user_configuration()
    show_user_configuration()
    add_status_form()
    add_start_form()
end

actions.start = function()
    if not check_session() then
        return
    end
    local result, name = check_login(true)
    report_login_result(result, name)
    read_user_configuration()
    show_user_configuration()
    start_process()
    add_status_form()
    add_start_form()
end

actions.status = function()
    if not check_session() then
        return
    end
    local result, name = check_login(true)
    report_login_result(result, name)
    read_user_configuration()
    show_user_configuration()
    add_status_form()
    add_start_form()
end

actions[parameters['Action']]()
